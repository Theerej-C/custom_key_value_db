#include "generic_file_operations.h"
#include "hash_map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int file_read_for_specific_key(String key, String *value_return){
    FILE* file;
    file = fopen("db.txt","rb");
    char buffer[256];
    if(!file){
        perror("File not found error");
        exit(0);
    }
    while(fgets(buffer, sizeof(buffer), file)){
       if(strcmp(buffer, key.value)){
            char* token = strtok(buffer, " ");
            char* final_char = NULL;
            while(!token){
                final_char = token;                
                token = strtok(NULL, " ");
            }
            value_return->size = sizeof(final_char);
            value_return->value = final_char; 
            return 1;
       } 
    }
    return 0;
}

int file_write_for_specific_key(String key, String value_inp){
    FILE* file;
    file = fopen("db.txt", "a");
    char* final_out = key.value;
    strcat(final_out," ");
    strcat(final_out, value_inp.value);
    fprintf(file, "%s",final_out); 
    return 0;

} 
