#include "basic_types.h"
#include "hash_map.h"
#include <stdio.h>
int main(){
    char string[100];
    char key[100];
    printf("Key: ");
    scanf("%99s", key);  // reads a single word into key

    printf("Value: ");
    scanf("%99s", string); // reads a single word into string
    HashMap* h_map = initialize_hashmap();
    hash_map_set(h_map, key, string);
    char buff[100];
    hash_map_get(h_map, buff, (const char*) key);
    printf("%s",buff);
    return 0;
}
