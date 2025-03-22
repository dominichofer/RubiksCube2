#include "pch.h"
#include <numeric>
#include <vector>

TEST(binomial, small_values)
{
	EXPECT_EQ(binomial(0, 0), 1);

	EXPECT_EQ(binomial(1, 0), 1);
	EXPECT_EQ(binomial(1, 1), 1);

	EXPECT_EQ(binomial(2, 0), 1);
	EXPECT_EQ(binomial(2, 1), 2);
	EXPECT_EQ(binomial(2, 2), 1);

	EXPECT_EQ(binomial(3, 0), 1);
	EXPECT_EQ(binomial(3, 1), 3);
	EXPECT_EQ(binomial(3, 2), 3);
	EXPECT_EQ(binomial(3, 3), 1);

	EXPECT_EQ(binomial(4, 0), 1);
	EXPECT_EQ(binomial(4, 1), 4);
	EXPECT_EQ(binomial(4, 2), 6);
	EXPECT_EQ(binomial(4, 3), 4);
	EXPECT_EQ(binomial(4, 4), 1);
}

TEST(combination_index, small_values)
{
	EXPECT_EQ(combination_index(1, { 0 }), 0);

	EXPECT_EQ(combination_index(2, { 0 }), 0);
	EXPECT_EQ(combination_index(2, { 1 }), 1);
	EXPECT_EQ(combination_index(2, { 0, 1 }), 0);

	EXPECT_EQ(combination_index(3, { 0 }), 0);
	EXPECT_EQ(combination_index(3, { 1 }), 1);
	EXPECT_EQ(combination_index(3, { 2 }), 2);

	EXPECT_EQ(combination_index(3, { 0, 1 }), 0);
	EXPECT_EQ(combination_index(3, { 0, 2 }), 1);
	EXPECT_EQ(combination_index(3, { 1, 2 }), 2);

	EXPECT_EQ(combination_index(3, { 0, 1, 2 }), 0);

	EXPECT_EQ(combination_index(4, { 0 }), 0);
	EXPECT_EQ(combination_index(4, { 1 }), 1);
	EXPECT_EQ(combination_index(4, { 2 }), 2);
	EXPECT_EQ(combination_index(4, { 3 }), 3);

	EXPECT_EQ(combination_index(4, { 0, 1 }), 0);
	EXPECT_EQ(combination_index(4, { 0, 2 }), 1);
	EXPECT_EQ(combination_index(4, { 0, 3 }), 2);
	EXPECT_EQ(combination_index(4, { 1, 2 }), 3);
	EXPECT_EQ(combination_index(4, { 1, 3 }), 4);
	EXPECT_EQ(combination_index(4, { 2, 3 }), 5);
}

TEST(nth_combination, small_values)
{
	// 1 choose 0
	EXPECT_EQ(nth_combination(1, 0, 0), (std::vector<int>{}));

	// 2 choose 1
	EXPECT_EQ(nth_combination(2, 1, 0), (std::vector<int>{0}));
	EXPECT_EQ(nth_combination(2, 1, 1), (std::vector<int>{1}));

	// 2 choose 2
	EXPECT_EQ(nth_combination(2, 2, 0), (std::vector<int>{0, 1}));

	// 3 choose 1
	EXPECT_EQ(nth_combination(3, 1, 0), (std::vector<int>{0}));
	EXPECT_EQ(nth_combination(3, 1, 1), (std::vector<int>{1}));
	EXPECT_EQ(nth_combination(3, 1, 2), (std::vector<int>{2}));

	// 3 choose 2
	EXPECT_EQ(nth_combination(3, 2, 0), (std::vector<int>{0, 1}));
	EXPECT_EQ(nth_combination(3, 2, 1), (std::vector<int>{0, 2}));
	EXPECT_EQ(nth_combination(3, 2, 2), (std::vector<int>{1, 2}));

	// 3 choose 3
	EXPECT_EQ(nth_combination(3, 3, 0), (std::vector<int>{0, 1, 2}));

	// 4 choose 1
	EXPECT_EQ(nth_combination(4, 1, 0), (std::vector<int>{0}));
	EXPECT_EQ(nth_combination(4, 1, 1), (std::vector<int>{1}));
	EXPECT_EQ(nth_combination(4, 1, 2), (std::vector<int>{2}));
	EXPECT_EQ(nth_combination(4, 1, 3), (std::vector<int>{3}));

	// 4 choose 2
	EXPECT_EQ(nth_combination(4, 2, 0), (std::vector<int>{0, 1}));
	EXPECT_EQ(nth_combination(4, 2, 1), (std::vector<int>{0, 2}));
	EXPECT_EQ(nth_combination(4, 2, 2), (std::vector<int>{0, 3}));
	EXPECT_EQ(nth_combination(4, 2, 3), (std::vector<int>{1, 2}));
	EXPECT_EQ(nth_combination(4, 2, 4), (std::vector<int>{1, 3}));
	EXPECT_EQ(nth_combination(4, 2, 5), (std::vector<int>{2, 3}));

	// 4 choose 3
	EXPECT_EQ(nth_combination(4, 3, 0), (std::vector<int>{0, 1, 2}));
	EXPECT_EQ(nth_combination(4, 3, 1), (std::vector<int>{0, 1, 3}));
	EXPECT_EQ(nth_combination(4, 3, 2), (std::vector<int>{0, 2, 3}));
	EXPECT_EQ(nth_combination(4, 3, 3), (std::vector<int>{1, 2, 3}));

	// 4 choose 4
	EXPECT_EQ(nth_combination(4, 4, 0), (std::vector<int>{0, 1, 2, 3}));
}