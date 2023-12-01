#include "../header/filework.h"

#define STR_L 200

char **reset_size(char **buf, int size) {
    if (buf == NULL) {
        buf = malloc(sizeof(char *) * size);
        return buf;
    }
    
    buf = realloc(buf, sizeof(char *) * size);

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
        char *buf = malloc(sizeof(char) * STR_L);
        fgets(buf, STR_L, f);

        content[i] = malloc(sizeof(char) * strlen(buf));
        strcpy(content[i++], buf);
        free(buf);

        if (i == len) {
            len <<= 1;
            content = reset_size(content, len);
        }
    }

    *size = i - 1;
    content = reset_size(content, i);

    return content;
}
