#include "pch.h"
#include <ranges>
//
//TEST(DistanceTable, Corners)
//{
//	const DistanceTable<Corners> table;
//
//	EXPECT_EQ(table.max_distance(), 11);
//
//	// According to https://oeis.org/A080629
//	EXPECT_EQ(std::ranges::count(table, 0), 1);
//	EXPECT_EQ(std::ranges::count(table, 1), 18);
//	EXPECT_EQ(std::ranges::count(table, 2), 243);
//	EXPECT_EQ(std::ranges::count(table, 3), 2'874);
//	EXPECT_EQ(std::ranges::count(table, 4), 28'000);
//	EXPECT_EQ(std::ranges::count(table, 5), 205'416);
//	EXPECT_EQ(std::ranges::count(table, 6), 1'168'516);
//	EXPECT_EQ(std::ranges::count(table, 7), 5'402'628);
//	EXPECT_EQ(std::ranges::count(table, 8), 20'776'176);
//	EXPECT_EQ(std::ranges::count(table, 9), 45'391'616);
//	EXPECT_EQ(std::ranges::count(table, 10), 15'139'616);
//	EXPECT_EQ(std::ranges::count(table, 11), 64'736);
//
//	RandomCubeGenerator<Corners> rnd(53412); // arbitrary seed
//	for (int i = 0; i < 100'000; i++)
//	{
//		Corners c = rnd();
//		auto sol = table.solution(c);
//		EXPECT_TRUE(c.twisted(sol).is_solved());
//		EXPECT_EQ(table[c], sol.size());
//	}
//}

TEST(DistanceTable, H0_cosets)
{
	const DistanceTable<Cube3x3> table(Cube3x3{}, Twists, H0::coset_index, H0::cosets);

	EXPECT_EQ(table.max_distance(), 11);

	// According to https://oeis.org/A080629
	EXPECT_EQ(std::ranges::count(table, 0), 0);
	EXPECT_EQ(std::ranges::count(table, 1), 1);
	EXPECT_EQ(std::ranges::count(table, 2), 2);
	EXPECT_EQ(std::ranges::count(table, 3), 3);
	EXPECT_EQ(std::ranges::count(table, 4), 4);
	EXPECT_EQ(std::ranges::count(table, 5), 5);
	EXPECT_EQ(std::ranges::count(table, 6), 6);
	EXPECT_EQ(std::ranges::count(table, 7), 7);
	EXPECT_EQ(std::ranges::count(table, 8), 8);
	EXPECT_EQ(std::ranges::count(table, 9), 9);
	EXPECT_EQ(std::ranges::count(table, 10), 10);
	EXPECT_EQ(std::ranges::count(table, 11), 11);
}

TEST(SolutionTable, Cube3x3)
{
	const SolutionTable<Cube3x3> table{ 5 };

	for (const auto& [cube, solution] : table)
		EXPECT_TRUE(cube.twisted(solution).is_solved());

	auto sol = table[Cube3x3::superflip()];
	EXPECT_FALSE(sol.has_value());
}
