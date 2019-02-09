#pragma once

#include <stdlib.h>
#include <limits.h>


typedef struct
{
    size_t         len;
    unsigned char* str;
    unsigned char* fingerprint;
    size_t         hash;
} word_t;


typedef struct fingerprint_t
{
    size_t                 len;
    unsigned char*         str;
    size_t                 words_size;
    unsigned char**        words;
    struct fingerprint_t** address;
} fingerprint_t;


typedef struct
{
    size_t          size;
    fingerprint_t** fingerprints;
} bucket_t;


void generate_fingerprint(const size_t in[UCHAR_MAX+1], unsigned char* out);
