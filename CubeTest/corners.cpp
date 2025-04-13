#include "pch.h"
#include <iostream>

// Fuzz test
//TEST(Corners, from_indices)
//{
//	RandomCubeGenerator<Corners> rnd(/*seed*/ 8533);
//	for (int i = 0; i < 1'000'000; i++)
//	{
//		auto cube = rnd();
//		auto p = cube.prm_index();
//		auto o = cube.ori_index();
//		auto from_index = Corners{ Corners::from_prm_index(p), Corners::from_ori_index(o) };
//		EXPECT_EQ(cube, from_index);
//	}
//}
