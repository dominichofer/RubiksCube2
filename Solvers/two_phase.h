#pragma once
#include "Std/std.h"
#include "Cubie/cubie.h"
#include "tables.h"
#include <stdexcept>
#include <iostream>

class TwoPhaseSolver
{
	const DistanceTable& phase_1;
	const DistanceTable& phase_2;
	const DistanceTable& corners;
	HashTable<Cube3x3, uint8_t> tt{ 1'000'000, Cube3x3::impossible(), 0 };
	Twists twists;
	int max_solution_length;

	void search(const Cube3x3& cube, int p1_depth, Twist last = Twist::None)
	{
		bool in_subset = cube.in_subset();
		if (p1_depth == 0 and in_subset)
		{
			if (phase_2.distance(cube.coset_index()) + twists.size() <= max_solution_length)
			{
				twists.append_range(phase_2.solution(cube, [](const Cube3x3& c) { return c.coset_index(); }));
				throw twists;
			}
		}
		if (p1_depth == 0 or in_subset)
			return;

		if (phase_1.distance(cube.coset_number()) > p1_depth)
			return;

		if (corners.distance(cube.corners_index()) > max_solution_length - twists.size())
			return;

		if (tt.lookup(cube).value_or(0) >= p1_depth)
			return;

		for (Twist t : (p1_depth == 1 ? H0::non_twists : all_twists))
		{
			if (same_plane(t, last))
				continue;
			twists.push_back(t);
			search(cube.twisted(t), p1_depth - 1, t);
			twists.pop_back();
		}

		tt.insert(cube, p1_depth);
	}
public:
	TwoPhaseSolver()
		: phase_1(H0_subset_distance_table())
		, phase_2(H0_solution_distance_table())
		, corners(Corners_distance_table())
	{
		twists.reserve(20);
	}

	Twists solve(const Cube3x3& cube, uint8_t max_solution_length)
	{
		twists.clear();
		this->max_solution_length = max_solution_length;
		try
		{
			for (int d = phase_1.distance(cube.coset_number()); d <= max_solution_length; d++)
				search(cube, d);
		}
		catch (const Twists& solution)
		{
			return solution;
		}
		throw std::runtime_error("No solution found");
	}
};
