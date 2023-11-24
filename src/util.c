#include "../header/util.h"

char *str_substring(char *tmp, unsigned int from, unsigned int to) {

    char *buf = malloc(sizeof(char) * (to - from + 2));

    for(int i = from, j = 0; i <= to; i++, j++) {
        buf[j] = tmp[i];
        if(tmp[i] == '\0') {
            break;
        }
    }
    return buf;
}




char *str_concat(char *first, char *second, char symbol) {
    char *buf = malloc(sizeof(char) * (strlen(first) + strlen(second)));
    int i, j;
    for(i = 0; ;i++) {
        buf[i] = first[i];
        if (first[i] == '\0') break;
    }

    if (symbol != 0) {
        buf[i++] = symbol;
    }

    for(j = 0; ;j++, i++) {
        buf[i] = second[j];
        if (second[j] == '\0') {
            break;
        }
    }
    return buf;
}


void moveCursore(NOTE *note ,char where) {
    if (note->cury <= 1 || note->cury >= note->maxy - 1) {
        return;
    }
    mvaddch(note->cury, note->curx, ' ');     
    if (where == UP) {
        mvaddch(--note->cury, note->curx, '>');
    } else {
        if (note->cury >= check_note_len(note)) {
            return;
        }
        mvaddch(++note->cury, note->curx, '>');
    }
}

int check_note_len(NOTE *note) {
    int count = note->note_count;

    for(int i = 0; i < note->note_count; i++) {
        if (note->notes[i]->open == true) {
            count += note->notes[i]->len_of_content;
        }
    }

    return count;
}
