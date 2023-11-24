#include "../header/util.h"



void moveCursore(NOTE *note ,char where) {
    if (note->cury <= 1 || note->cury >= note->maxy - 1) {
        return;
    }
    mvaddch(note->cury, note->curx, ' ');     
    if (where == UP) {
        mvaddch(--note->cury, note->curx, '>');
    } else {
        mvaddch(++note->cury, note->curx, '>');
    }
}
