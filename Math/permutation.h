#pragma once
#include <array>
#include <bit>
#include <cstdint>
#include <vector>

uint64_t factorial(uint64_t);

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