#include "preprocessing.h"

#include <stdbool.h>
#include <string.h>

#include "util.h"


int compare_fingerprint(const void* fp1, const void* fp2) 
{
    fingerprint_t* f1 = (fingerprint_t*)fp1;
    fingerprint_t* f2 = (fingerprint_t*)fp2;
    if (f1->len > f2->len) return  1;
    if (f1->len < f2->len) return -1;
    int a = strcmp((char*)f1->str, (char*)f2->str);
    if (a > 0) return 1;
    if (a < 0) return -1;
    return 0;
}

void preprocess_phrase(const char* anagram_phrase, size_t* char_count, size_t char_counts[UCHAR_MAX+1])
{
    char c;
    while((c = *anagram_phrase++))
    {
        if (c != ' ')
        {
            ++*char_count;
            ++char_counts[c];
        }
    }
}


void preprocess_fingerprints(
    const unsigned char* data,
    size_t               data_size,
    
    size_t               anagram_size,
    size_t               anagram_chars[UCHAR_MAX+1],

    fingerprint_t**      fingerprint_list,
    size_t*              fingerprint_count,

    bucket_t**           fingerprint_hashtable,
    size_t*              hashtable_size
)
{
    //We won't actually get that many words, we will reallocate later
    word_t* wordlist = malloc(data_size * sizeof *wordlist);
    size_t word_count = 0;

    //Get valid words: O(n)
    bool is_newline = true;
    bool is_valid   = true;
    size_t char_count = 0;
    size_t char_counts[UCHAR_MAX+1] = {0};

    for (size_t i = 0; i < data_size; ++i)
    {
        unsigned char character = data[i];
        if (character == '\n' || character == '\r' || i == data_size-1)
        {
            if (!is_newline)
            {
                /*
                 *Assuming the wordlist is sorted alphabetically, we can assume that duplicates
                 * (if any exist) have to be consecutive, and therefore can be eliminated by
                 * checking the previous word.
                 */
                if (word_count > 0)
                {
                    word_t* prev_word = &wordlist[word_count-1];
                    is_valid &= !data_equal(char_count, prev_word->len, &data[i-char_count], prev_word->str);
                }

                if (is_valid)
                {
                    word_t* word = &wordlist[word_count];
                    word->len = char_count;

                    //Copy word
                    word->str = malloc(char_count+1);
                    memcpy(word->str, &data[i-char_count], char_count);
                    //And null-terminate it
                    word->str[char_count] = 0;

                    //Generate fingerprint
                    word->fingerprint = malloc(char_count+1);
                    generate_fingerprint(char_counts, word->fingerprint);

                    //And hash it
                    word->hash = str_hash(word->fingerprint);

                    ++word_count;
                }
                is_newline = true;
                is_valid = true;
                char_count = 0;
                memset(char_counts, 0, sizeof char_counts);
            }
        }
        else if (is_valid)
        {
            ++char_count;
            if (++char_counts[character] > anagram_chars[character] || char_count > anagram_size)
                is_valid = false;
            is_newline = false;
        }
    }


    //Put the fingerprints in a list and a hashtable: O(n)
    *fingerprint_list = malloc(word_count * sizeof **fingerprint_list);
    size_t fp_c = 0;

    for (size_t i = 0; i < word_count; ++i)
    {
        (*fingerprint_list)[i].words = malloc(sizeof(unsigned char*)*word_count);
    }

    const size_t ht_s = word_count * 2;
    *hashtable_size = ht_s;

    *fingerprint_hashtable = calloc(ht_s, sizeof **fingerprint_hashtable);
    for (size_t i = 0; i < ht_s; ++i)
    {
        (*fingerprint_hashtable)[i].fingerprints = malloc(sizeof(fingerprint_t)*word_count);
    }

    for (size_t w = 0; w < word_count; ++w)
    {
        bool is_found_in_bucket = false;
        const word_t* word = &wordlist[w];
        bucket_t* bucket = &(*fingerprint_hashtable)[word->hash%ht_s];
        for (size_t f = 0; f < bucket->size; ++f)
        {
            fingerprint_t* fingerprint = bucket->fingerprints[f];
            if (data_equal(fingerprint->len, word->len, fingerprint->str, word->fingerprint))
            {
                is_found_in_bucket = true;
                fingerprint->words[fingerprint->words_size++] = word->str;
                free(word->fingerprint);
                break;
            }
        }
        
        if (!is_found_in_bucket)
        {
            fingerprint_t* fingerprint = &(*fingerprint_list)[fp_c++];
            fingerprint->len = word->len;
            fingerprint->str = word->fingerprint;
            fingerprint->words_size = 1;
            fingerprint->words[0] = word->str;

            bucket->fingerprints[bucket->size] = fingerprint;

            fingerprint->address = &bucket->fingerprints[bucket->size];

            ++bucket->size;
        }
    }

    //Fingerprint Count
    *fingerprint_count = fp_c;

    //Reclaim some memory
    free(wordlist);
    for (size_t i = 0; i < word_count; ++i)
    {
        (*fingerprint_list)[i].words = realloc((*fingerprint_list)[i].words, sizeof(unsigned char*) * (*fingerprint_list)[i].words_size);
    }
    *fingerprint_list = realloc(*fingerprint_list, fp_c * sizeof **fingerprint_list);
    for (size_t i = 0; i < ht_s; ++i)
    {
        if ((*fingerprint_hashtable)[i].size == 0)
        {
            free((*fingerprint_hashtable)[i].fingerprints);
        }
    }

    // Sort fingerprints by length: O(n log n)
    // (and no, I didn't implement my own sorting algorithm)
    qsort(*fingerprint_list, fp_c, sizeof **fingerprint_list, compare_fingerprint);

    //Update the addresses: O(n)
    for (size_t i = 0; i < fp_c; ++i)
    {
        *((*fingerprint_list)[i].address) = &(*fingerprint_list)[i];
    }
}


void ngrm_free(
    fingerprint_t* fp_list,
    size_t         fp_count,
    
    bucket_t*      fp_hashtable,
    size_t         hashtable_size
)
{
    //List and elements
    for (size_t i = 0; i < fp_count; ++i)
    {
        for (size_t j = 0; j < fp_list[i].words_size; ++j)
        {
            free(fp_list[i].words[j]);
        }
        free(fp_list[i].str);
        free(fp_list[i].words);
    }
    free(fp_list);

    //Hashtable and elements
    for (size_t i = 0; i < hashtable_size; ++i)
    {
        if (fp_hashtable[i].size != 0)
        {
            free(fp_hashtable[i].fingerprints);
        }
    }
    free(fp_hashtable);
}
