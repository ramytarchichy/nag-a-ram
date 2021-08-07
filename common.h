#pragma once

#include <stdlib.h>
#include <limits.h>


typedef struct
{
    size_t         len;
    unsigned char* str;
    unsigned char* fingerprint;
    size_t         hash;
} preprocessed_word;


typedef struct fingerprint
{
    size_t                 len;
    unsigned char*         str;
    size_t                 words_size;
    unsigned char**        words;
    struct fingerprint**   address;
} fingerprint;


typedef struct
{
    size_t          size;
    fingerprint** fingerprints;
} bucket;


void generate_fingerprint(const size_t in[UCHAR_MAX+1], unsigned char* out);
