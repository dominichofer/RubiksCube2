#include "binomial.h"

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
