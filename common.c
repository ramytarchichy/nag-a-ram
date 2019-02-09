#include "common.h"

#include <string.h>


void generate_fingerprint(const size_t in[UCHAR_MAX+1], unsigned char* out)
{
    size_t k = 0;
    for (size_t c = 0; c <= UCHAR_MAX; ++c)
    {
        memset(&out[k], c, in[c]);
        k += in[c];
    }
    //Null-terminate it
    out[k] = '\0';
}
