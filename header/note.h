#ifndef _NOTE_
#define _NOTE_
#include <ncurses.h>
#include <string.h>

typedef struct s_notes_m {
    char *note_name;
    char **content;
    unsigned int len_of_content;
    char open;
    unsigned int lay;
} note_c;


typedef struct s_notes {
    note_c **notes;
    unsigned int note_count;
    unsigned int note_size;

    unsigned short curx;
    unsigned short cury;

    unsigned short maxy;
    unsigned short maxx;

} NOTE;

char *readLineForNote();

int check_note_len(NOTE *note);

void create_note(NOTE *note, char *note_content);

void create_child_note(NOTE *note, char *note_name, char *note_content);

void delete_note(NOTE *note, int pos);

void open_note(NOTE *note);

void print_note(NOTE *note);

void show_screen();

void resetWindow(WINDOW *win, NOTE *note);


#endif // _NOTE_
