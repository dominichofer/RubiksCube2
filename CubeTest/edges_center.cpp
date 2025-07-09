#include "pch.h"

// Fuzz
TEST(EdgesCenter, from_index)
{
	RandomCubeGenerator<EdgesCenter> rnd(EdgesCenter::solved(), EdgesCenter::twists, /*seed*/ 3287);
	for (int i = 0; i < 1'000'000; i++)
	{
		auto cube = rnd();
		uint64_t slice_loc = cube.ud_slice_loc_index();
		uint64_t prm = cube.ud_prm_index();
		uint64_t ori = cube.ori_index();
		auto from_index = EdgesCenter::from_index(slice_loc, prm, ori);
		EXPECT_EQ(from_index, cube)
			<< "Failed for slice_loc: " << slice_loc << ", prm: " << prm << ", ori: " << ori;
	}
}
