#include "../header/note.h"
#include "../header/screen.h"






int main() {

    int ch;

    initscr();
    raw();
    echo();
    keypad(stdscr, TRUE);
    curs_set(0);
    box(stdscr, 0, 0);


    NOTE *note = init_note();

    note->cury = 1;
    note->curx = 1;

    mvaddch(1, 1, '>');

    print_content(note);
    show_win(stdscr);

    while((ch = getch()) != KEY_F(1)) {




    }


    endwin();
    return 0;
}
