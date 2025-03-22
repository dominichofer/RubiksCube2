#include "pch.h"
#include <vector>

TEST(statistic, average)
{
	EXPECT_EQ(average(std::vector<int>{ 1 }), 1);
	EXPECT_EQ(average(std::vector<int>{ 1, 1 }), 1);
	EXPECT_EQ(average(std::vector<int>{ 1, 2 }), 1.5);
	EXPECT_EQ(average(std::vector<int>{ 1, 2 }, [](auto x) { return x * x; }), 2.5);
}

TEST(statistic, variance)
{
	EXPECT_EQ(variance(std::vector<int>{ 1 }), 0);
	EXPECT_EQ(variance(std::vector<int>{ 1, 1 }), 0);
	EXPECT_EQ(variance(std::vector<int>{ 1, 2 }), 0.25);
	EXPECT_EQ(variance(std::vector<int>{ 1, 2 }, [](auto x) { return x * x; }), 2.25);
}

TEST(statistic, standard_deviation)
{
	EXPECT_EQ(standard_deviation(std::vector<int>{ 1 }), 0);
	EXPECT_EQ(standard_deviation(std::vector<int>{ 1, 1 }), 0);
	EXPECT_EQ(standard_deviation(std::vector<int>{ 1, 2 }), 0.5);
	EXPECT_EQ(standard_deviation(std::vector<int>{ 1, 2 }, [](auto x) { return x * x; }), 1.5);
}
