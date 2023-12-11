
#ifndef _SCREEN_
#define _SCREEN_

#include "note.h"
#include <ncurses.h>

#define UP 1
#define DOWN 2

#define NOTES 12
#define CONTENT 13

#define COLOR char
#define COLOR_ALMOND 8
#define COLOR_HEX 9
#define COLOR_TAUPE 10

struct color_list_b {
    char *cont;
    long type;
};

typedef struct color_list_b color_list;


//reset window content and print content agane
void reset_win(NOTE *note);

//show all content of window
void show_win(WINDOW *win);

//print all note content on window
void print_content(NOTE *note);

//move curs up or down
void move_curs(NOTE *note, char direction);

//paind box around window
void box_it(WINDOW *win, COLOR col);

//prepared colors
void prepare_colors();

#endif //_SCREEN_
