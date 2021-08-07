#include "trustpilot.h"

#include <stdio.h>
#include <string.h>


void trustpilot_check(const char* anagram, size_t anagram_size, void* data)
{
    //MD5 hash
    unsigned char hash[MD5_HASH_SIZE];
    md5_hash((unsigned char*)anagram, anagram_size-1, hash);

    //Check and output
    const bool easy   = data_equal(MD5_HASH_SIZE, MD5_HASH_SIZE, hash, ((trustpilot_data*)data)->hashes[0]);
    const bool medium = data_equal(MD5_HASH_SIZE, MD5_HASH_SIZE, hash, ((trustpilot_data*)data)->hashes[1]);
    const bool hard   = data_equal(MD5_HASH_SIZE, MD5_HASH_SIZE, hash, ((trustpilot_data*)data)->hashes[2]);

    if (easy || medium || hard)
    {
        const clock_t t_pre = ((trustpilot_data*)data)->t_pre;

        const char* difficulty;
        if      (easy)   difficulty = "EASY  ";
        else if (medium) difficulty = "MEDIUM";
        else if (hard)   difficulty = "HARD  ";

        printf("[T+%.2fs] %s : %s\n", clock_diff_ms(t_pre, clock())/1000, difficulty, anagram);
    }
}


void trustpilot_preprocess(unsigned char hashes[3][MD5_HASH_SIZE])
{
    const char hash_hex[3][MD5_HASH_SIZE*2] = {
        "e4820b45d2277f3844eac66c903e84be",
        "23170acc097c24edb98fc5488ab033fe",
        "665e5bcb0c20062fe8abaaf4628bb154"
    };
    for (size_t i = 0; i < 3; ++i)
    {
        const char* pos = hash_hex[i];
        for (size_t j = 0; j < MD5_HASH_SIZE; ++j)
        {
            sscanf(pos, "%2hhx", &hashes[i][j]);
            pos += 2;
        }
    }
}
