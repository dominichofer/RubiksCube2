#pragma once
#include "Cube/cube.h"
#include <chrono>
#include <stack>
#include <vector>

template <typename Cube>
class BruteForceSolver
{
	std::vector<Twist> twists, stack;

	void solve_(const Cube& cube, int depth)
	{
		if (depth == 0)
		{
			if (cube.is_solved())
				throw;
			return;
		}
		for (Twist t : twists)
		{
			stack.push_back(t);
			solve(cube.twisted(t), depth - 1);
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
			{
				auto start = std::chrono::high_resolution_clock::now();
				solve_(cube, d);
				auto stop = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
				std::cout << "Depth: " << d << " Time: " << duration.count() << " ms\n";
			}
		}
		catch (...)
		{
			return stack;
		}
		throw std::runtime_error("No solution found");
	}
};
