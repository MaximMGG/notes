#include "note.h"
#include <ncurses.h>


#ifndef _SCREEN_
#define _SCREEN_

#define UP 1
#define DOWN 2

//reset window content and print content agane
void reset_win(NOTE *note);

//show all content of window
void show_win(WINDOW *win);

//print all note content on window
void print_content(NOTE *note);

//move curs up or down
void move_curs(NOTE *note, char direction);

#endif //_SCREEN_