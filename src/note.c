#include <curses.h>
#include <ncurses.h>
#include "../header/note.h"



WINDOW *tmp;
CONFIG *cnf;

char *login_from_tmp(char *login) {
    system("whoami > tmp");
    FILE *f = fopen("tmp", "r");
    char *buf = SMAL(30);
    memset(buf, 0, 30);

    if (f == NULL) {
        login = NULL;
    }
    fgets(buf, 30, f);
    remove("tmp");

    fclose(f);

    return buf;
}



NOTE *init_note() {

    cnf = init_config();

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
    char *login = SMAL(30);

    login = getlogin();

    if (login == NULL) {
        free(login);
        login = login_from_tmp(login);
        login[strlen(login) - 1] = '\0';
        if (login == NULL) {
            fprintf(stderr, "ERROR, cant set login, please enter login here or try to reopen note with sudo");
            scanf("%s", login);
        }
    }

    char *path = SMAL(100);
    memset(path, 0, 100);
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
    // free(login);
    return note;
}

CONFIG *init_config() {

    return NULL;
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
    wmove(tmp, 1, 1);

    box(tmp, 0, 0);
    wrefresh(tmp);
    
    int ch;
    char *buffer = malloc(sizeof(char) * 200);
    int i = 0;
    x = 1;

    while((ch = wgetch(tmp)) != '\n') {
        if(ch == KEY_BACKSPACE) {
            if (x > 1) {
                mvwaddch(tmp, 1, x, ' ');
                mvwaddch(tmp, 1, --x, ' ');
                wmove(tmp, 1, x);
                buffer[--i] = 0;
                continue;
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

//private
void set_curs_on_close_note(NOTE *note, int pos) {
    int count = 1;
    for(int i = 0; i < note->note_len; i++) {
        if (pos == i) {
            mvaddch(note->cury, note->curx, ' ');
            note->cury = count;
            mvaddch(note->cury, note->curx, '>');
            return;
        }
        if (note->content[i]->cont_len > 0 && note->content[i]->open == TRUE) {
            count += note->content[i]->cont_len;
        }
        count++;
    }
}


void set_note_open(NOTE *note, int pos) {
    if (note->content[pos]->open == TRUE) {
        set_curs_on_close_note(note, pos);
        if ((int) (note->from - note->content[pos]->cont_len) < 0) {
            note->from = 0;
        } else {
            note->from -= note->content[pos]->cont_len;
        }
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

void delete_note(NOTE *note) {
    int cur_pos = get_note_on_curs(note);

    if (cur_pos == note->note_len - 1) {
        note->note_len--;
        note->total_len -= note->content[cur_pos]->cont_len + 1;
        if (note->content[cur_pos]->open == TRUE) {
            note->open_content -= note->content[cur_pos]->cont_len + 1;
            if (note->from > 0 && (int) (note->from - note->content[cur_pos]->cont_len) < 0) {
                note->from = 0;
            }
        } else {
            note->open_content--;
        }
        if (note->cury > 1) {
            mvaddch(note->cury, note->curx, ' ');
            mvaddch(--note->cury, note->curx, '>');
        }
        free(note->content[cur_pos]);
        return;
    } else {
        note->note_len--;
        note->total_len -= note->content[cur_pos]->cont_len + 1;
        if (note->content[cur_pos]->open == TRUE) {
            note->open_content -= note->content[cur_pos]->cont_len + 1;
            if (note->from > 0 && (int) (note->from - note->content[cur_pos]->cont_len) < 0) {
                note->from = 0;
            }
        } else {
            note->open_content--;
        }
    }

    free(note->content[cur_pos]);
    for(int i = cur_pos; i < note->note_len; i++) {
       note->content[i] = note->content[i + 1]; 
    }
}

//private
void delete_content_helper(NOTE *note, int note_pos, int cont_i) {
    if (cont_i == note->content[note_pos]->cont_len - 1) {
        note->content[note_pos]->cont_len--;
        note->total_len--;
        if (note->content[note_pos]->open == TRUE) {
            note->open_content--;
            if (note->open_content - note->from > note->maxy) {
                note->from--;
            }
        }
        free(note->content[note_pos]->cont[cont_i]);
        mvaddch(note->cury, note->curx, ' ');
        mvaddch(--note->cury, note->curx, '>');
        return;
    } else {
        note->content[note_pos]->cont_len--;
        note->total_len--;
        if (note->content[note_pos]->open == TRUE) {
            note->open_content--;
            if (note->open_content - note->from > note->maxy) {
                note->from--;
            }
        }
        free(note->content[note_pos]->cont[cont_i]);
        for(int i = cont_i; i < note->content[note_pos]->cont_len; i++) {
            note->content[note_pos]->cont[i] = note->content[note_pos]->cont[i + 1];
        }
    }
    mvaddch(note->cury, note->curx, ' ');
    mvaddch(--note->cury, note->curx, '>');
}


void delete_content(NOTE *note) {
    char buf[128];
    memset(buf, 0, 128);
    char ch;
    char ch2 = 0; 
    char ch3 = 0;
    int i = 0, p = 5;
    ch = mvinch(note->cury, note->curx + p);
    while(p < note->maxx) {
        if (ch == 32 || ch == 0) {
            if (ch2 == 0) {
                ch2 = 32;
            } else {
                ch3 = 32;
            }
            if (ch2 == 32 && ch3 == 32) {
                buf[--i] = '\0';
                break;
            }
        } else {
            ch2 = 0;
            ch3 = 0;
        }
        buf[i++] = ch;
        p++;
        ch = mvinch(note->cury, note->curx + p);
    }

    int pos = get_note_on_curs(note);

    for(int i = 0; i < note->content[pos]->cont_len; i++) {
        if (!strcmp(buf, note->content[pos]->cont[i])) {
            delete_content_helper(note, pos, i);
            break;
        }
    }
}
