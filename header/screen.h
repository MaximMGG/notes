#include "note.h"
#include <ncurses.h>


#ifndef _SCREEN_
#define _SCREEN_

//reset window content and print content agane
void reset_win(NOTE *note);

//show all content of window
void show_win(WINDOW *win);

//print all note content on window
void print_content(NOTE *note);

#endif //_SCREEN_
