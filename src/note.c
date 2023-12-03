#include "../header/note.h"
#include "../header/util.h"
#include <curses.h>



WINDOW *tmp;

char *get_login_from_pwd(char *pwd) {
    char *buf = SMAL(30);

    for(int i = 6, j = 0; ; i++, j++) {
        if(pwd[i] == '/') {
            buf[j] = '\0';
            return buf;
        }
        buf[j] = pwd[i];
    }
    return NULL;
}


NOTE *init_note() {
    NOTE *note = malloc(sizeof(*note));
    note->note_maxsize = 20;
    note->note_len = 0;
    note->content = malloc(sizeof(n_content *) * note->note_maxsize);

    getmaxyx(stdscr, note->maxy, note->maxx);
    tmp = newwin(5, 80, note->maxy - 14, note->maxx / 2 - 40);

    note->cury = 1;
    note->curx = 1;

    note->from = 0;

    note->total_len = 0;
    note->open_content = 0;

    char *login = getlogin();
    if (login == NULL) {
        char *cwd = SMAL(200);
        login = get_login_from_pwd(getcwd(cwd, 200));
        free(cwd);
    }

    char *path = SMAL(100);
    path = strcat(path, HOME);
    path = strcat(path, login);
    path = strcat(path, NOTE_NOT);
    unsigned int size = 0;
    char **content = get_note_from_file(path, &size);

    note->path = SMAL(strlen(path));
    strcpy(note->path, path);
    
    if (content == NULL) {
        return note;
    }

    set_note_from_disk(note, content, &size);
    note->total_len = size;

    free(path);
    return note;
}


void set_note_from_disk(NOTE *note, char **content, unsigned int *size) {
    char *buf;
    for(int i = 0; i < *size; i++) {
        if (content[i][0] == '-' && content[i][1] != '-') {
            buf = str_sub(content[i], 1, strlen(content[i]) - 1);
            add_note(note, buf); 
            i++;
        }
        if (content[i][0] == '-' && content[i][1] == '-') {
            char *parent_name = buf;
            for(;i < *size; i++) {
                if (content[i][0] == '-' && content[i][1] != '-') {
                    i--;
                    break;
                }
                buf = str_sub(content[i], 2, strlen(content[i]) - 1);
                add_notecontent(note, parent_name, buf);
            }
        }
    }
    free(buf);
}


void add_note(NOTE *note, char *note_name) {
    note->content[note->note_len] = malloc(sizeof(n_content *));
    note->content[note->note_len]->note_name = malloc(sizeof(char) * strlen(note_name));
    strcpy(note->content[note->note_len]->note_name, note_name);

    note->content[note->note_len]->cont_maxsize = 20;
    note->content[note->note_len]->cont = malloc(sizeof(char *) * 20);
    note->content[note->note_len]->cont_len = 0;
    note->content[note->note_len]->open = FALSE;
    note->note_len++;
    note->open_content++;
    note->total_len++;

    if (note->note_len >= note->note_maxsize) {
        note->note_maxsize <<= 1;
        note->content = realloc(note->content, sizeof(n_content * ) * note->note_maxsize);
    }
}

void add_notecontent(NOTE *note, char *note_name, char *content) {
    for(int i = 0; i < note->note_len; i++) {
        if (!strcmp(note->content[i]->note_name, note_name)) {
            note->content[i]->cont[note->content[i]->cont_len] = malloc(sizeof(char) * strlen(content));
            strcpy(note->content[i]->cont[note->content[i]->cont_len++], content);

            if(note->content[i]->open == TRUE) {
                note->open_content++;
            }

            if(note->content[i]->cont_len >= note->content[i]->cont_maxsize) {
                note->content[i]->cont_maxsize <<= 1;
                note->content[i]->cont = realloc(note->content[i]->cont, sizeof(char *) * note->content[i]->cont_maxsize);
            }
        }
    }
    note->total_len++;
}

char *get_user_input_window() {
    int y, x;
    getmaxyx(stdscr, y, x);

    echo();
    keypad(tmp, TRUE);
    curs_set(1);
    wmove(tmp, 1, 2);

    box(tmp, 0, 0);
    wrefresh(tmp);
    
    int ch;
    char *buffer = malloc(sizeof(char) * 200);
    int i = 0;
    x = 1;

    while((ch = wgetch(tmp)) != '\n') {
        switch (ch) {
            case KEY_BACKSPACE: {
                    if (x == 2) {
                        wmove(tmp, 1, 2);
                        continue;
                    }
                    mvwaddch(tmp, 1, x--, ' ');           
                    mvwaddch(tmp, 1, x, ' ');           
                    wmove(tmp, 1, x);
                    if (i >= 1)
                        buffer[--i] = ' ';
                    continue;
                    break;
                }
        }
        buffer[i++] = ch;
        x++;
    }
    buffer[i] = '\0';
    buffer = realloc(buffer, sizeof(char) * i);
   
    noecho();
    curs_set(0);

    wclear(tmp);
    wrefresh(tmp);

    return buffer;
}

int get_note_on_curs(NOTE *note) {
    int count = 0;
    for(int i = 0; i < note->open_content + 1; i++) {

        count++;
        if (count == note->cury) return i; 

        if (note->content[i]->cont_len > 0 && note->content[i]->open == TRUE) {
            for(int j = 0; j < note->content[i]->cont_len; j++) {

                count++;
                if (count == note->cury) return i; 
            }
        }
    }
    return count;
}

void set_note_open(NOTE *note, int pos) {
    if (note->content[pos]->open == TRUE) {
         note->content[pos]->open = FALSE;
         note->open_content -= note->content[pos]->cont_len;
    } else {
         note->content[pos]->open = TRUE;
         note->open_content += note->content[pos]->cont_len;
    }
}

void end_work(){
    delwin(tmp);
    endwin();
}

char **prepare_content_for_disk(NOTE *note) {
    char **content = malloc(sizeof(char *) * note->total_len);
    int p = 0;
    int size = 0;

    for(int i = 0; i < note->note_len; i++) {
        size = strlen(note->content[i]->note_name);
        content[p] = SMAL(size + 1);
        memset(content[p], 0, size + 1);
        content[p][0] = '-';
        strcat(content[p++], note->content[i]->note_name);
        if (note->content[i]->cont_len > 0) {
            for(int j = 0; j< note->content[i]->cont_len; j++) {
                size = strlen(note->content[i]->cont[j]);
                content[p] = SMAL(size + 2);
                memset(content[p], 0, size + 2);
                content[p][0] = '-';
                content[p][1] = '-';
                strcat(content[p++], note->content[i]->cont[j]);
            }
        }
    }
    return content;
}
