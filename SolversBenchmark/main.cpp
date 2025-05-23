#include "benchmark/benchmark.h"
#include "Solvers/solvers.h"
#include <cassert>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <vector>
#include <fstream>
#include <functional>

using namespace std::chrono_literals;

std::string to_string(std::chrono::nanoseconds duration)
{
	double value;
	std::string unit;

	auto d = duration.count();

	if (d < 1'000) {
		value = static_cast<double>(d);
		unit = "ns";
	}
	else if (d < 1'000'000) {
		value = d / 1'000.0;
		unit = "us";
	}
	else if (d < 1'000'000'000) {
		value = d / 1'000'000.0;
		unit = "ms";
	}
	else {
		value = d / 1'000'000'000.0;
		unit = "s";
	}

	// Determine number of digits before the decimal
	int int_digits = (value < 1) ? 0 : static_cast<int>(std::log10(value)) + 1;
	int precision = std::max(0, 3 - int_digits);

	std::ostringstream oss;
	oss << std::fixed << std::setprecision(precision) << value << ' ' << unit;
	return oss.str();
}

template <typename F>
void time(std::string name, F function)
{
	auto start = std::chrono::high_resolution_clock::now();
	if constexpr (std::is_same_v<decltype(function()), void>)
		function();
	else
		benchmark::DoNotOptimize(function());
	benchmark::ClobberMemory();
	auto stop = std::chrono::high_resolution_clock::now();
	std::cout << name << ": " << to_string(stop - start) << std::endl;
}

template <typename F>
void time(std::string name, F function, std::ranges::range auto&& range)
{
	if (range.size() == 0)
		return;
	auto start = std::chrono::high_resolution_clock::now();
	for (const auto& item : range)
	{
		if constexpr (std::is_same_v<decltype(function(item)), void>)
			function(item);
		else
			benchmark::DoNotOptimize(function(item));
		benchmark::ClobberMemory();
	}
	auto stop = std::chrono::high_resolution_clock::now();
	std::cout << name << ": " << to_string((stop - start) / range.size()) << std::endl;
}

