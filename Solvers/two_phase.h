#pragma once
#include "Std/std.h"
#include "Cube/cube.h"
#include "tables.h"
#include <vector>
#include <iostream>

class TwoPhaseSolver
{
	std::vector<Twist> twists;
	PathTable<Cube3x3, 12> cosets{
		[](const Cube3x3& c) { return H0::coset_number(c); },
		[](uint64_t i) { return H0::from_coset(i, 0); },
		H0::cosets
	};
	DistanceTable<Cube3x3> subset{
		H0::twists,
		[](const Cube3x3& c) { return H0::subset_index(c); },
		[](uint64_t i) { return H0::from_subset(i); },
		H0::set_size
	};

	void solve_(std::vector<Twist>& stack, const Cube3x3& cube, int depth, int max_solution_length) const
	{
		if (depth == 0)
		{
			auto phase_1 = cosets.solution(cube);
			if (phase_1.size() > depth + max_solution_length)
				return;
			auto subset_cube = cube.twisted(phase_1);
			int phase2_lenght = subset[subset_cube];
			if (phase_1.size() + phase2_lenght > max_solution_length)
				return;
			auto phase_2 = subset.solution(subset_cube);
			stack.append_range(phase_1);
			stack.append_range(phase_2);
			throw 0;
		}
		else
		{
			auto phase_1_length = cosets[cube];
			if (phase_1_length > depth + max_solution_length)
				return;
		}

		for (Twist t : twists)
		{
			if ((not stack.empty()) && same_plane(t, stack.back()))
				continue;
			stack.push_back(t);
			solve_(stack, cube.twisted(t), depth - 1, max_solution_length);
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
		cosets.read("D:\\coset.path");
		subset.read("D:\\subset.dst");
	}

	std::vector<Twist> solve(const Cube3x3& cube, int max_solution_length) const
	{
		std::vector<Twist> stack;
		try
		{
			for (int d = 0; d <= max_solution_length; d++)
				solve_(stack, cube, d, max_solution_length - d);
		}
		catch (...)
		{
			return stack;
		}
		throw std::runtime_error("No solution found");
	}
};
