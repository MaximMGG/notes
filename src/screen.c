#include "../header/screen.h"
#include <ncurses.h>
#include <stdalign.h>




color_list **get_content(NOTE *note) {
    color_list **cont = (color_list **)malloc(sizeof(struct color_list_b *) * note->open_content);
    for(int i = 0; i < note->open_content; i++) {
        cont[i] = (struct color_list_b *) malloc(sizeof(struct color_list_b));
    }
    int count = 0;
    for(int i = 0; i < note->note_len; i++) {
        cont[count]->cont = malloc(sizeof(char) * strlen(note->content[i]->note_name));
        strcpy(cont[count]->cont, note->content[i]->note_name);
        cont[count++]->type = NOTES;
        if (note->content[i]->open == TRUE && note->content[i]->cont_len > 0) {
            for(int j = 0; j < note->content[i]->cont_len; j++) {
                cont[count]->cont = malloc(sizeof(char) * strlen(note->content[i]->cont[j]));
                strcpy(cont[count]->cont, note->content[i]->cont[j]);
                cont[count++]->type = CONTENT;
            }
        }
    }
    return cont;
}

void prepare_colors() {
    init_color(COLOR_ALMOND, 851, 964, 648);
    init_color(COLOR_HEX, 914, 863, 789);
    init_color(COLOR_TAUPE, 281, 234, 195);
    // init_color(COLOR_BLACK, 281, 234, 195);
    init_pair(1, COLOR_ALMOND, COLOR_BLACK);
    init_pair(2, COLOR_HEX, COLOR_BLACK);
    init_pair(3, COLOR_TAUPE, COLOR_TAUPE);
}

void print_content(NOTE *note) {
    color_list **cont = get_content(note);

    // init_pair(1, COLOR_ALMOND, COLOR_BLACK);
    // init_pair(2, COLOR_HEX, COLOR_BLACK);
    

    for(int i = note->from, j = 1; j <= note->maxy - 2 && j < note->open_content + 1; i++, j++) {
        if (cont[i]->type == NOTES) {
            attron(COLOR_PAIR(1));
            mvaddstr(j, 2, cont[i]->cont);
            attroff(COLOR_PAIR(1));

        } else {
            attron(COLOR_PAIR(2));
            mvaddstr(j, 2, cont[i]->cont);
            attroff(COLOR_PAIR(2));
        }
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
    box_it(stdscr, COLOR_TAUPE);
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

void box_it(WINDOW *win, COLOR col) {
    int y, x;
    getmaxyx(win, y, x);
    char *line = malloc(sizeof(char) * x + 1);
    memset(line, 32, x);
    line[x + 1] = '\0';
    
    wattron(win, COLOR_PAIR(3));
    mvwaddstr(win, 0, 0, line);
    mvwaddstr(win, y - 1, 0, line);
    wattroff(win, COLOR_PAIR(3));
}
