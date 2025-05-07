#include "pch.h"
#include <array>
#include <numeric>
#include <random>
#include <vector>

TEST(factorial, recursive)
{
	EXPECT_EQ(factorial(0), 1);
	for (int i = 1; i <= 20; i++)
		EXPECT_EQ(factorial(i), factorial(i - 1) * i);
}

TEST(permutation_index, size_1)
{
	EXPECT_EQ(permutation_index(0), 0);
}

TEST(permutation_index, size_2)
{
	EXPECT_EQ(permutation_index(0, 1), 0);
	EXPECT_EQ(permutation_index(1, 0), 1);
}

TEST(permutation_index, size_3)
{
	EXPECT_EQ(permutation_index(0, 1, 2), 0);
	EXPECT_EQ(permutation_index(0, 2, 1), 1);
	EXPECT_EQ(permutation_index(1, 0, 2), 2);
	EXPECT_EQ(permutation_index(1, 2, 0), 3);
	EXPECT_EQ(permutation_index(2, 0, 1), 4);
	EXPECT_EQ(permutation_index(2, 1, 0), 5);
}

TEST(permutation_index, size_4)
{
	EXPECT_EQ(permutation_index(0, 1, 2, 3), 0);
	EXPECT_EQ(permutation_index(0, 1, 3, 2), 1);
	EXPECT_EQ(permutation_index(0, 2, 1, 3), 2);
	EXPECT_EQ(permutation_index(0, 2, 3, 1), 3);
	EXPECT_EQ(permutation_index(0, 3, 1, 2), 4);
	EXPECT_EQ(permutation_index(0, 3, 2, 1), 5);
	EXPECT_EQ(permutation_index(1, 0, 2, 3), 6);
	EXPECT_EQ(permutation_index(1, 0, 3, 2), 7);
	EXPECT_EQ(permutation_index(1, 2, 0, 3), 8);
	EXPECT_EQ(permutation_index(1, 2, 3, 0), 9);
	EXPECT_EQ(permutation_index(1, 3, 0, 2), 10);
	EXPECT_EQ(permutation_index(1, 3, 2, 0), 11);
	EXPECT_EQ(permutation_index(2, 0, 1, 3), 12);
	EXPECT_EQ(permutation_index(2, 0, 3, 1), 13);
	EXPECT_EQ(permutation_index(2, 1, 0, 3), 14);
	EXPECT_EQ(permutation_index(2, 1, 3, 0), 15);
	EXPECT_EQ(permutation_index(2, 3, 0, 1), 16);
	EXPECT_EQ(permutation_index(2, 3, 1, 0), 17);
	EXPECT_EQ(permutation_index(3, 0, 1, 2), 18);
	EXPECT_EQ(permutation_index(3, 0, 2, 1), 19);
	EXPECT_EQ(permutation_index(3, 1, 0, 2), 20);
	EXPECT_EQ(permutation_index(3, 1, 2, 0), 21);
	EXPECT_EQ(permutation_index(3, 2, 0, 1), 22);
	EXPECT_EQ(permutation_index(3, 2, 1, 0), 23);
}

TEST(nth_permutation, small_sets)
{
	for (int size = 0; size < 9; ++size)
	{
		std::vector<int> p(size), q(size);
		std::ranges::iota(p, 0);
		for (int64_t i = 0; i < factorial(size); ++i)
		{
			nth_permutation(i, q.begin(), size);
			EXPECT_EQ(q, p);
			std::ranges::next_permutation(p);
		}
	}
}

// Tests that nth_permutation is the inverse of permutation_index.
// Fuzz test
TEST(nth_permutation, is_inverse_of_permutation_index)
{
	std::mt19937 rnd{ 1233 }; // Fixed seed for reproducibility.
	std::array<int, 20> p, q;
	std::ranges::iota(p, 0);
	for (int i = 0; i < 10'000; ++i)
	{
		std::ranges::shuffle(p, rnd);
		nth_permutation(permutation_index(p), q);
		for (int j = 0; j < 20; ++j)
			EXPECT_EQ(p[j], q[j]);
	}
}

// Tests that permutation_index/2 is a bijection,
// between even permutations and [0, factorial(n)/2);
// and between odd permutations and [0, factorial(n)/2).
TEST(permutation_index_half, is_bijection)
{
	for (int size = 0; size < 11; ++size)
	{
		std::vector<int> p(size);
		int even_permutations = 0;
		int odd_permutations = 0;
		for (int i = 0; i < factorial(size); ++i)
		{
			nth_permutation(i, p);
			if (is_even_permutation(p))
			{
				EXPECT_EQ(permutation_index(p) / 2, even_permutations);
				++even_permutations;
			}
			else
			{
				EXPECT_EQ(permutation_index(p) / 2, odd_permutations);
				++odd_permutations;
			}
		}
	}
}
