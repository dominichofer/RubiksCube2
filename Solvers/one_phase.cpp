#include "one_phase.h"

void OnePhaseOptimalSolver::solve_(const Cube3x3& cube, int depth)
{
	if (corners_dst[cube.corners()] > depth)
		return;

	if (depth <= near.max_distance())
	{
		if (near[cube].has_value())
		{
			stack.append_range(near.solution(cube));
			throw 0;
		}
		return;
	}

	if (auto it = tt.lookup(cube); it.has_value() && it.value() >= depth)
		return;

	for (Twist t : twists)
	{
		Twist last = stack.back();
		if (same_plane(t, last))
			continue;
		stack.push_back(t);
		solve_(cube.twisted(t), depth - 1);
		stack.pop_back();
	}

	tt.insert(cube, depth);
}

Twists OnePhaseOptimalSolver::solve(const Cube3x3& cube, int max_depth)
{
	stack.clear();
	try
	{
		for (int d = 0; d <= max_depth; d++)
			solve_(cube, d);
	}
	catch (...)
	{
		return stack;
	}
	throw std::runtime_error("No solution found");
}
