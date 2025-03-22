#pragma once
#include "Cube/cube.h"
#include "tables.h"
#include "transposition_table.h"
#include <vector>

class TwoPhaseOptimalSolver
{
	std::vector<Twist> twists;
	const DistanceTable<Corners>& corners_dst;
	const SolutionTable<Cube3x3>& solution_table;
	TranspositionTable<Cube3x3, int>& tt;

	void solve(const Cube3x3&, int depth, Twist last);
public:
	TwoPhaseOptimalSolver(
		const DistanceTable<Corners>&,
		const SolutionTable<Cube3x3>&,
		TranspositionTable<Cube3x3, int>&
	) noexcept;

	std::vector<Twist> solve(const Cube3x3&, int max_depth = 20);
};
