#pragma once

#include <vector>
#include <ranges>
#include <iterator>


// k-combination with repetition
// https://en.wikipedia.org/wiki/Combination

template <class It>
class combinator
{
public:
	combinator(
		It begin,
		It end,
		size_t k_min,
		size_t k_max
	) :
		begin(begin),
		end(end),
		k_min(k_min),
		k_max(k_max)
	{
		iterators.reserve(k_max);

		for (size_t i = 1; i < k_min; ++i)
		{
			iterators.push_back(end);
		}
	}


	bool next_combination(size_t skip = 0)
	{
		//Next combination
		for (
			auto it = iterators.rbegin() + skip;
			it != iterators.rend();
			++it
		)
		{
			//std::cout << "i" << std::endl;
			if (*it != end && ++(*it) != end)
			{
				for (
					auto it_b = iterators.begin() + (
						iterators.size() -
						std::distance(iterators.rbegin(), it)
						);
					it_b != iterators.end();
					++it_b
				)
				{
					*it_b = *it;
				}

				//std::cout << "a" << std::endl;
				return true;
			}
		}

		// E X P A N D
		if (iterators.size() < k_max)
		{
			for (It& it : iterators)
				it = begin;

			iterators.push_back(begin);

			//std::cout << "b" << std::endl;
			return true;
		}
		
		//Exhausted combinations
		return false;
	}


	inline const std::vector<It>& get_combination() const noexcept
	{
		return iterators;
	}


private:
	It begin;
	It end;
	size_t k_min;
	size_t k_max;

	std::vector<It> iterators;
};
