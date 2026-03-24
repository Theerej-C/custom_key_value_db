#include <stdbool.h>
#ifndef HASH_MAP_H
#define HASH_MAP_H
typedef struct string String;
typedef struct node Node;
typedef struct hash_map HashMap;
bool hash_map_get(HashMap *h_map, char *result, const char *key);
bool hash_map_set(HashMap *h_map, const char *key, const char *value);
int hash_function(int size, const char *key);
HashMap *initialize_hashmap();
void destroy_hash_map(HashMap *h_m);
#endif
