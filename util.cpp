#include "util.hpp"

#include <fstream>


float clock_diff_ms(clock_t t1, clock_t t2) noexcept
{
    return (static_cast<float>(t2 - t1) / CLOCKS_PER_SEC) * 1000.0f;
}


std::string read_file(const std::string& file_path)
{
	std::string str;
	std::ifstream file(file_path, std::ios::ate);
	str.resize(file.tellg());
	file.seekg(0);
	file.read(str.data(), str.size());
	return str;
}
