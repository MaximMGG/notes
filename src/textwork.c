#include "../header/textwork.h"
#include "../header/util.h"

char **alloc_mem(char **buf, int from, int size) {
    if (buf == NULL) {
        buf = malloc(sizeof(char *) * size);
    } else {
        buf = realloc(buf, sizeof(char *) * size);
    }

    for (int i = from; i < size; i++) {
        buf[i] = malloc(sizeof(char) * 200);
    }

    return buf;
}


char **parsNoteNot(FILE *f) {
    int size = 20;

    char **buf = alloc_mem(buf, 0, size);
    int i = 0;

    while (!feof(f)) {
        fgets(buf[i++], 200, f);
        if (i == 20) {
            size <<= 1;
            buf = alloc_mem(buf, i, size);
        }
    }
    return buf;
}
 
NOTE *getNote() {
    NOTE *note = malloc(sizeof(*note));

    char *path = str_concat(HOME, getlogin(), 0);
    path = str_concat(path, PATH_TO_NOTE, 0);

    FILE *f = fopen(path, "r");
    if (f == NULL) {
        f = fopen(path, "w");
        note->cury = 1;
        note->curx = 1;
        note->note_size = 10;
        note->notes = malloc(sizeof(note->notes) * note->note_size);
        note->note_count = 0;
        return note;
    } else {
        char **content_of_note = parsNoteNot(f);
    }

    return NULL;
}
