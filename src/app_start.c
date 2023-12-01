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

    mvaddch(note->cury, note->curx, '>');

    if (note->content != NULL) {
        print_content(note);
    }

    show_win(stdscr);



    while((ch = getch()) != KEY_F(1)) {
        switch (ch) {
            case 'j':
            case KEY_DOWN: {

                } 
            case 'k':
            case KEY_UP: {

                } 
            case 'c': {
                    char *input = get_user_input_window();
                    add_note(note, input);
                    reset_win(note);
                    break;
                }
            case 'a': {
                    int index = get_note_on_curs(note);
                    char *input = get_user_input_window();
                    add_notecontent(note, note->content[index]->note_name, input);
                    reset_win(note);
                    break;
                }
        }
    }


    endwin();
    return 0;
}
