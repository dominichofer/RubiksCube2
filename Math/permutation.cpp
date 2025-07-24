#include "permutation.h"

bool is_even_permutation(uint64_t lexicographical_index)
{
	// Convert the index to its factoradic representation and sum the digits.
	int sum = 0;
	for (unsigned int i = 2; lexicographical_index > 0; i++)
	{
		sum += lexicographical_index % i;
		lexicographical_index /= i;
	}
	return sum % 2 == 0;
}

bool is_odd_permutation(uint64_t lexicographical_index)
{
	return not is_even_permutation(lexicographical_index);
}
