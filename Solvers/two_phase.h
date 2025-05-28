#pragma once
#include "Std/std.h"
#include "Cube/cube.h"
#include "tables.h"
#include <vector>
#include <iostream>

class TwoPhaseSolver
{
	std::vector<Twist> twists;
	DistanceTable<Cube3x3> phase1_length{
		Cube3x3::twists,
		[](const Cube3x3& c) { return H0::coset_number(c); },
		[](uint64_t i) { return H0::from_coset(i, 0); },
		H0::cosets
	};
	DistanceTable<Cube3x3> phase2_length{
		H0::twists,
		[](const Cube3x3& c) { return H0::subset_index(c); },
		[](uint64_t i) { return H0::from_subset(i); },
		H0::set_size
	};

	void solve_(std::vector<Twist>& stack, const Cube3x3& cube, uint8_t phase1_depth, uint8_t max_phase2_length) const
	{
		if (phase1_depth == 0)
		{
			if (not H0::in_subset(cube))
				return;
			if (phase2_length[cube] > max_phase2_length)
				return;
			stack.append_range(phase2_length.solution(cube));
			throw 0;
		}

		if (phase1_length[cube] > phase1_depth)
			return;

		if (phase1_depth == 1)
		{
			for (Twist t : H0::non_twists)
			{
				if ((not stack.empty()) && same_plane(t, stack.back()))
					continue;
				Cube3x3 next_cube = cube.twisted(t);
				if (not H0::in_subset(next_cube))
					continue;
				if (phase2_length[next_cube] > max_phase2_length)
					continue;
				stack.push_back(t);
				stack.append_range(phase2_length.solution(next_cube));
				throw 0;
			}
			return;
		}

		for (Twist t : twists)
		{
			if ((not stack.empty()) && same_plane(t, stack.back()))
				continue;
			stack.push_back(t);
			solve_(stack, cube.twisted(t), phase1_depth - 1, max_phase2_length);
			stack.pop_back();
		}
	}

public:
	TwoPhaseSolver(std::vector<Twist> twists)
		: twists(std::move(twists))
	{
		//cosets.fill(Cube3x3::solved(), Cube3x3::twists);
		//std::cout << "Cosets filled" << std::endl;
		//cosets.write("D:\\coset.path");
		phase1_length.read("D:\\coset.dst");
		phase2_length.read("D:\\subset.dst");
	}

	std::vector<Twist> solve(const Cube3x3& cube, uint8_t max_solution_length) const
	{
		std::vector<Twist> stack;
		try
		{
			for (uint8_t d = 0; d <= max_solution_length; d++)
				solve_(stack, cube, d, max_solution_length - d);
		}
		catch (...)
		{
			return stack;
		}
		throw std::runtime_error("No solution found");
	}
};
