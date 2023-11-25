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
    int y, x;
    getmaxyx(stdscr, y, x);


    NOTE *note = init_note();

    if (note->note_len == 0) {
        mvaddstr(y - 1, x / 2 - 4, "Enter c for creating note");
        refresh();
    }

    mvaddch(1, 1, '>');

    print_content(note);
    show_win(stdscr);

    while((ch = getch()) != KEY_F(1)) {




    }


    endwin();
    return 0;
}
