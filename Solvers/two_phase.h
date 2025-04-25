#pragma once
#include "Cube/cube.h"
#include "hash_table.h"
#include "tables.h"
#include <vector>
#include <iostream>

class TwoPhaseSolver
{
	std::vector<Twist> twists, stack;
	DistanceTable<Cube3x3> cosets{
		Cube3x3::twists,
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

	void solve_(const Cube3x3& cube, int depth, int max_solution_length, Twist last = Twist::None)
	{
		int phase_1_lenght = cosets[cube];
		if (phase_1_lenght > depth + max_solution_length) {
			std::cout << "Phase1: " << phase_1_lenght << ", Depth: " << depth << ", Max: " << max_solution_length << std::endl;
			return;
		}
		if (depth == 0)
		{
			auto phase1 = cosets.solution(cube);
			auto subset_cube = cube.twisted(phase1);
			int phase2_lenght = subset[subset_cube];
			std::cout << "Phase1: " << phase_1_lenght << ", Phase2: " << phase2_lenght << ", Total: " << phase_1_lenght + phase2_lenght << ", Max: " << max_solution_length << std::endl;
			if (phase_1_lenght + phase2_lenght > max_solution_length)
				return;
			auto phase2 = subset.solution(subset_cube);
			stack.append_range(phase1);
			stack.append_range(phase2);
			throw 0;
		}

		for (Twist t : twists)
		{
			if (same_plane(t, last))
				continue;
			stack.push_back(t);
			solve_(cube.twisted(t), depth - 1, max_solution_length, t);
			stack.pop_back();
		}
	}

public:
	TwoPhaseSolver(std::vector<Twist> twists)
		: twists(std::move(twists))
	{
		cosets.read("C:\\Users\\dohofer\\Documents\\RubiksCube2\\coset.dst");
		subset.read("C:\\Users\\dohofer\\Documents\\RubiksCube2\\subset.dst");
	}

	std::vector<Twist> solve(const Cube3x3& cube, int max_solution_length = 20)
	{
		stack.clear();
		try
		{
			for (int d = 0; d <= max_solution_length; d++)
				solve_(cube, d, max_solution_length - d);
		}
		catch (...)
		{
			return stack;
		}
		throw std::runtime_error("No solution found");
	}
};
