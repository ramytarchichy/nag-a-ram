#pragma once

#include <stdlib.h>
#include <limits.h>

#include "common.h"

typedef void (*callback_anagram)(char*, size_t, void*);

void anagrams_gen(
    size_t             min_size,
    size_t             max_size,
    
    size_t             in_char_count,
    size_t             in_char_counts[UCHAR_MAX+1],

    fingerprint*     fingerprint_list,
    size_t             fingerprint_count,

    bucket*          fingerprint_hashtable,
    size_t             hashtable_size,

    callback_anagram function,
    void*              data
);
