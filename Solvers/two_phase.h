#pragma once
#include "Std/std.h"
#include "Cube/cube.h"
#include "tables.h"
#include <stdexcept>
#include <vector>

class TwoPhaseSolver
{
	thread_local static inline Twists stack;
	thread_local static inline uint8_t max_phase2_length;
	const DistanceTable<Cube3x3> &phase_1, &phase_2;

	Twists phase_2_solution(const Cube3x3& cube) const
	{
		return solution(phase_2, H0::twists, cube);
	}

	void search(const Cube3x3& cube, uint8_t phase1_depth) const
	{
		if (phase1_depth == 0)
		{
			if (H0::in_subset(cube) and phase_2[cube] <= max_phase2_length)
			{
				stack.append_range(phase_2_solution(cube));
				throw 0;
			}
			return;
		}

		if (phase_1[cube] > phase1_depth)
			return;

		for (Twist t : (phase1_depth == 1 ? H0::non_twists : Cube3x3::twists))
		{
			if ((not stack.empty()) and same_plane(t, stack.back()))
				continue;
			stack.push_back(t);
			search(cube.twisted(t), phase1_depth - 1);
			stack.pop_back();
		}
	}

public:
	TwoPhaseSolver()
		: phase_1(H0_coset_distance_table())
		, phase_2(H0_subset_distance_table())
	{}

	Twists solve(const Cube3x3& cube, uint8_t max_solution_length) const
	{
		stack.clear();
		stack.reserve(max_solution_length);
		try
		{
			for (uint8_t d = 0; d <= max_solution_length; d++)
			{
				max_phase2_length = max_solution_length - d;
				search(cube, d);
			}
		}
		catch (...)
		{
			return stack;
		}
		throw std::runtime_error("No solution found");
	}
};
