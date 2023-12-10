#include "../header/note.h"
#include "../header/screen.h"


int main() {

    int ch;

    initscr();
    start_color();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    prepare_colors();
    box_it(stdscr, COLOR_TAUPE);

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
            case '\n': {
                    int index = get_note_on_curs(note);
                    set_note_open(note, index); 
                    reset_win(note);
                    break;
                }
            case 'd': {
                    delete_note(note);                    
                    reset_win(note);
                    break;
                }
            case 'r': {
                    delete_content(note);
                    reset_win(note);
                    break;
                }
        }
    }

    save_note_in_file(note->path, prepare_content_for_disk(note), note->total_len);
    end_work();
    return 0;
}
