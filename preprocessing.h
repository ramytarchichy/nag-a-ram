#pragma once

#include <stdlib.h>
#include <limits.h>

#include "common.h"


void preprocess_phrase (
    const char* anagram_phrase,
    size_t*     char_count,
    size_t      char_counts[UCHAR_MAX+1]
);

void preprocess_fingerprints(
    const unsigned char* data,
    size_t               data_size,
    
    size_t               anagram_size,
    size_t               anagram_chars[UCHAR_MAX+1],

    fingerprint_t**      fingerprint_list,
    size_t*              fingerprint_count,

    bucket_t**           fingerprint_hashtable,
    size_t*              hashtable_size
);

void ngrm_free(
    fingerprint_t* fp_list,
    size_t         fp_count,
    
    bucket_t*      fp_hashtable,
    size_t         hashtable_size
);
