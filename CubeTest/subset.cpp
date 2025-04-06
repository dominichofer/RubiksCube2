#include "pch.h"
#include <unordered_set>

// Tests that elements of the subset have a subset_index in the range [0, H0::subset_size).
// Fuzz test
TEST(H0_subset, index_range)
{
	RandomCubeGenerator rnd(Cube3x3::solved(), H0::twists, /*seed*/ 123);
	for (int i = 0; i < 1'000'000; i++)
	{
		auto index = H0::subset_index(rnd());
		EXPECT_GE(index, 0);
		EXPECT_LT(index, H0::subset_size);
	}
}

// Tests that subset_index and from_subset_index are inverses.
// Fuzz test
TEST(H0_subset, from_index)
{
	RandomCubeGenerator rnd(Cube3x3::solved(), H0::twists, /*seed*/ 124);
	for (int i = 0; i < 1'000'000; i++)
	{
		auto cube = rnd();
		EXPECT_EQ(cube, H0::from_subset(H0::subset_index(cube)));
	}
}

// Tests that elements of the subset H0 have unique subset_indices.
// Fuzz test
TEST(H0_subset, unique_index)
{
	RandomCubeGenerator rnd(Cube3x3::solved(), H0::twists, /*seed*/ 125);
	std::unordered_set<Cube3x3> set;
	for (int i = 0; i < 1'000'000; i++)
		set.insert(rnd());

	std::unordered_set<uint64_t> indices;
	for (const auto& cube : set)
		indices.insert(H0::subset_index(cube));

	EXPECT_EQ(indices.size(), set.size());
}

// Tests that elements of a coset of H0 have the same coset_index.
// Fuzz test
TEST(H0_coset_index, same)
{
	RandomTwistGenerator rnd_twists(H0::twists, /*seed*/ 125);
	RandomCubeGenerator rnd_subset_cube(Cube3x3::solved(), H0::twists, /*seed*/ 126);
	for (int i = 0; i < 1'000; i++)
	{
		auto twists = rnd_twists(100);
		auto cube = rnd_subset_cube();
		auto coset_index = H0::coset_index(cube);
		for (int j = 0; j < 1'000; j++)
			EXPECT_EQ(coset_index, H0::coset_index(rnd_subset_cube().twisted(twists)));
	}
}
