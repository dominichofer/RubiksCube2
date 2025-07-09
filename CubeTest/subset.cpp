#include "pch.h"
#include <unordered_map>

TEST(H0, subset_twists)
{
	for (Twist t : H0::twists)
		EXPECT_TRUE(H0::in_subset(Cube3x3::solved().twisted(t)))
			<< "Twist " << t << " is not in H0 subset";
	for (Twist t : H0::non_twists)
		EXPECT_FALSE(H0::in_subset(Cube3x3::solved().twisted(t)))
			<< "Non-twist " << t << " is in H0 subset";
}


// Generates cubes in the H0 subset and tests:
// 1. 'in_subset' is true.
// 2. 'coset_index' is the range [0, H0::set_size).
// 3. 'coset_index' is unique for each cube.
TEST(H0, subset)
{
	RandomCubeGenerator rnd_subset_cube(Cube3x3::solved(), H0::twists, /*seed*/ 124);
	std::unordered_map<uint64_t, Cube3x3> map;
	for (int i = 0; i < 1'000'000; i++)
	{
		auto cube = rnd_subset_cube();
		auto index = H0::coset_index(cube);

		// 'in_subset' is true.
		ASSERT_TRUE(H0::in_subset(cube));

		// 'coset_index' is the range [0, H0::set_size).
		ASSERT_GE(index, 0);
		ASSERT_LT(index, H0::set_size);

		// 'coset_index' is unique for each cube.
		if (map.contains(index))
			ASSERT_EQ(map[index], cube);
		map[index] = cube;
	}
}

// For multiple cosets, generates cubes in the coset and tests:
// 1. 'same_coset' is true.
// 2. 'coset_number' is the same for all cubes in the coset.
// 3. 'coset_number' is the range [0, H0::cosets).
// 4. 'coset_index' is the range [0, H0::set_size).
// 5. 'coset_index' is unique for each cube.
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

			// 'same_coset' is true.
			ASSERT_TRUE(H0::same_coset(cube, ref_cube));

			// 'coset_number' is the same for all cubes in the coset.
			ASSERT_EQ(ref_number, number);

			// 'coset_number' is the range [0, H0::cosets).
			ASSERT_GE(number, 0);
			ASSERT_LT(number, H0::cosets);

			// 'coset_index' is the range [0, H0::set_size).
			ASSERT_GE(index, 0);
			ASSERT_LT(index, H0::set_size);

			// 'coset_index' is unique for each cube.
			if (map.contains(index))
				ASSERT_EQ(map[index], cube);
			map[index] = cube;
		}
	}
}
