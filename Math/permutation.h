#pragma once
#include <array>
#include <bit>
#include <cstdint>
#include <vector>

constexpr uint64_t factorial(uint64_t n)
{
	switch (n)
	{
	case 0: return 1;
	case 1: return 1;
	case 2: return 2;
	case 3: return 6;
	case 4: return 24;
	case 5: return 120;
	case 6: return 720;
	case 7: return 5040;
	case 8: return 40320;
	case 9: return 362880;
	case 10: return 3628800;
	case 11: return 39916800;
	case 12: return 479001600;
	case 13: return 6227020800;
	case 14: return 87178291200;
	case 15: return 1307674368000;
	case 16: return 20922789888000;
	case 17: return 355687428096000;
	case 18: return 6402373705728000;
	case 19: return 121645100408832000;
	case 20: return 2432902008176640000;
	default: return n * factorial(n - 1);
	}
}

bool is_even_permutation(const std::vector<int>& permutation);
bool is_odd_permutation(const std::vector<int>& permutation);

template <typename T>
uint64_t permutation_index(const std::vector<T>& permutation)
{
	std::size_t size = permutation.size();
	uint64_t index = 0;
	uint32_t bitboard = 0;
	for (std::size_t i = 0; i < size; ++i)
	{
		uint32_t mask = 1 << permutation[i];

		// Number of remaining elements smaller than the current element
		// (total number of elements smaller than the current element) - (number of visited elements smaller than the current element)
		uint64_t smaller = permutation[i] - std::popcount(bitboard & (mask - 1));

		// Total number of elements bigger than the current element
		std::size_t bigger = size - i - 1;

		index += smaller * factorial(bigger);
		bitboard |= mask;
	}
	return index;
}

template <typename T, std::size_t Size>
uint64_t permutation_index(const std::array<T, Size>& permutation)
{
	std::size_t size = permutation.size();
	uint64_t index = 0;
	uint32_t bitboard = 0;
	for (std::size_t i = 0; i < size; ++i)
	{
		uint32_t mask = 1 << permutation[i];

		// Number of remaining elements smaller than the current element
		// (total number of elements smaller than the current element) - (number of visited elements smaller than the current element)
		uint64_t smaller = permutation[i] - std::popcount(bitboard & (mask - 1));

		// Total number of elements bigger than the current element
		std::size_t bigger = size - i - 1;

		index += smaller * factorial(bigger);
		bitboard |= mask;
	}
	return index;
}

template <typename... T>
uint64_t permutation_index(T... args)
{
	return permutation_index(std::array{ args... });
}

template <typename T>
void nth_permutation(std::vector<T>& vec, uint64_t index)
{
	std::size_t size = vec.size();
	std::vector<T> permutation;
	permutation.reserve(size);
	std::vector<bool> used(size, false);
	for (std::size_t i = 0; i < size; ++i)
	{
		uint64_t f = factorial(size - i - 1);
		uint64_t j = index / f;
		index %= f;
		for (std::size_t k = 0; k < size; ++k)
		{
			if (used[k])
				continue;
			if (j == 0)
			{
				permutation.push_back(vec[k]);
				used[k] = true;
				break;
			}
			--j;
		}
	}
	vec = permutation;
}
