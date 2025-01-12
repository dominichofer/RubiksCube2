#include "pch.h"

auto table = CloseSolutionTableCube3x3(1);

TEST(CloseSolutionTableCube3x3, finds_all_solutions)
{
	auto n = neighbours(Cube3x3{}, 1);
	for (const auto& [cube, twists] : n)
	{
		auto sol = table[cube];
		EXPECT_TRUE(sol.has_value());
		EXPECT_EQ(sol.value(), twists);
	}
}
