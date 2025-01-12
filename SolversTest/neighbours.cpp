#include "pch.h"

TEST(neighbours, max_distance_0)
{
	auto n = neighbours(Cube3x3{}, 0);
	EXPECT_EQ(n.size(), 1);
	for (const auto& [cube, twists] : n)
		EXPECT_EQ(Cube3x3().twisted(twists), cube);
}

TEST(neighbours, max_distance_1)
{
	auto n = neighbours(Cube3x3{}, 1);
	EXPECT_EQ(n.size(), 19);
	for (const auto& [cube, twists] : n)
		EXPECT_EQ(Cube3x3().twisted(twists), cube);
}

TEST(neighbours, max_distance_2)
{
	auto n = neighbours(Cube3x3{}, 2);
	EXPECT_EQ(n.size(), 262);
	for (const auto& [cube, twists] : n)
		EXPECT_EQ(Cube3x3().twisted(twists), cube);
}

TEST(neighbours, max_distance_3)
{
	auto n = neighbours(Cube3x3{}, 3);
	EXPECT_EQ(n.size(), 3'502);
	for (const auto& [cube, twists] : n)
		EXPECT_EQ(Cube3x3().twisted(twists), cube);
}

TEST(neighbours, max_distance_4)
{
	auto n = neighbours(Cube3x3{}, 4);
	EXPECT_EQ(n.size(), 46'741);
	for (const auto& [cube, twists] : n)
		EXPECT_EQ(Cube3x3().twisted(twists), cube);
}

TEST(neighbours, max_distance_5)
{
	auto n = neighbours(Cube3x3{}, 5);
	EXPECT_EQ(n.size(), 621'649);
	for (const auto& [cube, twists] : n)
		EXPECT_EQ(Cube3x3().twisted(twists), cube);
}

TEST(neighbours, max_distance_6)
{
	auto n = neighbours(Cube3x3{}, 6);
	EXPECT_EQ(n.size(), 8'240'087);
	for (const auto& [cube, twists] : n)
		EXPECT_EQ(Cube3x3().twisted(twists), cube);
}
