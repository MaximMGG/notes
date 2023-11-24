#include "../header/textwork.h"
#include "../header/util.h"
#include "../header/note.h"


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


char **parsNoteNot(FILE *f, int *len) {
    int size = 20;

    char **buf = alloc_mem(buf, 0, size);

    while (!feof(f)) {
        fgets(buf[*len++], 200, f);
        if (*len == 20) {
            size <<= 1;
            buf = alloc_mem(buf, *len, size);
        }
    }
    return buf;
}
 
NOTE *getNote() {
    NOTE *note = malloc(sizeof(*note));

    char *path = str_concat(HOME, getlogin(), 0);
    path = str_concat(path, PATH_TO_NOTE, 0);

    FILE *f = fopen(path, "r");

        note->cury = 1;
        note->curx = 1;
        note->note_size = 10;
        note->notes = malloc(sizeof(note->notes) * note->note_size);
        for(int i = 0; i < note->note_size; i++) {
            note->notes[i] = malloc(sizeof(note_c *));
            note->notes[i]->len_of_content = 0;
            note->notes[i]->open = false;
        }
        note->note_count = 0;

    if (f == NULL) {
        return note;
    } else {
        int len = 0;
        char **content = parsNoteNot(f, &len);

        char *buf;
        for (int i = 0; i < len; i++) {
           if (content[i][0] == '-' && content[i][1] != '-') {
               create_note(note, str_substring(content[i], 1, strlen(content[i])));
           }

           if (content[i][0] == '-' && content[i][1] == '-') {
               buf = str_substring(content[i - 1], 1, strlen(content[i - 1])); 
               for (; ;i++) {
                    if (content[i][0] == '-' && content[i][1] != '-') {
                        i--;
                        break;
                    }
                    create_child_note(note, buf, str_substring(content[i], 2, strlen(content[i])));
               }
           }
        }
    }

    return note;
}
