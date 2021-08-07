#include "util.h"

#include <string.h>
#include <stdio.h>
#include <openssl/md5.h>


bool data_equal(size_t a_len, size_t b_len, const unsigned char* a, const unsigned char* b)
{
    if (a_len != b_len)
    {
        return false;
    }
    else
    {
        for (size_t i = 0; i < a_len; ++i)
        {
            if(a[i] != b[i]) return false;
        }

        return true;
    }
}

//djb2
size_t str_hash(const unsigned char* str)
{
    size_t hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}


float clock_diff_ms(clock_t t1, clock_t t2)
{
    return ((float)(t2 - t1) / CLOCKS_PER_SEC) * 1000;
}


size_t min(size_t a, size_t b)
{
    return (a < b) ? a : b;
}


int read_file_to_memory(const char* file_path, unsigned char** data, size_t* size)
{
    //Open wordlist in read-only mode
    FILE* const file = fopen(file_path, "rb");
    if (file == NULL) return -1;

    //Get size
    {
        const int error = fseek(file, 0L, SEEK_END);
        if (error != 0) return -1;
    }

    const size_t s = ftell(file);
    if (s == -1L) return -1;

    rewind(file);

    //Save file contents to memory
    *size = s;
    *data = malloc(s * sizeof **data);

    const size_t ret = fread(*data, 1, s, file);
    if (ret != s) return -1;

    //Wordlist is saved in memory, we can now close the file
    {
        const int error = fclose(file);
        if (error != 0) return -1;
    }

    return 0;
}


void md5_hash(const unsigned char* data, size_t data_size, unsigned char* hash)
{
    MD5_CTX c;
    MD5_Init(&c);
    MD5_Update(&c, data, data_size);
    MD5_Final(hash, &c);
}
