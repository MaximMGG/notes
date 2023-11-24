#include <string.h>
#include <stdlib.h>
#include "note.h"
#define UP 1
#define DOWN 2




char *str_concat(char *first, char *secont, char symbol);

char *str_substring(char *tmp, unsigned int from, unsigned int to);

void moveCursore(NOTE *note, char where);
