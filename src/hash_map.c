#include "hash_map.h"
#include <stdlib.h>
#include <string.h>
#include "basic_types.h"
struct hash_map initialize_hashmap(){
    struct hash_map h_m;
    h_m.size = 4;
    h_m.buckets = calloc(h_m.size,sizeof(struct node));
    return h_m;
}
bool destroy_hash_map(struct hash_map h_m){
    free(h_m.buckets);
    return true;
}

int hash_function(int size, const char *key){
    int hash = 0;
    for(ul i=0;i<strlen(key);i++){
        hash += (int) (key[i]-'0');
    }
    return hash%size;
}
bool hash_map_get(struct hash_map *h_map, char *result, const char *key){
    int hash = hash_function(h_map->size, key); 
    struct node* bucket = h_map->buckets[hash];
    while(bucket){
        if(strcmp(bucket->key.value,key)==0){
            strcpy(result, bucket->value.value);
            return true;
            break;
        }
        bucket = bucket->next;
    } 
   return false; 
}

bool hash_map_set(struct hash_map *h_map, const char *key, const char *value){
    int hash = hash_function(h_map->size, key);  // need to implement hash function
    struct node* bucket = h_map->buckets[hash];
    struct string key_string = {strlen(key),(char *)key};
    struct string key_value = {strlen(value),(char *)value};
    struct node *new_node = malloc(sizeof(struct node));
    new_node->next = NULL;
    new_node->key = key_string;
    new_node->value = key_value;
    if(bucket){
        while(bucket->next!=NULL){
            bucket = bucket->next;
        }
        bucket->next = new_node;
    }
    else{
       bucket = new_node; 
    }
    return true;
}
