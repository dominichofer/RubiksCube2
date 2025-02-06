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
		std::iota(p.begin(), p.end(), 0);
		for (int i = 0; i < factorial(size); ++i)
		{
			std::iota(q.begin(), q.end(), 0);
			nth_permutation(q, i);
			EXPECT_EQ(q, p);
			std::next_permutation(p.begin(), p.end());
		}
	}
}

// Fuzz test
TEST(permutation, large_sets)
{
	std::mt19937 rnd(/*arbitrary*/ 123);
	std::array<int, 20> p;
	std::vector<int> q(20);
	std::iota(p.begin(), p.end(), 0);
	for (int i = 0; i < 10'000; ++i)
	{
		std::shuffle(p.begin(), p.end(), rnd);
		std::iota(q.begin(), q.end(), 0);
		nth_permutation(q, permutation_index(p));
		for (int j = 0; j < 20; ++j)
			EXPECT_EQ(p[j], q[j]);
	}
}
