#include "benchmark/benchmark.h"
#include "Solvers/solvers.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <vector>
#include <fstream>

using namespace std::chrono_literals;

int main()
{
	//const DistanceTable<Corners> corners_dst{
	//	Corners::solved(),
	//	Corners::twists,
	//	[](const Corners& c) { return c.index(); },
	//	[](uint64_t i) { return Corners::from_index(i); },
	//	Corners::index_space
	//};
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
	cosets.fill(Cube3x3::solved());
	std::ofstream cosets_file("coset.dst", std::ios::out | std::ios::binary);
	cosets.write(cosets_file);

	subset.fill(Cube3x3::solved());
	std::ofstream subset_file("subset.dst", std::ios::out | std::ios::binary);
	subset.write(subset_file);
	//const SolutionTable<Cube3x3> solution_table{ 5 };
	//TranspositionTable<Cube3x3, int> tt(10'000'000, Cube3x3::impossible(), 0);
	//OnePhaseOptimalSolver solver(corners_dst, solution_table, tt);

	//std::vector<Corners> rnd_corners = RandomCubes<Corners>(1'000'000, /*seed*/565248);
	//std::vector<Cube3x3> rnd_cubes = RandomCubes<Cube3x3>(1'000, /*seed*/3812301);

	//// neighbours
	//{
	//	auto start = std::chrono::high_resolution_clock::now();
	//	benchmark::DoNotOptimize(neighbours(5, Cube3x3{}));
	//	auto stop = std::chrono::high_resolution_clock::now();
	//	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	//	std::cout << "neighbours: " << duration << std::endl;
	//}

	//// DistanceTable::operator[]
	//{
	//	auto start = std::chrono::high_resolution_clock::now();
	//	for (const Corners& c : rnd_corners)
	//		benchmark::DoNotOptimize(corners_dst[c]);
	//	auto stop = std::chrono::high_resolution_clock::now();
	//	std::cout << "DistanceTable::operator[]: " << (stop - start) / rnd_corners.size() << std::endl;
	//}

	//// DistanceTable::solution
	//{
	//	auto start = std::chrono::high_resolution_clock::now();
	//	for (const Corners& c : rnd_corners)
	//		benchmark::DoNotOptimize(corners_dst.solution(c));
	//	auto stop = std::chrono::high_resolution_clock::now();
	//	std::cout << "DistanceTable::solve: " << (stop - start) / rnd_corners.size() << std::endl;
	//}

	//// SolutionTable::operator[] hit
	//{
	//	std::vector<Cube3x3> hit_cubes;
	//	for (int dst = 0; dst <= solution_table.max_distance(); dst++)
	//		for (const Cube3x3& cube : cube3x3_of_distance[dst])
	//			hit_cubes.push_back(cube);
	//	auto start = std::chrono::high_resolution_clock::now();
	//	for (const Cube3x3& cube : hit_cubes)
	//		benchmark::DoNotOptimize(solution_table[cube]);
	//	auto stop = std::chrono::high_resolution_clock::now();
	//	std::cout << "SolutionTable::operator[] hit: " << (stop - start) / hit_cubes.size() << std::endl;
	//}

	//// SolutionTable::operator[] miss
	//{
	//	std::vector<Cube3x3> miss_cubes;
	//	for (int dst = solution_table.max_distance() + 1; dst < cube3x3_of_distance.size(); dst++)
	//		for (const Cube3x3& cube : cube3x3_of_distance[dst])
	//			miss_cubes.push_back(cube);
	//	auto start = std::chrono::high_resolution_clock::now();
	//	for (const Cube3x3& cube : miss_cubes)
	//		benchmark::DoNotOptimize(solution_table[cube]);
	//	auto stop = std::chrono::high_resolution_clock::now();
	//	std::cout << "SolutionTable::operator[] miss: " << (stop - start) / miss_cubes.size() << std::endl;
	//}

	//// OnePhaseOptimalSolver::solve
	//{
	//	for (int dst = 0; dst < cube3x3_of_distance.size(); dst++)
	//	{
	//		auto start = std::chrono::high_resolution_clock::now();
	//		for (const Cube3x3& cube : cube3x3_of_distance[dst])
	//			benchmark::DoNotOptimize(solver.solve(cube, dst));
	//		auto stop = std::chrono::high_resolution_clock::now();
	//		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	//		std::cout << "OnePhaseOptimalSolver::solve(dst=" << dst << "): " << duration / cube3x3_of_distance[dst].size() << std::endl;
	//	}
	//}
}
