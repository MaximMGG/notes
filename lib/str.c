#include "../header/str.h"



unsigned int str_len(char *str) {
    unsigned int len = 0;

    for(int i = 0; ;i++) {
        if (str[i] == '\0' || str[i] == '\n') {
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
    
    if (str_len(target) != size) {
        target = realloc(target, sizeof(char) * size);
    }

    int dword = size / 4;
    int les = size % 4;

    unsigned int *i_t = (unsigned int *)target;
    unsigned int *i_f = (unsigned int *)from;

    for(int i = 0; i < dword; i++) {
        *(i_t++) = *(i_f++);
    }

    unsigned char *c_t = (unsigned char *)i_t;
    unsigned char *c_f = (unsigned char *)i_f;
    
    for(int i = 0; i < les; i++) {
        *(c_t++) = *(c_f++);
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

