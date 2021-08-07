#include "anagrams.h"

#include <string.h>
#include <stdbool.h>

#include "util.h"


/*
 * /!\ WARNING - BEFORE YOU GET A HEART ATTACK:
 * 
 * I am well aware that I shouldn't put like 5 nested for loops as I did in
 * some of the functions below, and that I should split them into multiple
 * functions because they're so long they don't even fit on my vertical monitor,
 * but due to time constraints I recycled the whole thing from one of my earlier
 * proof of concept versions that I knew worked well, optimizing it as I went.
 */


static void swap(fingerprint** a, fingerprint** b)
{
    fingerprint* const tmp = *a;
    *a = *b;
    *b = tmp;
}

static void next_cmb(size_t* cmb, size_t cmb_size, size_t index, size_t fingerprint_count, bool* is_cmb_found)
{
    for (long i = index; i >= 0; --i)
    {
        if (cmb[i] < fingerprint_count-1)
        {
            ++cmb[i];
            *is_cmb_found = true;
            for (size_t x = i; x < cmb_size-1; ++x)
            {
                cmb[x] = cmb[i];
            }
            break;
        }
    }
}



static void anagram_word_permutations(fingerprint** prm, size_t cmb_size, size_t in_char_count, callback_anagram function, void* data)
{
    //Word Permutations
    size_t wrd[cmb_size];
    memset(wrd, 0, sizeof wrd);
    bool is_done = false;
    
    bool is_wrd_found = true;
    while(is_wrd_found)
    {
        is_wrd_found = false;

        for (size_t i = 0; i < cmb_size; ++i)
        {
            fingerprint* const fp = prm[i];

            if (!is_done) is_done = true;
            else ++wrd[i];

            if (wrd[i] < fp->words_size)
            {
                memset(wrd, 0, sizeof(size_t)*i);

                //Build anagram string
                const size_t len = in_char_count + cmb_size;
                char result[len];
                size_t last_index = 0;
                for (size_t j = 0; j < cmb_size; ++j)
                {
                    fingerprint* const fp = prm[j];
                    memcpy(&result[last_index], fp->words[wrd[j]], fp->len);
                    last_index += fp->len;
                    if (j < cmb_size-1) result[last_index++] = ' ';
                }
                result[last_index] = '\0';

                (*function)(result, len, data);

                is_wrd_found = true;
                break;
            }
        }
    }
}


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
)
{
    size_t cmb_max_size = min(in_char_count, max_size);
    size_t cmb[max_size];
    
    // Keep generating combinations of a specific length (in words) until there's none left,
    // at which point increase the size to make it longer and generate more combinations
    for (size_t cmb_size = min_size; cmb_size <= cmb_max_size; ++cmb_size)
    {
        memset(cmb, 0, sizeof(size_t)*cmb_size);
        bool is_cmb_found = true;
        while (is_cmb_found)
        {
            //Ckeck combination length in chatacters, and find a combination of the right
            //length if it's not valid
            size_t cmb_char_count;
            bool is_cmb_valid = false;
            while (!is_cmb_valid && is_cmb_found)
            {
                is_cmb_valid = true;

                cmb_char_count = 0;
                for (size_t i = 0; i < cmb_size-1; ++i)
                {
                    cmb_char_count += fingerprint_list[cmb[i]].len;
                    if (cmb_char_count >= in_char_count)
                    {
                        is_cmb_valid = false;
                        is_cmb_found = false;
                        next_cmb(cmb, cmb_size, i-1, fingerprint_count, &is_cmb_found);
                        break;
                    }
                }
            }

            if (is_cmb_valid)
            {
                //Make sure the combination doesn't have too many of any character
                size_t cmb_chars_used[UCHAR_MAX+1] = {0};
                for (size_t f = 0; f < cmb_size-1; ++f)
                {
                    fingerprint* fp = &fingerprint_list[cmb[f]];
                    for (size_t c = 0; c < fp->len; ++c)
                    {
                        if (++cmb_chars_used[fp->str[c]] > in_char_counts[fp->str[c]])
                        {
                            is_cmb_valid = false;
                            break;
                        }
                    }
                }

                if (is_cmb_valid)
                {
                    is_cmb_valid = false;

                    //Generate the last fingerprint from the leftover letters
                    size_t cmb_chars_left[UCHAR_MAX+1];
                    for (size_t c = 0; c <= UCHAR_MAX; ++c)
                    {
                        cmb_chars_left[c] = in_char_counts[c] - cmb_chars_used[c];
                    }
                    size_t f_size = in_char_count - cmb_char_count;
                    unsigned char f_str[f_size+1];
                    generate_fingerprint(cmb_chars_left, f_str);
                    
                    //Look for it in the hash table: O(1)
                    bucket* bucket = &fingerprint_hashtable[str_hash(f_str)%hashtable_size];
                    if (bucket->size > 0)
                    {
                        for (size_t f = 0; f < bucket->size; ++f)
                        {
                            fingerprint* fingerprint = bucket->fingerprints[f];
                            if (data_equal(fingerprint->len, f_size, fingerprint->str, f_str))
                            {
                                size_t fingerprint_index = fingerprint - fingerprint_list;
                                if(fingerprint_index <= cmb[0])
                                {
                                    cmb[cmb_size-1] = fingerprint_index;
                                    is_cmb_valid = true;
                                }
                                break;
                            }
                        }
                    }

                    if (is_cmb_valid)
                    {
                        //We no longer need to perform any checks, since the word arrangement
                        // and such won't affect the validity of the combination

                        //Convert `cmb[]` into a fingerprint array
                        fingerprint* prm[cmb_size];
                        for (size_t i = 0; i < cmb_size; ++i)
                        {
                            prm[i] = &fingerprint_list[cmb[i]];
                        }

                        //Generate fingerprint permutations using Heap's algorithm
                        size_t c[cmb_size];
                        memset(c, 0, sizeof c);

                        anagram_word_permutations(prm, cmb_size, in_char_count, function, data);

                        size_t i = 0;
                        while (i < cmb_size)
                        {
                            if  (c[i] < i)
                            {
                                if (i%2==0) swap(&prm[0], &prm[i]);
                                else        swap(&prm[c[i]], &prm[i]);

                                anagram_word_permutations(prm, cmb_size, in_char_count, function, data);

                                ++c[i];
                                i = 0;
                            }
                            else
                            {
                                c[i++] = 0;
                            }
                        }
                    }
                }
            }

            //Move to the next combination
            is_cmb_found = false;
            next_cmb(cmb, cmb_size, cmb_size-2, fingerprint_count, &is_cmb_found);
        }
    }
}
