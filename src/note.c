#include "../header/note.h"
#include "../header/util.h"
#include "../header/textwork.h"
#include <stdlib.h>


int main() {

    int ch;
    initscr();
    raw();
    keypad(stdscr, true);
    noecho();
    box(stdscr, 0, 0);

    NOTE *note = getNote();

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

        }
    } 
}



