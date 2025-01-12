#include "pch.h"
#include <vector>

TEST(statistic, average)
{
	std::vector<int> v;
	
	v = { 1 };
	EXPECT_EQ(average(v), 1);

	v = { 1, 1 };
	EXPECT_EQ(average(v), 1);

	v = { 1, 2 };
	EXPECT_EQ(average(v), 1.5);

	v = { 1, 2 };
	auto square = [](auto x) { return x * x; };
	EXPECT_EQ(average(v, square), 2.5);
}

TEST(statistic, variance)
{
	std::vector<int> v;

	v = { 1 };
	EXPECT_EQ(variance(v), 0);

	v = { 1, 1 };
	EXPECT_EQ(variance(v), 0);

	v = { 1, 2 };
	EXPECT_EQ(variance(v), 0.25);

	v = { 1, 2 };
	auto square = [](auto x) { return x * x; };
	EXPECT_EQ(variance(v, square), 2.25);
}

TEST(statistic, standard_deviation)
{
	std::vector<int> v;

	v = { 1 };
	EXPECT_EQ(standard_deviation(v), 0);

	v = { 1, 1 };
	EXPECT_EQ(standard_deviation(v), 0);

	v = { 1, 2 };
	EXPECT_EQ(standard_deviation(v), 0.5);

	v = { 1, 2 };
	auto square = [](auto x) { return x * x; };
	EXPECT_EQ(standard_deviation(v, square), 1.5);
}
