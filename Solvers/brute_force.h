#pragma once
#include "Cube/cube.h"
#include <vector>
#include <stdexcept>

class SolutionFoundException : public std::exception
{
	std::vector<Twist> solution;
};

template <typename Cube>
class BruteForceSolver
{
	std::vector<Twist> twists, stack;

	void solve_(const Cube& cube, int depth)
	{
		if (depth == 0)
		{
			if (cube.is_solved())
				throw 0;
			return;
		}
		for (Twist t : twists)
		{
			stack.push_back(t);
			solve_(cube.twisted(t), depth - 1);
			stack.pop_back();
		}
	}
public:
	BruteForceSolver(std::vector<Twist> twists) noexcept : twists(std::move(twists)) {}

	std::vector<Twist> solve(const Cube& cube, int max_depth)
	{
		stack.clear();
		try
		{
			for (int d = 0; d <= max_depth; d++)
				solve_(cube, d);
		}
		catch (...)
		{
			return stack;
		}
		throw std::runtime_error("No solution found");
	}
};
