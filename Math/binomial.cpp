#include "binomial.h"

std::vector<int8_t> nth_combination(int8_t n, int8_t k, int64_t index)
{
	std::vector<int8_t> combination;
	combination.reserve(k);
	int8_t remaining = k;
	int8_t start = 0;
	while (remaining > 0)
	{
		for (int8_t i = start; i < n; ++i)
		{
			int64_t count = binomial(n - (i + 1), remaining - 1);
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
