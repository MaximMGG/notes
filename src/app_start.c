#include "../header/note.h"
#include "../header/screen.h"




int main() {

    int ch;

    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    box(stdscr, 0, 0);

    NOTE *note = init_note();



    endwin();
    return 0;
}
