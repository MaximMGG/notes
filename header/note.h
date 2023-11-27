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

#define WSL_LOGIN(a, b) do { \
                for (int i = 6, j = 0; ; j++, i++) { \
                    if (a[i] = '/') { \
                        b[j] = '\0'; \
                        break;\
                    }\
                    b[j] = a[i];\
                }\
            }while(0);\



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

    int from;
    int to;

    unsigned int total_len;
    unsigned int open_content;

} NOTE;

// initialize note, if file on disk apty just create empy note;
NOTE *init_note();

//fill NOTE from note.not file
void set_note_from_disk(NOTE *note, char **content, unsigned int *size);

//add note 
void add_note(NOTE *note, char *note_name);

//add content in note_name note
void add_notecontent(NOTE *note, char *note_name, char *content);

//delete note with name note_name
void delete_note(NOTE *note, char *note_name);

//delete content from note is pos position
void delte_content(NOTE *note, char *note_name, unsigned int pos);

//cast all notes and content to char ** for disk writing
char **prepare_content_for_disk(NOTE *note);

//return sum of all open notes
int get_open_content(NOTE *note);

//if note open == true -> set false and opozite
void set_note_open(NOTE *note);

//return index of note on cury position
int get_note_on_curs(NOTE *note);

//create window for user input and return char * with user enter string
char *user_input_window();


#endif //_NOTE_
