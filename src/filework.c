#include "../header/filework.h"


//[private]
char **reset_content(char **content, int size, int wsize, int from) {
    if (content == NULL) {
       content = (char **) malloc(sizeof(char *) * size);
    } else {
        content = realloc(content, sizeof(char *) * size);
    }
    for(int i = from; i < size; i++) {
        content[i] = malloc(sizeof(char) * wsize);
    }
    return content;
}

char *get_path_to_dir(char *path) {
    int len = str_len(path) - 9;
    char *path_dir = malloc(sizeof(char) * len);
    int i = 0;
    for(; i < len - 1; i++) {
        path_dir[i] = path[i];
    }
    path_dir[i] = '\0';
    return path_dir;
}


//read note.not and return all content from file, if file not exist create it
//and return NULL, athou return size of note contents
char **get_note_from_file(char *path, unsigned int *size) {

    FILE *f = fopen(path, "r");
    if (f == NULL) {
        f = fopen(path, "w");
        system(str_concat("mkdir ", get_path_to_dir(path), 0)); 

        fclose(f);
        return NULL;
    }
    int count = 100;
    char **content = reset_content(NULL, 100, 10, 0);
    int i = 0;


    while(!feof(f)) {
        char *buf = malloc(sizeof(char) * 200);
        fgets(buf, 200, f);
        mem_cpy(content[i++], buf, str_len(buf));
        if (i > count) {
            count <<= 1;
            content = reset_content(content, count, 10, i);
        }
        free(buf);
    }
    fclose(f);
    return content;
}

//save note content in file note.not
int save_note_in_file(char *path, char **content, int size) {
    FILE *f = fopen(path, "w");

    for(int i = 0; i < size; i++) {
        fputs(content[i], f);
    }

    fclose(f);

    return 1;
}
