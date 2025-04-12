#pragma once
#include <array>
#include <bit>
#include <cstdint>
#include <ranges>
#include <stdexcept>
#include <vector>
#include <intrin.h>

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
	default: throw std::invalid_argument("n is too big");
	}
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

template <std::ranges::random_access_range R>
bool is_odd_permutation(const R& permutation)
{
	return not is_even_permutation(permutation);
}

uint64_t permutation_index(const std::ranges::random_access_range auto& permutation)
{
	std::size_t size = std::ranges::distance(permutation);
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

void nth_permutation(uint64_t index, int64_t size, auto out_it)
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
