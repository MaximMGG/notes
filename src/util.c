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


MAP *map_init(unsigned int size) {
    MAP *map;
    map = malloc(sizeof(*map));
    if (size == 0) 
        map->map = malloc(sizeof(C_map *) * DEF_MAP_SIZE);
    else 
        map->map = malloc(sizeof(C_map *) * size);

    map->len = 0;
    map->max_len = DEF_MAP_SIZE;

    return map;
}

void map_add(MAP *map, char *key, char *value) {
    map->map[map->len] = malloc(sizeof(C_map *));
    map->map[map->len]->key = SMAL(strlen(key));
    map->map[map->len]->value = SMAL(strlen(value));

    strcpy(map->map[map->len]->key, key);
    strcpy(map->map[map->len]->value, value);

    map->len++;
    if (map->len >= map->max_len) {
        map->max_len >>= 1;
        map->map = realloc(map->map, sizeof(C_map *) * map->max_len);
    }
}

char *map_get_val(MAP *map, char *key) {
    int index = map_conteins_key(map, key);
    if (index == -1) {
        fprintf(stderr, "ERROR MAP: doesn't conteins this key in map");
        return NULL;
    }
    return map->map[index]->value;
}
 
int map_conteins_key(MAP *map, char *key) {
    for(int i = 0; i < map->len; i++) {
        if (!strcmp(map->map[i]->key, key)) {
            return i;
        }
    }
    return -1;
}

int map_conteins_value(MAP *map, char *value) {
    for(int i = 0; i < map->len; i++) {
        if (!strcmp(map->map[i]->value, value)) {
            return i;
        }
    }
    return -1;

}

void map_destroy(MAP *map) {
    for(int i = 0; i < map->len; i++) {
        free(map->map[i]);
    }

    free(map);
}


C_map *pars_val_from_config(char *str) {
    C_map *pair = malloc(sizeof(C_map *));

    char *key_buf = SMAL(50);
    char *val_buf = SMAL(50);
    memset(key_buf, 0, 50);
    memset(val_buf, 0, 50);

    for(int i = 0; i < strlen(str); i++) {
        key_buf[i] = str[i];
        if (str[i] == ':') {
            for (int j = 0, k = i; j < strlen(str); j++, k++) {
                val_buf[j] = str[k];
                if(str[k] == '\0' || str[k] == '\n') {
                    break;
                }
            }
            break;
        }
    }
    pair->key = SMAL(strlen(key_buf));
    pair->value = SMAL(strlen(val_buf));

    strcpy(pair->key, key_buf);
    strcpy(pair->value, val_buf);

    free(key_buf);
    free(val_buf);

    return pair;
}
