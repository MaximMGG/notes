#include "str.h"
#include "filework.h"
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>


#ifndef _NOTE_
#define _NOTE_

#define HOME "/home/"
#define NOTE_NOT "/.local/share/note/note.not"

#define GET_PATH(b) str_concat(str_concat(HOME, b, 0), NOTE_NOT, 0) 


typedef struct s_content {
    char *note_name;
    char **cont;
    unsigned int cont_len;
    unsigned int cont_maxsize;
    bool open;
} n_content;



typedef struct s_note {

    n_content **content;
    unsigned int note_len;
    unsigned int note_maxsize;

    int maxy;
    int maxx;

    int cury;
    int curx;

} NOTE;

// initialize note, if file on disk apty just create empy note;
NOTE *init_note();

//fill NOTE from note.not file
void set_note_from_disk(NOTE *note, char **content);

//add note 
void add_note(NOTE *note, char *note_name);

//add content in note_name note
void add_notecontent(NOTE *note, char *note_name, char *content);

//delete note with name note_name
void delete_note(NOTE *note, char *note_name);

//delete content from note is pos position
void delte_content(NOTE *note, char *note_name, unsigned int pos);




#endif //_NOTE_
