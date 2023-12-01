#include "../header/util.h"


char *str_sub(char *tar, int from, int to) {
    char *buf = SMAL(to - from + 1);
    
    int j = 0;
    for(int i = from; i < to; i++, j++ ) {
        buf[j] = tar[i];
    }
    buf[j] = '\0';
    return buf;
}
