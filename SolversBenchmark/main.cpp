#include "benchmark/benchmark.h"
#include "Solvers/solvers.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std::chrono_literals;

int main()
{
	const DistanceTable<Corners> corners_dst;
	const SolutionTable<Cube3x3> solution_table{ 5 };
	TranspositionTable<Cube3x3, int> tt(10'000'000, Cube3x3::impossible(), 0);
	OnePhaseOptimalSolver solver(corners_dst, solution_table, tt);

	std::vector<Corners> rnd_corners = RandomCubes<Corners>(1'000'000, /*seed*/565248);
	std::vector<Cube3x3> rnd_cubes = RandomCubes<Cube3x3>(1'000, /*seed*/3812301);

	// neighbours
	{
		auto start = std::chrono::high_resolution_clock::now();
		benchmark::DoNotOptimize(neighbours(5, Cube3x3{}));
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		std::cout << "neighbours: " << duration << std::endl;
	}

	// DistanceTable::operator[]
	{
		auto start = std::chrono::high_resolution_clock::now();
		for (const Corners& c : rnd_corners)
			benchmark::DoNotOptimize(corners_dst[c]);
		auto stop = std::chrono::high_resolution_clock::now();
		std::cout << "DistanceTable::operator[]: " << (stop - start) / rnd_corners.size() << std::endl;
	}

	// DistanceTable::solution
	{
		auto start = std::chrono::high_resolution_clock::now();
		for (const Corners& c : rnd_corners)
			benchmark::DoNotOptimize(corners_dst.solution(c));
		auto stop = std::chrono::high_resolution_clock::now();
		std::cout << "DistanceTable::solve: " << (stop - start) / rnd_corners.size() << std::endl;
	}

	// SolutionTable::operator[] hit
	{
		std::vector<Cube3x3> hit_cubes;
		for (int dst = 0; dst <= solution_table.max_distance(); dst++)
			for (const Cube3x3& cube : cube3x3_of_distance[dst])
				hit_cubes.push_back(cube);
		auto start = std::chrono::high_resolution_clock::now();
		for (const Cube3x3& cube : hit_cubes)
			benchmark::DoNotOptimize(solution_table[cube]);
		auto stop = std::chrono::high_resolution_clock::now();
		std::cout << "SolutionTable::operator[] hit: " << (stop - start) / hit_cubes.size() << std::endl;
	}

	// SolutionTable::operator[] miss
	{
		std::vector<Cube3x3> miss_cubes;
		for (int dst = solution_table.max_distance() + 1; dst < cube3x3_of_distance.size(); dst++)
			for (const Cube3x3& cube : cube3x3_of_distance[dst])
				miss_cubes.push_back(cube);
		auto start = std::chrono::high_resolution_clock::now();
		for (const Cube3x3& cube : miss_cubes)
			benchmark::DoNotOptimize(solution_table[cube]);
		auto stop = std::chrono::high_resolution_clock::now();
		std::cout << "SolutionTable::operator[] miss: " << (stop - start) / miss_cubes.size() << std::endl;
	}

	// OnePhaseOptimalSolver::solve
	{
		for (int dst = 0; dst < cube3x3_of_distance.size(); dst++)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (const Cube3x3& cube : cube3x3_of_distance[dst])
				benchmark::DoNotOptimize(solver.solve(cube, dst));
			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
			std::cout << "OnePhaseOptimalSolver::solve(dst=" << dst << "): " << duration / cube3x3_of_distance[dst].size() << std::endl;
		}
	}
}
