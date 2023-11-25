#include "../header/screen.h"

//reset window content and print content agane
void reset_win(NOTE *note) {
    wclear(stdscr);
    print_content(note);
    box(stdscr, 0, 0);
    mvaddch(note->cury, note->curx, '>');
    refresh();
}

//show all content of window
void show_win(WINDOW *win) {
    wrefresh(win);
}

//[private]
char **get_screen_content(NOTE *note, int *size) {
    char **content = malloc(sizeof(char *) * note->total_len);

    int p = 0;
    for(int i = 0; i < note->note_len; i++) {
        mem_cpy(content[p++], note->content[i]->note_name, str_len(note->content[i]->note_name));
        if (note->content[i]->cont_len > 0 && note->content[i]->open == TRUE) {
            for(int j = 0; j < note->content[i]->cont_len; j++) {
                mem_cpy(content[p++], 
                       str_concat("    ", note->content[i]->cont[j], 0) , str_len(note->content[i]->cont[j]));
            }
        }
    }
    *size = p;
    return content;
}


//print all note content on window
void print_content(NOTE *note) {
    int size = 0;
    char **content = get_screen_content(note, &size);
    int y = 1;
    for (int i = note->from; i < size || i < note->to; i++) {
       mvaddstr(y++, 1, content[i]); 
    }
}

//move curs up or down
void move_curs(NOTE *note, char direction) {
    if (direction == UP) {
        if (note->cury == 1) return;
        else {

        }
    }
}
