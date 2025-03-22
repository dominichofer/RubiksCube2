#pragma once
#include "Cube/cube.h"
#include <vector>

class BruteForceSolver
{
	std::vector<Twist> twists, generating_twists;

	void solve(const Cube3x3&, int depth, Twist last);
public:
	BruteForceSolver(std::vector<Twist> generating_twists) noexcept;

	std::vector<Twist> solve(const Cube3x3&, int max_depth);
};
