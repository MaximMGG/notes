#include "../header/note.h"
#include "../header/util.h"
#include "../header/textwork.h"
#include <ncurses.h>
#include <stdlib.h>


int main() {

    int ch;
    initscr();
    raw();
    keypad(stdscr, true);
    noecho();
    box(stdscr, 0, 0);

    NOTE *note = getNote();
    if (note->note_count == 0) {
        mvaddstr(2, 30, "enter c for creating notes");
        show_screen();
    }

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
            case 'c' :{
                    char *buf = readLineForNote();
                    resetWindow(stdscr, note);
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
                mvaddstr(y, 3, note->notes[i]->content[j]);
                y++;
            }
            continue;
        }
    }
    note->cury = 1;
    note->curx = 1;
    mvaddch(1, 1, '>');
    box(stdscr, 0, 0);
}


void create_note(NOTE *note, char *note_content) {
    if (note->note_count == 0) {
        note->notes = malloc(sizeof(note->notes) * 20);
    }
    if (note->note_count == 20) {
        note->notes = realloc(note->notes, sizeof(note->notes) * 20);
    }



    note->notes[note->note_count] = malloc(sizeof(*(note->notes[note->note_count]))); 
    note->notes[note->note_count]->note_name = malloc(sizeof(char) * strlen(note_content));
    strcpy(note->notes[note->note_count++]->note_name, note_content);
}


void create_child_note(NOTE *note, char *note_name, char *note_content) {
    for(int i = 0; i < note->note_count; i++) {
        if (!strcmp(note->notes[i]->note_name, note_name)) {
            note->notes[i]->content[note->notes[i]->len_of_content] = malloc(sizeof(char) * strlen(note_content));
            strcpy(note->notes[i]->content[note->notes[i]->len_of_content++], note_content);
        }
    } 
}

//TODO (Maxim) write func read name of note 
char *readLineForNote() {
    int x, y;
    getmaxyx(stdscr, y, x);
    WINDOW *tmp = newwin(10, 120, y - 20, 5);
    echo();
    box(tmp, 0, 0);
    wrefresh(tmp);

    wmove(tmp, 1, 1);
    char *buffer = malloc(sizeof(char) * 200);
    int i = 0;

    int ch;
    while((ch = wgetch(tmp)) != '\n') {
        buffer[i++] = ch;
    }
    buffer[i] = '\0';

    wrefresh(tmp);

    noecho();
    delwin(tmp);

    return buffer;
}

void show_screen() {
    wrefresh(stdscr);
}

void resetWindow(WINDOW *win, NOTE *note) {
    wclear(win);
    print_note(note);
    wrefresh(win);
}

