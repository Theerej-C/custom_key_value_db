#include <stdbool.h>
#ifndef HASH_MAP_H
#define HASH_MAP_H
struct string {
  int size;
  char *value;
};
typedef struct string String;
typedef struct node Node;
struct node {
  String key;
  String value;
  Node *next;
};
struct hash_map {
  int size;
  Node **buckets;
};
typedef struct hash_map HashMap;
bool hash_map_get(HashMap *h_map, char *result, const char *key);
bool hash_map_set(HashMap *h_map, const char *key, const char *value);
int hash_function(int size, const char *key);
HashMap *initialize_hashmap();
void destroy_hash_map(HashMap *h_m);
#endif
