#include "../header/str.h"



unsigned int str_len(char *str) {
    unsigned int len = 0;

    for(int i = 0; ;i++) {
        if (str[i] == '\0' && str[i] == '\n') {
            len = ++i;
            return len;
        }
    }

    return len;
}

char *str_concat(char *first, char *second, char symbol) {
    char *buf = malloc(sizeof(char) * (str_len(first) + str_len(second)));
    
    int i, j;

    for(i = 0;  ;i++) {
        if (first[i] == '\0') {
            break;
        }
        buf[i] = first[i];
    }

    if (symbol != 0) {
        buf[i++] = symbol; 
    }

    for(j = 0; ; j++, i++) {
        buf[i] = second[j];
        if (second[j] == '\0') {
            break;
        }
    }
    return buf;
}

void mem_cpy(char *target, char *from, unsigned int size) {
    
    if (target == NULL) {
        target = malloc(sizeof(char) * size);
    } else {
        target = realloc(target, sizeof(char) * size); 
    }

    int dword = size / 4;
    int les = size % 4;

    unsigned char *b_t;
    unsigned char *b_f;

    if (dword > 0) {
        unsigned int *p_t = (unsigned int *)target;
        unsigned int *p_f = (unsigned int *)from;

        for(int i = 0; i < dword; i++) {
            *(p_t)++ = *(p_f)++;
        }
 
        b_t = (unsigned char *) p_t;
        b_f = (unsigned char *) p_f;
    } else {
        b_t = (unsigned char *) target;
        b_t = (unsigned char *) from;
    }

    for(int i = 0; i < les; i++) {
        *(b_t)++ = *(b_f)++;
    }
}


char str_cmp(const char *first, const char *second) {

    for(int i = 0; ; i++) {
        if (first[i] != second[i]) {
            return 0;
        }

        if (first[i] == '\0' && second[i] == '\0') {
            return 1;
        }
    }

    return 1;
}
