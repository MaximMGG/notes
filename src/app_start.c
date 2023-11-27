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
    getmaxyx(stdscr, note->maxy, note->maxx);


    mvaddch(1, 1, '>');

    print_content(note);
    show_win(stdscr);

    if (note->note_len == 0) {
        mvaddstr(note->maxy - 2, note->maxx / 2 - 8, "Enter c for creating note");
        refresh();
    }

    while((ch = getch()) != KEY_F(1)) {
        switch (ch) {
            case 'j':
            case KEY_DOWN: {
                    move_curs(note, DOWN); 
                    show_win(stdscr);
                    break;
                 }
            case 'k':
            case KEY_UP: {
                    move_curs(note, UP); 
                    show_win(stdscr);
                    break;
                 }
            case '\n': {
                    set_note_open(note);
                    get_open_content(note);
                    reset_win(note);
                    break;
                 }
            case 'c': {
                    add_note(note, user_input_window());
                    get_open_content(note);
                    reset_win(note);
                    break;
                 }
            case 'a': {
                    int pos = get_note_on_curs(note);
                    add_notecontent(note, 
                            note->content[pos]->note_name, user_input_window());
                    get_open_content(note);
                    reset_win(note);
                    break;
                 }
        }

    }

    char **content = prepare_content_for_disk(note);
    save_note_in_file(note->path, content, note->total_len);

    endwin();
    return 0;
}
