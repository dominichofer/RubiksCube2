#include "pch.h"
#include <iostream>

TEST(ori_swap_0_1, all_states)
{
	for (uint8_t noise = 0x00; noise < 0x10; noise++)
	{
		EXPECT_EQ(ori_swap_0_1(0x00 | noise), 0x10 | noise);
		EXPECT_EQ(ori_swap_0_1(0x10 | noise), 0x00 | noise);
		EXPECT_EQ(ori_swap_0_1(0x20 | noise), 0x20 | noise);
	}
}

TEST(ori_swap_0_2, all_states)
{
	for (uint8_t noise = 0x00; noise < 0x10; noise++)
	{
		EXPECT_EQ(ori_swap_0_2(0x00 | noise), 0x20 | noise);
		EXPECT_EQ(ori_swap_0_2(0x10 | noise), 0x10 | noise);
		EXPECT_EQ(ori_swap_0_2(0x20 | noise), 0x00 | noise);
	}
}

TEST(ori_swap_1_2, all_states)
{
	for (uint8_t noise = 0x00; noise < 0x10; noise++)
	{
		EXPECT_EQ(ori_swap_1_2(0x00 | noise), 0x00 | noise);
		EXPECT_EQ(ori_swap_1_2(0x10 | noise), 0x20 | noise);
		EXPECT_EQ(ori_swap_1_2(0x20 | noise), 0x10 | noise);
	}
}

// Fuzz test
TEST(Corners, index)
{
	RandomCubeGenerator<Corners> rnd(/*seed*/ 8533);
	for (int i = 0; i < 1'000'000; i++)
	{
		auto cube1 = rnd();
		auto cube2 = Corners::from_index(cube1.index());
		EXPECT_EQ(cube1, cube2);
	}
}

TEST(Corners, same_permutation)
{
	Corners c1({ 0, 1, 2, 3, 4, 5, 6, 7 }, { 0, 0, 0, 0, 0, 0, 0, 0 });
	Corners c2({ 0, 1, 2, 3, 4, 5, 6, 7 }, { 1, 1, 1, 1, 1, 1, 1, 1 });
	Corners c3({ 7, 6, 5, 4, 3, 2, 1, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 });

	EXPECT_TRUE(same_permutation(c1, c2));
	EXPECT_FALSE(same_permutation(c1, c3));
}

TEST(Corners, same_orientation)
{
	Corners c1({ 0, 1, 2, 3, 4, 5, 6, 7 }, { 0, 0, 0, 0, 0, 0, 0, 0 });
	Corners c2({ 0, 1, 2, 3, 4, 5, 6, 7 }, { 0, 0, 0, 0, 0, 0, 0, 0 });
	Corners c3({ 0, 1, 2, 3, 4, 5, 6, 7 }, { 1, 1, 1, 1, 1, 1, 1, 1 });

	EXPECT_TRUE(same_orientation(c1, c2));
	EXPECT_FALSE(same_orientation(c1, c3));
}
