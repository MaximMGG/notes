#include "../header/note.h"



// initialize note, if file on disk apty just create empy note;
NOTE *init_note() {

    NOTE *new = malloc(sizeof(*new));

    new->note_len = 0;
    new->note_maxsize = 20;
    new->total_len = 0;
    new->open_content = 0;

    new->cury = 1;
    new->curx = 1;

    new->from = 0;
    new->to = 0;

    new->maxy = 0;
    new->maxx = 0;

    new->content = malloc(sizeof(n_content *) * new->note_maxsize);

    unsigned int size = 0;

    char **content = get_note_from_file(GET_PATH(getlogin()), &size);

    if (content == NULL) {
        return new;
    }
    set_note_from_disk(new, content, &size);

    new->to = new->total_len;

    return new;
}

void set_note_from_disk(NOTE *note, char **content, unsigned int *size) {
    for (int i = 0; i < *size; i++) {
         if(content[i][0] == '-' && content[i][1] != '-') {
            add_note(note, content[i]);
         }
         if(content[i][0] == '-' && content[i][1] == '-') {
             char *note_name = content[i - 1];
             for(; ; i++) {
                if (content[i][0] == '-' && content[i][1] != '-') {
                    i--;
                    break;
                }
                add_notecontent(note, note_name, content[i]);
             }

         }
    }
}

//add note 
void add_note(NOTE *note, char *note_name) {
    note->content[note->note_len] = malloc(sizeof(n_content *));
    note->content[note->note_len]->cont_maxsize = 20;
    note->content[note->note_len]->cont_len = 0;
    note->content[note->note_len]->cont = malloc(sizeof(char *) * 20);

    mem_cpy(note->content[note->note_len++]->note_name, note_name, 
                                                    str_len(note_name));
    
    if (note->note_len >= note->note_maxsize) {
        note->note_maxsize <<= 1;
        note->content = realloc(note->content, 
                        sizeof(note->content) * note->note_maxsize);
    }

    note->content[note->note_len - 1]->open = FALSE;
    note->total_len++;

}

//add content in note_name note
void add_notecontent(NOTE *note, char *note_name, char *content) {
    for(int i = 0; i < note->note_len;  i++) {
        if (str_cmp(note->content[i]->note_name, note_name)) {
            mem_cpy(note->content[i]->cont[note->content[i]->cont_len++], 
                    content, str_len(content));

            if (note->content[i]->cont_len >= note->content[i]->cont_maxsize) {
                note->content[i]->cont_maxsize <<= 1;
                note->content[i]->cont = realloc(note->content[i]->cont, 
                        sizeof(char *) * note->content[i]->cont_maxsize);
            }
            break;
        }
    }
    note->total_len++;
}

//delete note with name note_name
void delete_note(NOTE *note, char *note_name);

//delete content from note is pos position
void delte_content(NOTE *note, char *note_name, unsigned int pos);


char **prepare_content_for_disk(NOTE *note) {
    char **content = malloc(sizeof(char *) * note->total_len);
    int j = 0;

    for(int i = 0; i < note->note_len; i++) {
        mem_cpy(content[j++], str_concat("-", note->content[i]->note_name, 0), str_len(note->content[i]->note_name));
        if (note->content[i]->cont_len > 0) {
            for(int k = 0; k < note->content[i]->cont_len; k++) {
                mem_cpy(content[j++], str_concat("--", note->content[i]->cont[k], 0), str_len(note->content[i]->cont[k]));
            }
        }
    }
    return content;
}

//TODO (Maxim) need to use only when notes opens or closes
int get_open_content(NOTE *note) {
    int count = note->note_len;
    for(int i = 0; i < note->note_len; i++) {
        if (note->content[i]->cont_len > 0 && note->content[i]->open == TRUE) {
            count += note->content[i]->cont_len;
        }
    }
    note->open_content = count;
    return count;
}

