#include "one_phase.h"
#include "corners.h"

OnePhaseOptimalSolver::OnePhaseOptimalSolver(
	const CornersDistanceTable& corners_dst,
	const CloseSolutionTable<Cube3x3>& solution_table,
	TranspositionTable<Cube3x3, int>& tt) noexcept
	: corners_dst(corners_dst)
	, solution_table(solution_table)
	, tt(tt)
{
	twists.reserve(20);
}

void OnePhaseOptimalSolver::solve(const Cube3x3& cube, int depth, Cube3x3::Twist last)
{
	if (corners_dst[cube.corners()] > depth)
		return;

	if (depth <= solution_table.max_distance())
	{
		if (auto sol = solution_table[cube]; sol.has_value())
		{
			if (last != Cube3x3::Twist::None)
				twists.push_back(last);
			twists.insert(twists.end(), sol->begin(), sol->end());
			throw std::runtime_error("Solution found");
		}
		return;
	}

	if (auto it = tt.lookup(cube); it.has_value() && it.value() >= depth)
		return;

	if (last != Cube3x3::Twist::None)
		twists.push_back(last);
	auto l = std::to_underlying(last) / 3;
	if (l != 0) {
		solve(cube.L1(), depth - 1, Cube3x3::Twist::L1);
		solve(cube.L2(), depth - 1, Cube3x3::Twist::L2);
		solve(cube.L3(), depth - 1, Cube3x3::Twist::L3);
	}
	if (l != 1) {
		solve(cube.R1(), depth - 1, Cube3x3::Twist::R1);
		solve(cube.R2(), depth - 1, Cube3x3::Twist::R2);
		solve(cube.R3(), depth - 1, Cube3x3::Twist::R3);
	}
	if (l != 2) {
		solve(cube.U1(), depth - 1, Cube3x3::Twist::U1);
		solve(cube.U2(), depth - 1, Cube3x3::Twist::U2);
		solve(cube.U3(), depth - 1, Cube3x3::Twist::U3);
	}
	if (l != 3) {
		solve(cube.D1(), depth - 1, Cube3x3::Twist::D1);
		solve(cube.D2(), depth - 1, Cube3x3::Twist::D2);
		solve(cube.D3(), depth - 1, Cube3x3::Twist::D3);
	}
	if (l != 4) {
		solve(cube.F1(), depth - 1, Cube3x3::Twist::F1);
		solve(cube.F2(), depth - 1, Cube3x3::Twist::F2);
		solve(cube.F3(), depth - 1, Cube3x3::Twist::F3);
	}
	if (l != 5) {
		solve(cube.B1(), depth - 1, Cube3x3::Twist::B1);
		solve(cube.B2(), depth - 1, Cube3x3::Twist::B2);
		solve(cube.B3(), depth - 1, Cube3x3::Twist::B3);
	}
	if (last != Cube3x3::Twist::None)
		twists.pop_back();

	tt.insert(cube, depth);
}

std::vector<Cube3x3::Twist> OnePhaseOptimalSolver::solve(const Cube3x3& cube, int max_depth)
{
	twists.clear();
	try
	{
		for (int d = 0; d <= max_depth; d++)
			solve(cube, d, Cube3x3::Twist::None);
	}
	catch (const std::runtime_error&)
	{
		return twists;
	}
	throw std::runtime_error("No solution found");
}
