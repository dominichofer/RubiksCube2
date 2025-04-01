#pragma once
#include <cstdint>
#include <ranges>
#include <vector>

// Returns the binomial coefficient "n choose k".
constexpr uint64_t binomial(uint64_t n, uint64_t k)
{
	if (k > n)
		return 0;
	if (k == 0 or k == n)
		return 1;
	if (k > n - k)
		k = n - k;

	uint64_t result = 1;
	for (uint64_t i = 0; i < k; ++i)
	{
		if ((n - i) % (i + 1) == 0)
			result *= (n - i) / (i + 1);
		else if (result % (i + 1) == 0)
			result = result / (i + 1) * (n - i);
		else
			result = result * (n - i) / (i + 1);
	}
	return result;
}

// Returns the index of the combination
// in the lexicographically sorted list of all possible
// combinations of n elements taken k at a time.
template <std::ranges::random_access_range R>
uint64_t combination_index(uint64_t n, R&& combination)
{
	uint64_t index = 0;
	uint64_t j = 0;
	uint64_t k = std::ranges::size(combination);
	for (uint64_t i = 0; i < k; ++i)
		for (++j; j < combination[i] + 1; ++j)
			index += binomial(n - j, k - i - 1);
	return index;
}

// Returns the index-th combination of n elements taken k at a time.
std::vector<int> nth_combination(uint64_t n, uint64_t k, uint64_t index);
