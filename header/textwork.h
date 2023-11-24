#include "note.h"
#include <unistd.h>

#define pathToConfig(a, b, c) #a ## #b ## #c

#define HOME "/home/"
#define PATH_TO_NOTE "/.local/share/note/note.not"

NOTE *getNote();

char **parsNoteNot(FILE *f);
