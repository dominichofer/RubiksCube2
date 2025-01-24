#pragma once
#include "Cube/cube.h"
#include "close_solution.h"
#include <vector>

class BruteForceSolver
{
	std::vector<Cube3x3::Twist> twists;

	void solve(const Cube3x3&, int depth, Cube3x3::Twist last);
public:
	BruteForceSolver() noexcept;

	std::vector<Cube3x3::Twist> solve(const Cube3x3&, int max_depth);
};
