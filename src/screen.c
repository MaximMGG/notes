#include "../header/screen.h"



char **get_content(NOTE *note) {
    char **cont = malloc(sizeof(char *) * note->open_content);
    int count = 0;
    for(int i = 0; i < note->note_len; i++) {
        cont[count] = malloc(sizeof(char) * strlen(note->content[i]->note_name)); 
        strcpy(cont[count++], note->content[i]->note_name);
        if (note->content[i]->cont_len > 0 && note->content[i]->open == TRUE) {
            for(int j = 0; j < note->content[i]->cont_len; j++) {
                cont[count] = malloc(sizeof(char) * strlen(note->content[i]->cont[j]));
                strcpy(cont[count++], note->content[i]->cont[j]);
            }
        }
    }
    return cont;
}


void print_content(NOTE *note) {
    char **cont = get_content(note);

    for(int i = note->from; i <= note->maxy - 1 && note->open_content; i++) {
        mvaddstr(i + 2, 2, cont[i]);
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
