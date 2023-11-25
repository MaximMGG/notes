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
    getmaxyx(stdscr, note->maxy, note->maxx);

    if (note->note_len == 0) {
        mvaddstr(note->maxy - 1, note->maxx / 2 - 4, "Enter c for creating note");
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
