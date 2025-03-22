#include "brute_force.h"
#include <chrono>
#include <iostream>
#include <utility>

BruteForceSolver::BruteForceSolver(std::vector<Twist> generating_twists) noexcept
	: generating_twists(std::move(generating_twists))
{
	twists.reserve(20);
}

void BruteForceSolver::solve(const Cube3x3& cube, int depth, Twist last)
{
	if (depth == 0)
	{
		if (cube.is_solved())
			throw std::runtime_error("Solution found");
		return;
	}

	if (last != Twist::None)
		twists.push_back(last);

	auto l = std::to_underlying(last) / 3;
	if (l != 0)
	{
		solve(cube.L1(), depth - 1, Twist::L1);
		solve(cube.L2(), depth - 1, Twist::L2);
		solve(cube.L3(), depth - 1, Twist::L3);
	}
	if (l != 1)
	{
		solve(cube.R1(), depth - 1, Twist::R1);
		solve(cube.R2(), depth - 1, Twist::R2);
		solve(cube.R3(), depth - 1, Twist::R3);
	}
	if (l != 2)
	{
		solve(cube.U1(), depth - 1, Twist::U1);
		solve(cube.U2(), depth - 1, Twist::U2);
		solve(cube.U3(), depth - 1, Twist::U3);
	}
	if (l != 3)
	{
		solve(cube.D1(), depth - 1, Twist::D1);
		solve(cube.D2(), depth - 1, Twist::D2);
		solve(cube.D3(), depth - 1, Twist::D3);
	}
	if (l != 4)
	{
		solve(cube.F1(), depth - 1, Twist::F1);
		solve(cube.F2(), depth - 1, Twist::F2);
		solve(cube.F3(), depth - 1, Twist::F3);
	}
	if (l != 5)
	{
		solve(cube.B1(), depth - 1, Twist::B1);
		solve(cube.B2(), depth - 1, Twist::B2);
		solve(cube.B3(), depth - 1, Twist::B3);
	}
	if (last != Twist::None)
		twists.pop_back();
}

std::vector<Twist> BruteForceSolver::solve(const Cube3x3& cube, int max_depth)
{
	twists.clear();
	try
	{
		for (int d = 0; d <= max_depth; d++)
		{
			auto start = std::chrono::high_resolution_clock::now();
			solve(cube, d, Twist::None);
			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
			std::cout << "Depth: " << d << " Time: " << duration.count() << " ms\n";
		}
	}
	catch (const std::runtime_error&)
	{
		return twists;
	}
	throw std::runtime_error("No solution found");
}