int main()
{
	//// neighbours
	//for (int d = 0; d < 6; d++)
	//	time(
	//		std::format("neighbours({}, Cube3x3)", d),
	//		[&]() { return neighbours(d, Cube3x3::solved()); });

	//// DistanceTable
	//DistanceTable<Corners> corners_dst{
	//	Corners::twists,
	//	[](const Corners& c) { return c.index(); },
	//	&Corners::from_index,
	//	Corners::index_space
	//};
	//auto rnd_corners = RandomCubes<Corners>(1'000'000, /*seed*/ 565248);
	//time(
	//	"DistanceTable<Corners>::fill()",
	//	[&]() { corners_dst.fill(Corners::solved()); });
	//time(
	//	"DistanceTable<Corners>::operator[]",
	//	[&](const auto& x) { return corners_dst[x]; },
	//	rnd_corners);
	//time(
	//	"DistanceTable<Corners>::solution()",
	//	[&](const auto& x) { return corners_dst.solution(x); },
	//	rnd_corners);

	//// SolutionTable
	//SolutionTable<Cube3x3> solution_table;
	//for (int d = 0; d < 6; d++)
	//{
	//	solution_table.clear();
	//	time(
	//		std::format("SolutionTable<Cube3x3>::fill(d={})", d),
	//		[&]() { solution_table.fill(Cube3x3::solved"), Cube3x3::twists, d); });
	//}
	//std::vector<Cube3x3> hits;
	//hits.append_range(neighbours(0, solution_table.max_distance"), Cube3x3::solved()));
	//auto misses = RandomCubes<Cube3x3>(hits.size"), /*seed*/ 3812301);
	//time(
	//	"SolutionTable<Cube3x3>::operator[hit]",
	//	[&](const auto& x) { return solution_table[x]; },
	//	hits);
	//time(
	//	"SolutionTable<Cube3x3>::operator[miss]",
	//	[&](const auto& x) { return solution_table[x]; },
	//	misses);

	// BruteForceSolver
	//BruteForceSolver<Cube3x3> brute_force_solver{ Cube3x3::twists };
	//for (int d = 0; d < 7; d++)
	//	time(
	//		std::format("BruteForceSolver<Cube3x3>::solve(dst={})", d),
	//		[&](const Cube3x3& cube) {
	//			auto sol = brute_force_solver.solve(cube, 20);
	//			assert(cube.twisted(sol).is_solved());
	//		},
	//		cube3x3_of_distance[d]);

	//// One Phase Optimal Solver
	//DistanceTable<Corners> corners_dst{
	//	Corners::twists,
	//	[](const Corners& c) { return c.index(); },
	//	&Corners::from_index,
	//	Corners::index_space
	//};
	//corners_dst.fill(Corners::solved());

	//PartialDistanceTable<Cube3x3> near{ Cube3x3::twists };
	//near.fill(Cube3x3::solved"), 6);

	//HashTable<Cube3x3, int> tt{ 1'000'000, Cube3x3::impossible() };

	auto file = std::ifstream("..\\irreducible.3x3");
	std::vector<Twists> irreducible;
	std::string line;
	while (std::getline(file, line))
		irreducible.push_back(twists_from_string(line));
	file.close();

	//// One Phase Optimal Solver
	//DistanceTable<Corners> corners_dst{
	//	Corners::twists,
	//	[](const Corners& c) { return c.index(); },
	//	&Corners::from_index,
	//	Corners::index_space
	//};
	//PartialDistanceTable<Cube3x3> near{ Cube3x3::twists };
	//near.fill(Cube3x3::solved(), 6);
	//HashTable<Cube3x3, int> tt{ 10'000'000, Cube3x3::impossible() };

	//OnePhaseOptimalSolver one_phase{ Cube3x3::twists, corners_dst, near, tt };
	//for (int d = 0; d <= 11; d++)
	//{
	//	std::vector<Cube3x3> cubes;
	//	for (const Twists& t : irreducible)
	//		if (t.size() == d)
	//			cubes.push_back(Cube3x3::solved().twisted(t));
	//	tt.clear();
	//	time(
	//		std::format("OnePhaseOptimalSolver::solve(dst={})", d),
	//		[&](const Cube3x3& cube) {
	//			auto sol = one_phase.solve(cube, d);
	//			if (not cube.twisted(sol).is_solved())
	//				std::cerr << "Solution not found" << std::endl;
	//		},
	//		cubes);
	//}

	// Two Phase Solver
	TwoPhaseSolver two_phase{ Cube3x3::twists };
	//auto start = std::chrono::high_resolution_clock::now();
	//two_phase.solve(Cube3x3::superflip());
	//auto stop = std::chrono::high_resolution_clock::now();
	//std::cout << "TwoPhaseSolver::solve(superflip): " << to_string(stop - start) << std::endl;


	for (int d = 0; d <= 15; d++)
	{
		std::vector<Cube3x3> cubes;
		for (const Twists& t : irreducible)
			if (t.size() == d)
				cubes.push_back(Cube3x3::solved().twisted(t));
		time(
			std::format("TwoPhaseSolver::solve(dst={})", d),
			[&](const Cube3x3& cube) {
				auto sol = two_phase.solve(cube, 20);
				if (not cube.twisted(sol).is_solved())
					std::cerr << "Solution not found" << std::endl;
			},
			cubes);
	}
	RandomCubeGenerator<Cube3x3> rnd{ /*seed*/ 323470 };
	for (int i = 0; i < 100; i++)
	{
		auto cube = rnd(100);
		auto start = std::chrono::high_resolution_clock::now();
		auto sol = two_phase.solve(cube, 20);
		auto stop = std::chrono::high_resolution_clock::now();
		if (not cube.twisted(sol).is_solved())
			std::cerr << "Solution not found" << std::endl;
		std::cout << "TwoPhaseSolver::solve(random): " << to_string(stop - start) << std::endl;
	}

	auto cube = Cube3x3::superflip();
	auto start = std::chrono::high_resolution_clock::now();
	auto sol = two_phase.solve(cube, 20);
	auto stop = std::chrono::high_resolution_clock::now();
	if (not cube.twisted(sol).is_solved())
		std::cerr << "Solution not found" << std::endl;
	std::cout << "TwoPhaseSolver::solve(superflip): " << to_string(stop - start) << std::endl;
}
