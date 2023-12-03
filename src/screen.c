#include "../header/screen.h"




char **get_content(NOTE *note) {
    char **cont = malloc(sizeof(char *) * note->open_content);
    int count = 0;
    for(int i = 0; i < note->note_len; i++) {
        cont[count] = malloc(sizeof(char) * strlen(note->content[i]->note_name)); 
        strcpy(cont[count++], note->content[i]->note_name);
        if (note->content[i]->cont_len > 0 && note->content[i]->open == TRUE) {
            for(int j = 0; j < note->content[i]->cont_len; j++) {
                cont[count] = malloc(sizeof(char) * strlen(note->content[i]->cont[j]) + 4);
                strcpy(cont[count], "    ");
                strcat(cont[count++], note->content[i]->cont[j]);
            }
        }
    }
    return cont;
}


void print_content(NOTE *note) {
    char **cont = get_content(note);

    for(int i = note->from, j = 1; j <= note->maxy - 2 && j < note->open_content + 1; i++, j++) {
        mvaddstr(j, 2, cont[i]);
    }

    free(cont);
}




void show_win(WINDOW *win) {
    wrefresh(win);
}

void reset_win(NOTE *note) {
    wclear(stdscr);
    print_content(note);
    mvaddch(note->cury, note->curx, '>');
    box(stdscr, 0, 0);
    refresh();
}


void move_curs(NOTE *note, char direction) {
    if(note->open_content < 2) {
        return;
    }
    if (direction == UP) {
        if (note->cury == 1) {
            return;
        }
        if (note->from > 0 && note->cury < 8) {
            note->from--;
            reset_win(note);
            return;
        }
        if (note->from > 0 && note->cury > 7) {
            mvaddch(note->cury--, note->curx, ' ');
            mvaddch(note->cury, note->curx, '>');
            return;
        }
        if (note->from == 0) {
            mvaddch(note->cury--, note->curx, ' ');
            mvaddch(note->cury, note->curx, '>');
            return;
        }
    } else {
        if (note->cury == note->open_content - note->from) {
            return;
        }
        if (note->cury == note->maxy - 2) {
            return;
        }
        if ((note->open_content - note->from) > note->maxy - 2) {
            if (note->cury > note->maxy - 9) {
                note->from++;
                reset_win(note);
                return;
            }
            if (note->cury < note->maxy - 9) {
                mvaddch(note->cury++, note->curx, ' ');
                mvaddch(note->cury, note->curx, '>');
                return;
            }
            else {
                mvaddch(note->cury++, note->curx, ' ');
                mvaddch(note->cury, note->curx, '>');
                return;
            }
        } else {
            mvaddch(note->cury++, note->curx, ' ');
            mvaddch(note->cury, note->curx, '>');
            return;
        }
    }
}

