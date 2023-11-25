
#ifndef _FILE_WORK_
#define _FILE_WORK_


//read note.not and return all content from file, if file not exist create it
//and return NULL
char **get_note_from_file(char *path);

//save note content in file note.not
int save_note_in_file(char **content);


#endif
