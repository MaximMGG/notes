#include <stdlib.h>

#define SMAL(a) malloc(sizeof(char) * a)
#define boolean char

#define true 1
#define false 0

typedef struct {
    char *key;
    char *value;
} C_map;

typedef struct {
    C_map *map;
    unsigned int len;
} MAP;

typedef struct {
    char *login;
} N_config;

//start MAP func
MAP *map_init(unsigned int size);

//add key, and value in map
void map_add(char *key, char *value);

//return value byu *key
char *map_get_val(char *key);

//if map conteins *key return index of key position
//return -1 if not conteins that *key
int map_conteins_key(char *key);

//if map conteins *value, return index of value position
//return -1 if not conteins that *value
int map_conteins_value(char *value);

//free all mamory in map
void *map_destroy(MAP *map);

//end MAP func

char *str_sub(char *tar, int from, int to);
