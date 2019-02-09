#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MD5_HASH_SIZE 16U

bool   data_equal          (size_t a_len, size_t b_len, const unsigned char* a, const unsigned char* b);
size_t str_hash            (const unsigned char* str);
float  clock_diff_ms       (clock_t t1, clock_t t2);
size_t min                 (size_t a, size_t b);
int    read_file_to_memory (const char* file_path, unsigned char** data, size_t* size);
void   md5_hash            (const unsigned char* data, size_t data_size, unsigned char* hash);

