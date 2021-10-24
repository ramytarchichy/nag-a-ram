#include <ctime>
#include <string>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <string_view>

#include "md5.hpp"
#include "util.hpp"
#include "anagram_generator.hpp"

using namespace nagaram;


int main()
{
	//TODO: C++20: constexpr strings
    const std::string phrase = "poultry outwits ants";
    const std::string wordlist_path = "wordlist.txt";
    constexpr size_t min_size = 3;
    constexpr size_t max_size = 4;
    
    /*constexpr std::array<md5_result, 3> hashes = []() {
    	//TODO
    	std::array<std::string, 3> h {
    		"",
    		"",
    		""
    	};
    	
    	return res;
    }();*/

    const clock_t t_start = clock();
    
    // Read and parse wordlist
	std::vector<std::string> wordlist = split(read_file(wordlist_path), '\n');

    const clock_t t_read = clock();
    
    // Preprocessing
    
    std::string phrase_baked = sort_copy(phrase);
	phrase_baked.erase(
		std::remove_if(
			phrase_baked.begin(),
			phrase_baked.end(),
			[](char c)
			{
				return c == ' ';
			}
		),
		phrase_baked.cend()
	);

	// Deduplicate

	// The wordlist just so happens to be sorted in lexicographical order,
	// meaning we can remove duplicates in O(N) very efficiently before even
	// sorting, meaning there will be fewer items to sort later, meaning we
	// shave off an extra few hundred microseconds of runtime.

	// If we were given an unsorted wordlist, we would first sort by length and
	// lexicographical order, and then deduplicate.
	const auto it = std::unique(wordlist.begin(), wordlist.end());
	wordlist.resize(std::distance(wordlist.begin(), it));
	wordlist.shrink_to_fit();

	// Prepare wordlist for baking

	// Sorting by length is required for preprocessing
	std::sort(wordlist.begin(), wordlist.end(),
	[](const std::string& a, const std::string& b) {
		return a.size() < b.size();

		// Sorting further by lexicographical order allows for linear
		// deduplication, which we already did. But if the wordlist was not
		// sorted lexicographically, we would use this instead:
		//return (a.size() == b.size()) ? a < b : (a.size() < b.size());
	});

	const clock_t t_preprocessing = clock();

    // Generate baked wordlist data for this specific phrase
    anagram_generator<std::string> anagrams(
		phrase_baked,
		wordlist,
		min_size,
		max_size
	);

	//const clock_t t_preprocessing = clock();

	std::cout << wordlist.size() << '\n';
	std::cout << "Prep: " << clock_diff_ms(t_read, t_preprocessing) << std::endl;
	std::cout << "Read: " << clock_diff_ms(t_start, t_read) << std::endl;

	// Check anagrams

	//TODO
	//while()
	{
		
	}
	
	const clock_t t_end = clock();

	// Output
	
	//TODO

    return EXIT_SUCCESS;
}
