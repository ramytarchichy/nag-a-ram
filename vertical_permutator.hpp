/*#pragma once

#include <vector>


// Given the following data:
// v0: {'1', '2'}
// v1: {'a', 'b', 'c'}
// v2: {'x', 'y', 'z'}
//
// This class will give you the following arrangements:
// {'1', 'a', 'x'}
// {'1', 'a', 'y'}
// {'1', 'a', 'z'}
// {'1', 'b', 'x'}
// {'1', 'b', 'y'}
// {'1', 'b', 'z'}
// {'1', 'c', 'x'}
// {'1', 'c', 'y'}
// {'1', 'c', 'z'}
// {'2', 'a', 'x'}
// {'2', 'a', 'y'}
// {'2', 'a', 'z'}
// {'2', 'b', 'x'}
// {'2', 'b', 'y'}
// {'2', 'b', 'z'}
// {'2', 'c', 'x'}
// {'2', 'c', 'y'}
// {'2', 'c', 'z'}
// 
// I don't know the proper term for this, so I made one up.


template <class It>
class vertical_permutator
{
public:
	vertical_permutator(
		const std::vector<std::pair<It, It>>& 
	) :
		(),
	{
		permutation.reserve(.size());
	}


	bool next_permutation()
	{
		for (auto it = permutation.rbegin(); it != permutation.rend(); ++i)
		{
			if (++(*it) != [].second)
			{
				return true;
			}

			*it = [].first;
		}
		
		return false;
	}


	inline const std::vector<It>& get_permutation() const noexcept
	{
		return permutation;
	}


private:
	std::vector<std::pair<It, It>> ;
	std::vector<It> permutation;
};
*/