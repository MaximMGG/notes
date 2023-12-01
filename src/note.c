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

    char *path = strcat(HOME, login);
    path = strcat(path, NOTE_NOT);
    unsigned int size = 0;
    //TODO (Maxim) write whis method
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

