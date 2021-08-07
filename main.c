#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#include "common.h"
#include "util.h"
#include "trustpilot.h"
#include "preprocessing.h"
#include "anagrams.h"

/*
 * Notes:
 * * I omited `malloc()` and `printf()` error checks because:
 *     1. if `malloc()` fails, chances are you have bigger problems to deal with anyway, such as your OS crashing soon.
 *     2. if `printf()` fails, you don't have I/O, in which case why are you running this in the first place?
 */

int main(int argc, const char** argv)
{
    const char* const in = "poultry outwits ants";
    const char* const wordlist_path = "wordlist.txt";
    const size_t min_size = 1;
    const size_t max_size = 4;//in_char_count;


    //Start timer
    const clock_t t_start = clock();

    
    //Read wordlist to memory for faster processing, since it's only a few hundred kilobytes
    unsigned char* file_text;
    size_t file_size;
    const int err_read = read_file_to_memory(wordlist_path, &file_text, &file_size);
    if (err_read != 0)
    {
        printf("Error: Could not read file \"%s\"\n", wordlist_path);
        return EXIT_FAILURE;
    }


    //Another timer
    const clock_t t_read = clock();


    //Count anagram letters
    size_t in_char_count = 0;
    size_t in_char_counts[UCHAR_MAX+1] = {0};
    preprocess_phrase(in, &in_char_count, in_char_counts);

    //Generate hash table and fingerprint list: O(n)
    fingerprint* fingerprint_list;
    size_t fingerprint_count = 0;
    bucket* fingerprint_hashtable;
    size_t hashtable_size;
    preprocess_fingerprints(
        file_text,
        file_size,

        in_char_count,
        in_char_counts,

        &fingerprint_list,
        &fingerprint_count,

        &fingerprint_hashtable,
        &hashtable_size
    );

    //Original text is now useless
    free(file_text);

    //Trustpilot data
    trustpilot_data data;
    trustpilot_preprocess(data.hashes);
    const clock_t t_pre = clock();
    data.t_pre = t_pre;

    //    PRE-PROCESSING COMPLETE
    printf("\n");
    printf("--=PRE-PROCESSING COMPLETE=--\n");
    printf("\n");
    printf("File Read      : %.0f ms\n", clock_diff_ms(t_start, t_read));
    printf("Pre-Processing : %.0f ms\n", clock_diff_ms(t_read, t_pre));
    printf("Fingerprints   : %lu\n", fingerprint_count);
    printf("\n");
    printf("  --=BEGINNING MAIN LOOP=-- \n");
    printf("\n");


    //Find anagrams
    anagrams_gen(
        min_size,
        max_size,

        in_char_count,
        in_char_counts,

        fingerprint_list,
        fingerprint_count,

        fingerprint_hashtable,
        hashtable_size,

        (callback_anagram)trustpilot_check,
        (void*)&data
    );


    //    ANAGRAM SEARCH COMPLETE
    printf("\nTotal Runtime: %.0f s\n", clock_diff_ms(t_pre, clock())/1000.0f);


    //Clean up
    ngrm_free(fingerprint_list, fingerprint_count, fingerprint_hashtable, hashtable_size);

    return EXIT_SUCCESS;
}
