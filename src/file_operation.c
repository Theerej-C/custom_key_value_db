#include "file_operation.h"
#include <stdlib.h>
#include <stdio.h>
#include "hash_map.h"
int file_read(HashMap *h_m,char *file_name){
    FILE *file;
    file = fopen(file_name, "rb");
    if(!file){
        return 0;
    }
    while(1){
        int key_len,value_len;
        if(fread(&key_len, sizeof(int), 1, file)!=1) break;
        char* key = malloc(key_len+1);
        if(!key){
            fclose(file);
            return 0;
        }
        if(fread(key, sizeof(char), key_len, file)!=(unsigned int)key_len){
            free(key);
            fclose(file);
            return 0;
        }
        key[key_len] = '\0';
        fread(&value_len, sizeof(int), 1, file);
        char* value = malloc(value_len+1);
        if(!value){
            fclose(file);
            return 0;
        }
        if(fread(value,sizeof(char),value_len,file)!=(unsigned int)value_len){
            free(value);
            fclose(file);
            return 0;
        }
        value[value_len] = '\0';
        hash_map_set(h_m,key,value);
        free(key);
        free(value);
    }
    fclose(file);
    return 1;
}


int file_write(HashMap *h_m, char *file_name){
    FILE* file;
    file = fopen(file_name, "wb");
    if(!file){
        return 0;
    }
    int hash_map_size = h_m->size; 
    for(int i=0;i<hash_map_size;i++){
        Node* current_node = h_m->buckets[i];
        while(current_node){
            int key_len = current_node->key.size;
            int value_len = current_node->value.size;
            fwrite(&key_len, sizeof(int), 1, file);
            fwrite(current_node->key.value,sizeof(char),key_len,file);
            fwrite(&value_len, sizeof(int), 1, file);
            fwrite(current_node->value.value,sizeof(char),value_len,file);
            current_node = current_node->next;
        }
    }
    fclose(file);
    return 1;
}
