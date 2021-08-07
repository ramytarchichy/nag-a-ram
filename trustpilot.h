#pragma once

#include <stdlib.h>
#include "util.h"

typedef struct
{
    unsigned char hashes[3][MD5_HASH_SIZE];
    clock_t       t_pre;
} trustpilot_data;

void trustpilot_check      (const char* anagram, size_t anagram_size, void* data);
void trustpilot_preprocess (unsigned char hashes[3][MD5_HASH_SIZE]);
