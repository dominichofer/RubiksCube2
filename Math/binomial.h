#pragma once
#include <cstdint>
#include <ranges>
#include <vector>

namespace
{
	// Lookup table for binomial coefficients.
	// The table is filled with the values of "n choose k" for n = 0 to 12 and k = 0 to n.
	static std::array<std::array<int64_t, 13>, 13> binomial_lookup = [] {
		std::array<std::array<int64_t, 13>, 13> table{};
		for (int64_t n = 0; n <= 12; ++n) {
			table[n][0] = 1;
			for (int64_t k = 1; k <= n; ++k) {
				table[n][k] = table[n - 1][k - 1] + table[n - 1][k];
			}
		}
		return table;
		}();
}

// Returns the binomial coefficient "n choose k".
constexpr int64_t binomial(int64_t n, int64_t k)
{
    if (n <= 12)
        return binomial_lookup[n][k];
    
    if (k > n)
        return 0;
    if (k == 0 or k == n)
        return 1;
    if (k > n - k)
        k = n - k;

    int64_t result = 1;
    for (int64_t i = 0; i < k; ++i)
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
int64_t combination_index(int64_t n, R&& combination)
{
	int64_t index = 0;
	int64_t j = 0;
	int64_t k = std::ranges::size(combination);
	for (int64_t i = 0; i < k; ++i)
		for (++j; j < combination[i] + 1; ++j)
			index += binomial(n - j, k - i - 1);
	return index;
}

// Returns the index-th combination of n elements taken k at a time.
std::vector<int8_t> nth_combination(int8_t n, int8_t k, int64_t index);

template <int8_t k>
std::array<int8_t, k> nth_combination(int8_t n, int64_t index)
{
	std::array<int8_t, k> combination;
	int8_t size = 0;
	for (int8_t i = 0; i < n; ++i)
	{
		int64_t count = binomial(n - 1 - i, k - size - 1);
		if (count > index)
		{
			combination[size++] = i;
			if (size == k)
				return combination;
		}
		else
			index -= count;
	}
}