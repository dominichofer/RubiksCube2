#pragma once
#include "Cube/cube.h"
#include "close_solution.h"
#include "corners.h"
#include <vector>

class TwoPhaseOptimalSolver
{
	std::vector<Cube3x3::Twist> twists;
	const CornersDistanceTable& corners_dst;
	const CloseSolutionTable<Cube3x3>& solution_table;

	void solve(const Cube3x3&, int depth, Cube3x3::Twist last);
public:
	TwoPhaseOptimalSolver(
		const CornersDistanceTable&,
		const CloseSolutionTable<Cube3x3>&
	) noexcept;

	std::vector<Cube3x3::Twist> solve(const Cube3x3&);
};
