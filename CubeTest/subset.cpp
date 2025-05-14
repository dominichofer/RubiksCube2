#include "pch.h"
#include <unordered_map>

// Generates cubes in the subset and tests:
// 1. 'in_subset' is true.
// 2. 'subset_index' is the range [0, H0::set_size).
// 3. 'subset_index' is unique for each cube.
// 4. 'from_subset' and 'subset_index' are inverses.
TEST(H0, subset)
{
	RandomCubeGenerator rnd_subset_cube(Cube3x3::solved(), H0::twists, /*seed*/ 124);
	std::unordered_map<uint64_t, Cube3x3> map;
	for (int i = 0; i < 1'000'000; i++)
	{
		auto cube = rnd_subset_cube();
		auto index = H0::subset_index(cube);

		ASSERT_TRUE(H0::in_subset(cube));

		// subset_index is the range [0, H0::set_size).
		ASSERT_GE(index, 0);
		ASSERT_LT(index, H0::set_size);

		// subset_index is unique for each cube.
		if (map.contains(index))
			ASSERT_EQ(map[index], cube);
		map[index] = cube;

		// from_subset and subset_index are inverses.
		ASSERT_EQ(cube, H0::from_subset(index));
	}
}

// For multiple cosets, generates cubes in the coset and tests:
// 1. 'same_coset' is true.
// 2. 'coset_number' is the same for all cubes in the coset.
// 3. 'coset_number' is the range [0, H0::cosets).
// 4. 'coset_index' is the range [0, H0::set_size).
// 5. 'coset_index' is unique for each cube.
// 6. 'from_coset' and (coset_number, coset_index) are inverses.
TEST(H0, coset)
{
	RandomTwistGenerator rnd_twists(Cube3x3::twists, /*seed*/ 125);
	RandomCubeGenerator rnd_subset_cube(Cube3x3::solved(), H0::twists, /*seed*/ 126);
	for (int coset = 0; coset < 10; coset++)
	{
		auto coset_twists = rnd_twists(100); // twists that define the coset
		auto ref_cube = rnd_subset_cube().twisted(coset_twists);
		auto ref_number = H0::coset_number(ref_cube);

		std::unordered_map<uint64_t, Cube3x3> map;
		for (int i = 0; i < 100'000; i++)
		{
			auto cube = rnd_subset_cube().twisted(coset_twists);
			auto number = H0::coset_number(cube);
			auto index = H0::coset_index(cube);

			ASSERT_TRUE(H0::same_coset(cube, ref_cube));
			ASSERT_EQ(ref_number, number);

			// coset_number is the range [0, H0::cosets).
			ASSERT_GE(number, 0);
			ASSERT_LT(number, H0::cosets);

			// coset_index is the range [0, H0::set_size).
			ASSERT_GE(index, 0);
			ASSERT_LT(index, H0::set_size);

			// coset_index is unique for each cube.
			if (map.contains(index))
				ASSERT_EQ(map[index], cube);
			map[index] = cube;

			// from_coset and (cosed_number, coset_index) are inverses.
			ASSERT_EQ(cube, H0::from_coset(number, index));
		}
	}
}
