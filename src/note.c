#include "../header/note.h"
#include "../header/util.h"


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

    note->cury = 1;
    note->curx = 1;

    note->from = 0;

    note->total_len = 0;
    note->open_content = 0;

    char *login = getlogin();
    if (login == NULL) {
        char *cwd = SMAL(200);
        login = get_login_from_pwd(getcwd(cwd, 200));
    }

    char *path = SMAL(100);
    path = strcat(HOME, login);
    path = strcat(path, NOTE_NOT);
    unsigned int size = 0;
    char **content = get_note_from_file(path, &size);
    
    if (content == NULL) {
        return note;
    }

    set_note_from_disk(note, content, &size);
    note->total_len = size;

    return note;
}


void set_note_from_disk(NOTE *note, char **content, unsigned int *size) {
    for(int i = 0; i < *size; i++) {
        char *buf;
        if (content[i][0] == '-' && content[i][1] != '-') {
            buf = str_sub(content[i], 1, strlen(content[i]) - 1);
            add_note(note, buf); //TODO (Maxim) write method
        }
        if (content[i][0] == '-' && content[i][1] == '-') {
            char *parent_name = buf;
            for(;i < *size; i++) {
                if (content[i][0] == '-' && content[i][1] != '-') {
                    i--;
                    break;
                }
                buf = str_sub(content[i], 2, strlen(content[i]) - 1);
                //TODO (Maxim) write this method
                add_notecontent(note, parent_name, buf);
            }
        }
        if (buf != NULL) {
            free(buf);
        }
    }
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

            if(note->content[i]->cont_len >= note->content[i]->cont_maxsize) {
                note->content[i]->cont_maxsize <<= 1;
                note->content[i]->cont = realloc(note->content[i]->cont, sizeof(char *) * note->content[i]->cont_maxsize);
            }
        }
    }
}
