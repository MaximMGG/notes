#include "../header/note.h"
#include "../header/util.h"
#include "../header/textworc.h"
#include <stdlib.h>


int main() {

    int ch;
    initscr();
    raw();
    keypad(stdscr, true);
    noecho();
    box(stdscr, 0, 0);

    NOTE *note = malloc(sizeof(*note));

    note->cury = 1;
    note->curx = 1;
    mvaddch(note->cury, note->curx, '>');
    

    while((ch = getch()) != KEY_F(1)) {
        switch (ch) {
            case '\n' : {

                    break;
                 }
            case 'j':
            case KEY_DOWN: {
                    moveCursore(note, DOWN); 
                    break;
                 }
            case 'k':
            case KEY_UP: {
                    moveCursore(note, UP); 
                    break;
                 }
        } 
    }



    endwin();
    return 0;
}


void print_note(NOTE *note) {
    int y = 1;
    for (int i = 0; i < note->note_count; i++) {
        mvaddstr(y, 1, note->notes[i]->note_name);
        y++;
        if (note->notes[i]->open) {
            for(int j = 0; j < note->notes[i]->len_of_content; j++) {
                mvaddstr(y, 3, note->notes[i]->note_content[j]);
                y++;
            }
            continue;
        }
    }
}

