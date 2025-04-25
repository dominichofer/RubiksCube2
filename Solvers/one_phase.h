#pragma once
#include "Cube/cube.h"
#include "hash_table.h"
#include "tables.h"
#include <vector>

class OnePhaseOptimalSolver
{
	std::vector<Twist> twists, stack;
	DistanceTable<Corners> corners_dst;
	PartialDistanceTable<Cube3x3> near;
	HashTable<Cube3x3, int> tt;

	void solve_(const Cube3x3&, int depth, Twist last = Twist::None);
public:
	OnePhaseOptimalSolver(std::vector<Twist> twists, DistanceTable<Corners> corners_dst, PartialDistanceTable<Cube3x3> near, HashTable<Cube3x3, int> tt)
		: twists(std::move(twists))
		, corners_dst(std::move(corners_dst))
		, near(std::move(near))
		, tt(std::move(tt))
	{}

	std::vector<Twist> solve(const Cube3x3& cube, int max_depth = 20);
};
