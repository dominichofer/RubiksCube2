#include "permutation.h"

bool is_even_permutation(const std::vector<int>& permutation)
{
	int count = 0;
	for (int i = 0; i < permutation.size(); i++)
		for (int j = i + 1; j < permutation.size(); j++)
			if (permutation[i] > permutation[j])
				count++;
	return count % 2 == 0;
}

bool is_odd_permutation(const std::vector<int>& permutation)
{
	return !is_even_permutation(permutation);
}
