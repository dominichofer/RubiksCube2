#pragma once
#include "Std/std.h"
#include "Cube/cube.h"
#include "tables.h"
#include <vector>

class OnePhaseOptimalSolver
{
	std::vector<Twist> stack;
	const std::vector<Twist> twists;
	const DistanceTable<Corners>& corners_dst;
	const PartialDistanceTable<Cube3x3>& near;
	HashTable<Cube3x3, int>& tt;

	void solve_(const Cube3x3&, int depth);
public:
	OnePhaseOptimalSolver(
		std::vector<Twist> twists,
		const DistanceTable<Corners>& corners_dst,
		const PartialDistanceTable<Cube3x3>& near,
		HashTable<Cube3x3, int>& tt)
		: twists(std::move(twists))
		, corners_dst(corners_dst)
		, near(near)
		, tt(tt)
	{}

	std::vector<Twist> solve(const Cube3x3& cube, int max_depth = 20);
};
