#include "pch.h"
#include <unordered_map>

//TEST(H0_subset, fuzzing)
//{
//	RandomCubeGenerator rnd(Cube3x3::solved(), H0::twists, /*seed*/ 124);
//	std::unordered_map<uint64_t, Cube3x3> map;
//	for (int i = 0; i < 1'000'000; i++)
//	{
//		auto cube = rnd();
//		auto index = H0::subset_index(cube);
//
//		// subset_index is the range [0, H0::set_size).
//		EXPECT_GE(index, 0);
//		EXPECT_LT(index, H0::set_size);
//
//		// subset_index is unique for each cube.
//		if (map.contains(index))
//			ASSERT_EQ(map[index], cube);
//		map[index] = cube;
//
//		// from_subset_index and subset_index are inverses.
//		EXPECT_EQ(cube, H0::from_subset(index));
//	}
//}

// Tests that elements of the same coset of H0 have the same coset_number.
// Fuzz test
TEST(H0_coset, fuzzing)
{
	RandomTwistGenerator rnd_twists(Cube3x3::twists, /*seed*/ 125);
	RandomCubeGenerator rnd_subset_cube(Cube3x3::solved(), H0::twists, /*seed*/ 126);
	for (int coset = 0; coset < 100; coset++)
	{
		auto twists = rnd_twists(100); // twists that define the coset
		auto ref_cube = rnd_subset_cube().twisted(twists);
		auto ref_number = H0::coset_number(ref_cube);

		std::unordered_map<uint64_t, Cube3x3> map;
		for (int i = 0; i < 100'000; i++)
		{
			auto cube = rnd_subset_cube().twisted(twists);
			auto number = H0::coset_number(cube);
			auto index = H0::coset_index(cube);

			// coset_number is the range [0, H0::cosets).
			EXPECT_GE(number, 0);
			EXPECT_LT(number, H0::cosets);

			// coset_index is the range [0, H0::set_size).
			EXPECT_GE(index, 0);
			EXPECT_LT(index, H0::set_size);

			// coset_number depends on the coset.
			EXPECT_EQ(ref_number, number);

			// coset_index is unique for each cube.
			if (map.contains(index))
				ASSERT_EQ(map[index], cube);
			map[index] = cube;

			// from_coset and (cosed_number, coset_index) are inverses.
			std::cout << to_string(cube) << std::endl;
			std::cout << to_string(H0::from_coset(number, index)) << std::endl;
			EXPECT_EQ(cube, H0::from_coset(number, index));
		}
	}
}
