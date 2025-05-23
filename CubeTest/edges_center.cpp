#include "pch.h"

// Fuzz test
TEST(EdgesCenter, from_indices)
{
	RandomCubeGenerator<EdgesCenter> rnd(/*seed*/ 68453);
	for (int i = 0; i < 1'000'000; i++)
	{
		auto ref = rnd();
		auto p = ref.prm_index();
		auto o = ref.ori_index();
		auto cube = EdgesCenter{ EdgesCenter::from_prm_index(p), EdgesCenter::from_ori_index(o) };
		EXPECT_EQ(cube, ref);
	}
}

TEST(EdgesCenter, ud_slice_location_index)
{
	auto solved_loc = EdgesCenter::solved().ud_slice_location();
	for (Twist twits : EdgesCenter::twists)
	{
		auto twisted_loc = EdgesCenter::solved().twisted(twits).ud_slice_location();
		bool H0_twist = std::ranges::contains(H0::twists, twits);
		EXPECT_EQ(twisted_loc == solved_loc, H0_twist);
	}
}
