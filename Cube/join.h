#pragma once
#include <string>
#include <string_view>
#include <ranges>

template <class Proj = std::identity>
std::string join(std::string_view separator, const std::ranges::range auto& range, Proj proj = {})
{
	using std::to_string;
	std::string result;
	for (auto it = range.begin(); it != range.end(); ++it)
	{
		if (it != range.begin())
			result += separator;
		result += to_string(proj(*it));
	}
	return result;
}
