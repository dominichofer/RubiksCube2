#include "pch.h"
#include <algorithm>

const CornersDistanceTable corners_dst;
const CloseSolutionTable<Cube3x3> solution_table(5, 0x100000);
TranspositionTable<Cube3x3, int> tt(100, Cube3x3::impossible(), 0);
OnePhaseOptimalSolver solver(corners_dst, solution_table, tt);

TEST(OnePhaseOptimalSolver, finds_all_solutions)
{
	for (int dst = 0; dst <= 10; dst++)
		for (const Cube3x3& cube : cube3x3_of_distance[dst])
		{
			auto sol = solver.solve(cube, dst);
			EXPECT_EQ(sol.size(), dst);
			EXPECT_TRUE(cube.twisted(sol).is_solved());
		}
}

TEST(OnePhaseOptimalSolver, finds_no_solution)
{
	EXPECT_ANY_THROW(solver.solve(Cube3x3::superflip(), 5));
}
