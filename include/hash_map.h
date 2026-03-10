#include <stdbool.h>
#ifndef HASH_MAP_H
#define HASH_MAP_H
struct string {
  int size;
  char *value;
};
struct node {
  struct string key;
  struct string value;
  struct node *next;
};
struct hash_map {
  int size;
  struct node **buckets;
};
bool hash_map_get(struct hash_map *h_map, char *result, const char *key);
bool hash_map_set(struct hash_map *h_map, const char *key, const char *value);
int hash_function(int size, const char *key);
struct hash_map initialize_hashmap();
bool destroy_hash_map(struct hash_map h_m);
#endif
