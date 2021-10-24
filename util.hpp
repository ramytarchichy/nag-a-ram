#pragma once

#include <ctime>
#include <string>
#include <algorithm>


float clock_diff_ms(clock_t t_begin, clock_t t_end) noexcept;
std::string read_file(const std::string& file_path);


template <class T> //TODO: func
inline T sort_copy(T data)
{
    std::sort(std::begin(data), std::end(data));
    return data;
}


template <class T, class Func>
constexpr void for_split(
	const T& data,
	const typename T::value_type& delim,
	Func f
)
{
	for(
		typename T::const_iterator
			a = std::cbegin(data),
			b = std::find(std::next(a), std::cend(data), delim);
		
		a != std::cend(data);
		
		a = (b == std::cend(data)) ? std::cend(data) : std::next(b),
		b = (b == std::cend(data)) ?
			std::cend(data) : std::find(a, std::cend(data), delim)
	)
	{
		f(a, b);
	}
}


template <class T>
constexpr std::vector<T> split(
	const T& data,
	const typename T::value_type& delim
)
{
	std::vector<T> result;
	result.reserve(data.size());

	for_split(data, delim,
	[&](typename T::const_iterator a, typename T::const_iterator b)
	{
		result.emplace_back(a, b);
	});
	
	result.shrink_to_fit();
	return result;
}


template <class T>
int compare(const T& a, const T& b)
{
	if (a > b) return 1;
	if (a < b) return -1;
	return 0;
}


/*template <class It, class T, class Func>
It binary_find(It begin, It end, const T& val, Func f = compare<T>)
{
	//TODO
	const It pivot = begin + std::distance(begin, end) / 2;

	switch (f(*pivot, val))
	{
		case 0:
		return pivot;

		case -1: // *pivot < val
		return binary_find(, , val, f);

		case 1: // *pivot > val
		return binary_find(, , val, f);;
	}
}
*/