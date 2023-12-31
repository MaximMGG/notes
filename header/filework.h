#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

#ifndef _FILE_WORK_
#define _FILE_WORK_


#define LOGIN "login"


//read note.not and return all content from file, if file not exist create it
//and return NULL, athou return size of note contents
char **get_note_from_file(char *path, unsigned int *size);

//save note content in file note.not
int save_note_in_file(char *path, char **content, int size);

//return MAP with config from saved file
MAP *read_config_from_file();

#endif
