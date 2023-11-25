#include <stdlib.h>

#ifndef _M_STR_
#define _M_STR_


// concat two string with symbol in the middle if symbol == 0, just concat two
// string
char *str_concat(char *first, char *second, char symbol);

//return length of string
unsigned int str_len(char *str);

#endif
