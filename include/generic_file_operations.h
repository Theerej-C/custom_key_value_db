#ifndef GENERIC_FILE_OPERATIONS_H
#define GENERIC_FILE_OPERATIONS_H
#include "hash_map.h"
int file_read_for_specific_key(String key, String *value);
int file_write_for_specific_key(String key, String value);
int file_line_delete(String key);
#endif
