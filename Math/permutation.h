#pragma once
#include <array>
#include <bit>
#include <cstdint>
#include <ranges>
#include <stdexcept>
#include <vector>
#include <intrin.h>

constexpr int64_t factorial(int64_t n)  
{
	constexpr int64_t precomputed[] = {
		1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880,
		3628800, 39916800, 479001600, 6227020800, 87178291200,
		1307674368000, 20922789888000, 355687428096000,
		6402373705728000, 121645100408832000, 2432902008176640000
	};

    return precomputed[n];  
}

template <std::ranges::random_access_range R>
bool is_even_permutation(const R& permutation)
{
	std::size_t size = std::ranges::distance(permutation);
	std::size_t count = 0;
	for (std::size_t i = 0; i < size; i++)
		for (std::size_t j = i + 1; j < size; j++)
			if (permutation[i] > permutation[j])
				count++;
	return count % 2 == 0;
}

bool is_even_permutation(uint64_t lexicographical_index);

template <std::ranges::random_access_range R>
bool is_odd_permutation(const R& permutation)
{
	return not is_even_permutation(permutation);
}

bool is_odd_permutation(uint64_t lexicographical_index);

int64_t permutation_index(const std::ranges::random_access_range auto& permutation)
{
	std::size_t size = std::ranges::distance(permutation);
	int64_t index = 0;
	uint64_t bitboard = 0;
	for (std::size_t i = 0; i < size; ++i)
	{
		uint64_t mask = 1ULL << permutation[i];

		// Number of remaining elements smaller than the current element
		// (total number of elements smaller than the current element) - (number of visited elements smaller than the current element)
		int64_t smaller = permutation[i] - std::popcount(bitboard & (mask - 1));

		// Total number of elements bigger than the current element
		int64_t bigger = size - i - 1;

		index += smaller * factorial(bigger);
		bitboard |= mask;
	}
	return index;
}

template <typename... T>
int64_t permutation_index(T... args)
{
	return permutation_index(std::array{ args... });
}

void nth_permutation(int64_t index, auto out_it, int64_t size)
{
	uint64_t unused = 0xFFFFFFFFFFFFFFULL;
	for (int64_t i = size - 1; i >= 0; --i)
	{
		int64_t f = factorial(i);
		uint64_t mask = _pdep_u64(1ULL << (index / f), unused);
		index %= f;
		*out_it++ = std::countr_zero(mask);
		unused ^= mask;
	}
}

void nth_permutation(int64_t index, std::ranges::range auto& out)
{
	nth_permutation(index, std::ranges::begin(out), std::ranges::size(out));
}
