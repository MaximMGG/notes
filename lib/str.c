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
