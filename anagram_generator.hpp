#pragma once

#include <set>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

#include "word_group.hpp"
#include "combinator.hpp"
#include "vertical_permutator.hpp"

#include <iostream>


namespace nagaram
{
	template <class T>
	class anagram_generator
	{
	public:
		// `words` must not contain duplicates and must be sorted by length.
		// `k_min` and `k_max` must be >= 1
		anagram_generator
		(
			const T& sorted_phrase,
			const std::vector<T>& words,
			size_t k_min,
			size_t k_max
		)
		{
			// First stage:
			// pick words that might make valid anagrams based on length and
			// characters, group them based on their sorted values
			std::vector<std::unique_ptr<word_group<T>>> word_group_vector;
			std::vector<size_t> lengths;
			{
				std::unordered_map<T, word_group<T>&> word_group_map;

				for (const T& word : words)
				{
					// The rest of the words are too long, skip them.
					if (word.size() > sorted_phrase.size())
						break;
					
					// Check character count
					T sorted_word = sort_copy(word);
					bool is_valid = true;
					auto it = sorted_phrase.cbegin();
					for (const auto& c : sorted_word)
					{
						it = std::find(it, sorted_phrase.cend(), c);
						if (it == sorted_phrase.cend())
						{
							is_valid = false;
							break;
						}
						++it;
					}
					
					// Word contains characters that are not in the phrase, skip
					if (!is_valid)
						continue;
					
					// Keep track of word lengths
					if (lengths.size() == 0 || lengths.back() != word.size())
					{
						lengths.push_back(word.size());
						word_group_map.clear();
					}

					// Add word to word_group
					if (
						const auto it = word_group_map.find(sorted_word);
						it != word_group_map.end()
					)
					{
						it->second.words.push_back(word);
					}
					else
					{
						word_group_vector.push_back(
							std::make_unique<word_group<T>>(
								sorted_word,
								std::vector<T>{word}
							)
						);

						word_group_map.emplace(
							sorted_word,
							*(word_group_vector.back())
						);
					}
				}
			}

			// Second stage:
			// Group word_groups based on their word lengths
			
		}


		bool next_anagram() const
		{
			
		}


		/*std::vector<> get_anagram() const
		{

		}*/


	private:
		//combinator<> cmb_len;

		/*std::vector<size_t> lengths;
		std::unordered_map<T, word_group<T>> wordgroup_map;
		std::unordered_map<size_t, std::vector<word_group<T>&>> length_map;*/
	};
}
