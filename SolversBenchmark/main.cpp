#include "benchmark/benchmark.h"
#include "Solvers/solvers.h"
#include <chrono>
#include <iostream>

void solution_distance(const std::vector<Corners>& corners)
{
	auto start = std::chrono::high_resolution_clock::now();
	for (const Corners& c : corners)
		benchmark::DoNotOptimize(solution_distance(c));
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
	std::cout << "solution_distance(Corners): " << corners.size() / 1000 / duration << " M/s" << std::endl;
}

void solution(const std::vector<Corners>& corners)
{
	auto start = std::chrono::high_resolution_clock::now();
	for (const Corners& c : corners)
		benchmark::DoNotOptimize(solution(c));
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
	std::cout << "solution(Corners): " << corners.size() / duration << " k/s" << std::endl;
}

int main()
{
	RandomCubeGenerator<Corners> rnd(565248); // arbitrary seed
	std::vector<Corners> cubes;
	std::size_t size = 1'000'000;
	cubes.reserve(size);
	for (int i = 0; i < size; i++)
		cubes.push_back(rnd());

	solution_distance(cubes);
	solution(cubes);
}
