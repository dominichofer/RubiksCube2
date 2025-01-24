#pragma once
#include "Cube/cube.h"
#include "close_solution.h"
#include "corners.h"
#include "transposition_table.h"
#include <vector>

class OnePhaseOptimalSolver
{
	std::vector<Cube3x3::Twist> twists;
	const CornersDistanceTable& corners_dst;
	const CloseSolutionTable<Cube3x3>& solution_table;
	TranspositionTable<Cube3x3, int>& tt;

	void solve(const Cube3x3&, int depth, Cube3x3::Twist last);
public:
	OnePhaseOptimalSolver(
		const CornersDistanceTable&,
		const CloseSolutionTable<Cube3x3>&,
		TranspositionTable<Cube3x3, int>&
	) noexcept;

	std::vector<Cube3x3::Twist> solve(const Cube3x3&, int max_depth = 20);
};

