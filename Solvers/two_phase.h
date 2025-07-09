#pragma once
#include "Std/std.h"
#include "Cube/cube.h"
#include "tables.h"
#include <stdexcept>
#include <vector>

class TwoPhaseSolver
{
	const DistanceTable<Cube3x3> &phase_1, &phase_2;
	HashTable<Cube3x3, uint8_t> tt{ 1'000'000, Cube3x3::impossible(), 0 };

	void search(const Cube3x3& cube, uint8_t p1_depth, uint8_t p2_depth, Twist last = Twist::None)
	{
		if (p1_depth == 0)
		{
			if (H0::in_subset(cube) and phase_2.distance(cube) <= p2_depth)
				throw 0;
			return;
		}

		if (phase_1.distance(cube) > p1_depth)
			return;

		auto x = tt.lookup(cube);
		if (x.value_or(0) >= p1_depth)
			return;

		if (H0::in_subset(cube))
			return;

		for (Twist t : (p1_depth == 1 ? H0::non_twists : Cube3x3::twists))
		{
			if (same_plane(t, last))
				continue;
			search(cube.twisted(t), p1_depth - 1, p2_depth, t);
		}

		tt.insert(cube, p1_depth);
	}

public:
	TwoPhaseSolver()
		: phase_1(H0_coset_distance_table())
		, phase_2(H0_subset_distance_table())
	{}

	Twists solve(const Cube3x3& cube, uint8_t max_solution_length)
	{
		tt.clear();
		try
		{
			for (uint8_t d = phase_1.distance(cube); d <= max_solution_length; d++)
				search(cube, d, max_solution_length - d);
		}
		catch (...)
		{
			return {};
		}
		throw std::runtime_error("No solution found");
	}
};
