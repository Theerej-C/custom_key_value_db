#include "hash_map.h"
#include <stdlib.h>
#include <string.h>
#include "basic_types.h"
HashMap * initialize_hashmap(){
    HashMap *h_m = malloc(sizeof(HashMap));
    if(!h_m){
        return NULL;
    }
    h_m->size = 4;
    Node **buckets = malloc(4*sizeof(Node*));
    if(!buckets){
        free(h_m);
        return NULL;
    }
    for(int i=0;i<4;i++){
        buckets[i] = NULL;
    }
    h_m->buckets = buckets;
    return h_m;
}
void destroy_hash_map(HashMap * h_m){
    for (int i = 0; i < h_m->size; i++) {
        Node *current = h_m->buckets[i];
        while (current) {
            Node *temp = current;
            current = current->next;
            free(temp->key.value);
            free(temp->value.value);
            free(temp);
        }
    }
    free(h_m->buckets);
    free(h_m);
}

int hash_function(int size, const char *key){
    int hash = 0;
    ul key_length = strlen(key);
    for(ul i=0;i<key_length;i++){
         hash = hash * 31 + key[i]; 
    }
    return hash%size;
}
bool hash_map_get(HashMap *h_map, char *result, const char *key){
    if(!h_map) return false;
    int hash = hash_function(h_map->size, key); 
    Node* bucket = h_map->buckets[hash];
    while(bucket){
        if(strcmp(bucket->key.value,key)==0){
            strncpy(result, bucket->value.value,bucket->value.size+1);
            return true;
        }
        bucket = bucket->next;
    } 
   return false; 
}

bool hash_map_set(HashMap *h_map, const char *key, const char *value){
    if(!h_map) return false;
    int hash = hash_function(h_map->size, key);  // need to implement hash function
    Node* bucket = h_map->buckets[hash];
    char *key_copy = strdup(key);
    char *value_copy = strdup(value);
    if(!key_copy||!value_copy){
        return false;
    }
    String key_string = {strlen(key_copy),key_copy};
    String key_value = {strlen(value_copy),value_copy};
    Node *new_node = malloc(sizeof(struct node));
    if(!new_node){
        return false;
    }
    new_node->next = NULL;
    new_node->key = key_string;
    new_node->value = key_value;
    if(bucket){
        while (bucket) {
            if (strcmp(bucket->key.value, key) == 0) {
                free(bucket->value.value);
                char* value_copy = strdup(value);
                if(!value_copy) return false;
                bucket->value.value = value_copy;
                bucket->value.size = strlen(value_copy);
                return true;
            }
            if (bucket->next == NULL) break;
            bucket = bucket->next;
        }
        bucket->next = new_node;
    }
    else{
       h_map->buckets[hash] = new_node;
    }
    return true;
}
