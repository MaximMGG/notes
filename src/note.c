#include "../header/note.h"
#include <unistd.h>



//[private]
char *get_login_from_pwd(char *pwd, char *login) {
    int i = 6, j = 0;
    for(;;i++, j++) {
        if (pwd[i] == '/') {
            login[j] = '\0';
            return login;
        }
        login[j] = pwd[i];
    }
}


// initialize note, if file on disk apty just create empy note;
NOTE *init_note() {

    NOTE *new = malloc(sizeof(*new));

    new->note_len = 0;
    new->note_maxsize = 20;
    new->total_len = 0;
    new->open_content = 0;

    new->cury = 1;
    new->curx = 1;

    new->from = 0;
    new->to = 0;

    new->maxy = 0;
    new->maxx = 0;

    new->content = malloc(sizeof(n_content *) * new->note_maxsize);

    unsigned int size = 0;

    char *name = malloc(sizeof(char) * 30);
    char *pwd = malloc(sizeof(char) * 100);

    getcwd(pwd, 100);
    name = getlogin();

    //it should work for ubuntu wsl
    if (name == NULL || str_len(name) < 1) {
        name = get_login_from_pwd(pwd, name);
    }

    char *total_path = GET_PATH(name);

    char **content = get_note_from_file(total_path, &size);

    char *path = malloc(sizeof(char) * str_len(total_path));
    mem_cpy(path, total_path, str_len(total_path));
    new->path = path;

    // free(name);
    // free(pwd);
    // free(total_path);

    if (content == NULL) {
        return new;
    }
    set_note_from_disk(new, content, &size);

    new->to = new->total_len;

    return new;
}

void set_note_from_disk(NOTE *note, char **content, unsigned int *size) {
    for (int i = 0; i < *size; i++) {
         if(content[i][0] == '-' && content[i][1] != '-') {
            add_note(note, content[i]);
         }
         if(content[i][0] == '-' && content[i][1] == '-') {
             char *note_name = content[i - 1];
             for(; ; i++) {
                if (content[i][0] == '-' && content[i][1] != '-') {
                    i--;
                    break;
                }
                add_notecontent(note, note_name, content[i]);
             }

         }
    }
}

//add note 
void add_note(NOTE *note, char *note_name) {
    int size = str_len(note_name);

    note->content[note->note_len] = malloc(sizeof(n_content *));
    note->content[note->note_len]->cont_maxsize = 20;
    note->content[note->note_len]->cont_len = 0;
    note->content[note->note_len]->cont = malloc(sizeof(char *) * 20);
 
    note->content[note->note_len]->note_name = malloc(sizeof(char) * size);

    mem_cpy(note->content[note->note_len++]->note_name, note_name, size);
    
    if (note->note_len >= note->note_maxsize) {
        note->note_maxsize <<= 1;
        note->content = realloc(note->content, 
                        sizeof(note->content) * note->note_maxsize);
    }

    note->content[note->note_len - 1]->open = FALSE;
    note->total_len++;

}

//add content in note_name note
void add_notecontent(NOTE *note, char *note_name, char *content) {
    for(int i = 0; i < note->note_len;  i++) {
        if (str_cmp(note->content[i]->note_name, note_name)) {
            int len = str_len(content);
            note->content[i]->cont[note->content[i]->cont_len] = malloc(sizeof(char) * len);

            mem_cpy(note->content[i]->cont[note->content[i]->cont_len++], content, len);

            if (note->content[i]->cont_len >= note->content[i]->cont_maxsize) {
                note->content[i]->cont_maxsize <<= 1;
                note->content[i]->cont = realloc(note->content[i]->cont, 
                        sizeof(char *) * note->content[i]->cont_maxsize);
            }
            break;
        }
    }
    note->total_len++;
}

//delete note with name note_name
void delete_note(NOTE *note, char *note_name);

//delete content from note is pos position
void delte_content(NOTE *note, char *note_name, unsigned int pos);


char **prepare_content_for_disk(NOTE *note) {
    char **content = malloc(sizeof(char *) * note->total_len);
    int j = 0;

    for(int i = 0; i < note->note_len; i++) {
        int len = str_len(note->content[i]->note_name);
        content[j] = malloc(sizeof(char) * len + 1);
        mem_cpy(content[j++], str_concat("-", note->content[i]->note_name, 0), len);
        if (note->content[i]->cont_len > 0) {
            for(int k = 0; k < note->content[i]->cont_len; k++) {
                len = str_len(note->content[i]->cont[k]);
                content[j] = malloc(sizeof(char) * len + 2);
                mem_cpy(content[j++], str_concat("--", note->content[i]->cont[k], 0), str_len(note->content[i]->cont[k]));
            }
        }
    }
    return content;
}

//TODO (Maxim) need to use only when notes opens or closes
int get_open_content(NOTE *note) {
    int count = note->note_len;
    for(int i = 0; i < note->note_len; i++) {
        if (note->content[i]->cont_len > 0 && note->content[i]->open == TRUE) {
            count += note->content[i]->cont_len;
        }
    }
    note->open_content = count;
    return count;
}


//if note open == true -> set false and opozite
void set_note_open(NOTE *note) {
    int index = get_note_on_curs(note);
    if (note->content[index]->open == TRUE)
        note->content[index]->open = FALSE;
    else 
        note->content[index]->open = TRUE;
    }

//return index of note on cury position
int get_note_on_curs(NOTE *note) {
    int count = 1;
    for(int i = 0; note->note_len; i++) {
        if (note->cury == count) {
            return i;
        }
        count++;

        if (note->content[i]->cont_len > 0 && note->content[i]->open == TRUE) {

            for(int j = 0; j < note->content[i]->cont_len; j++) {
                if (note->cury == count) {
                    return i;
                }
                count++;
            }

        }
    }
    return -1;
}


//create window for user input and return char * with user enter string
//TODO(maxim) if size of enter > 200 realloc
char *user_input_window() {
    int ch;
    int y, x;
    getmaxyx(stdscr, y, x);
    WINDOW *tmp = newwin(5, 80, y - 15, x / 2 - 40);
    box(tmp, 0, 0);
    echo();
    curs_set(1);
    keypad(tmp, TRUE);

    int i = 0;
    char *enter = malloc(sizeof(char) * 200);
    wmove(tmp, 1, 1);
    wrefresh(tmp);
    y = 1;
    x = 1;

    while ((ch = wgetch(tmp)) != '\n') {
        switch (ch) {
            case KEY_BACKSPACE: {
                mvwaddch(tmp, y, --x, ' ');       
                // mvwaddch(tmp, y, --x, ' ');       
                wmove(tmp, y, x);
                continue;
                break;
            }
        }
        enter[i++] = ch;
        x++;
    }

    enter[i] = '\0';
    noecho();
    curs_set(0);

    delwin(tmp);

    return enter;
}
