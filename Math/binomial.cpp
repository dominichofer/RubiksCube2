#include "binomial.h"

uint64_t binomial(uint64_t n, uint64_t k)
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

uint64_t combination_index(uint64_t n, const std::vector<int>& combination)
{
	uint64_t index = 0;
	uint64_t j = 0;
	uint64_t k = combination.size();
	for (uint64_t i = 0; i < k; ++i)
		for (++j; j < combination[i] + 1; ++j)
			index += binomial(n - j, k - i - 1);
	return index;
}

std::vector<int> nth_combination(uint64_t n, uint64_t k, uint64_t index)
{
	std::vector<int> combination;
	combination.reserve(k);
	uint64_t remaining = k;
	uint64_t start = 0;
	while (remaining > 0)
	{
		for (uint64_t i = start; i < n; ++i)
		{
			uint64_t count = binomial(n - (i + 1), remaining - 1);
			if (count > index)
			{
				combination.push_back(i);
				start = i + 1;
				--remaining;
				break;
			}
			else
				index -= count;
		}
	}
	return combination;
}
