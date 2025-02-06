#include "pch.h"

const auto table = CloseSolutionTable<Cube3x3>(5, 2'000'001);

TEST(CloseSolutionTable_Cube3x3, finds_all_solutions)
{
	auto n = neighbours(Cube3x3{}, 0, 5);
	for (const auto& [cube, twists] : n)
	{
		auto sol = table[cube];
		EXPECT_TRUE(sol.has_value());
		EXPECT_EQ(sol.value(), inversed(twists));
	}
}

TEST(CloseSolutionTable_Cube3x3, finds_no_solution)
{
	auto sol = table[Cube3x3::superflip()];
	EXPECT_FALSE(sol.has_value());
}
