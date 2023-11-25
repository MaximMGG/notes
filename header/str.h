#include <stdlib.h>

#ifndef _M_STR_
#define _M_STR_


// concat two string with symbol in the middle if symbol == 0, just concat two
// string
char *str_concat(char *first, char *second, char symbol);

//return length of string
unsigned int str_len(char *str);

//copy block off memory from "from" to target if target NULL allocate memory
//copied [size] number of bytes
void mem_cpy(char *target, char *from, unsigned int size);

//compering to strings if same return 1 or 0
char str_cmp(const char *first, const char *second);

#endif
