#include "pch.h"
#include <iostream>

// Fuzz test
TEST(Corners, from_indices)
{
	RandomCubeGenerator<Corners> rnd(/*seed*/ 8533);
	for (int i = 0; i < 1'000'000; i++)
	{
		auto cube = rnd();
		auto p = cube.prm_index();
		auto o = cube.ori_index();
		auto from_index = Corners{ Corners::from_prm_index(p), Corners::from_ori_index(o) };
		EXPECT_EQ(cube, from_index);
	}
}

TEST(Corners, same_permutation)
{
	Corners c1(0, 1, 2, 3, 4, 5, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0);
	Corners c2(0, 1, 2, 3, 4, 5, 6, 7, 1, 1, 1, 1, 1, 1, 1, 1);
	Corners c3(7, 6, 5, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	EXPECT_TRUE(same_permutation(c1, c2));
	EXPECT_FALSE(same_permutation(c1, c3));
}

TEST(Corners, same_orientation)
{
	Corners c1(0, 1, 2, 3, 4, 5, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0);
	Corners c2(0, 1, 2, 3, 4, 5, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0);
	Corners c3(0, 1, 2, 3, 4, 5, 6, 7, 1, 1, 1, 1, 1, 1, 1, 1);

	EXPECT_TRUE(same_orientation(c1, c2));
	EXPECT_FALSE(same_orientation(c1, c3));
}
