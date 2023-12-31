#include "../header/filework.h"

#define STR_L 200

//private
char **reset_size(char **buf, int size) {
    if (buf == NULL) {
        buf = (char **) malloc(sizeof(char *) * size);
        return buf;
    }
    
    buf = (char **) realloc(buf, sizeof(char *) * size);

    return buf;
}



char **get_note_from_file(char *path, unsigned int *size) {
    FILE *f = fopen(path, "r");

    if (f == NULL) {
        f = fopen(path, "w");
        return NULL;
    }
    int len = 100;
    char **content = NULL;
    content = reset_size(content, len);
    
    int i = 0;
    while(!feof(f)) {
        char buf[STR_L];
        fgets(buf, STR_L, f);

        content[i] = (char *) malloc(sizeof(char) * strlen(buf) + 1);
        strcpy(content[i++], buf);

        if (i == len) {
            len <<= 1;
            content = reset_size(content, len);
        }
    }

    *size = i - 1;
    content = reset_size(content, i);

    return content;
}

int save_note_in_file(char *path, char **content, int size) {
    FILE *f = fopen(path, "w");

    if (f ==NULL) return 0;

    for(int i = 0; i < size; i++) {
        fprintf(f, "%s\n", content[i]);
    }

    return 1;
}
