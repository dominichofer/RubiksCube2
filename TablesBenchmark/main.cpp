#include "Tables/tables.h"
#include "Math/math.h"
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

void corner_solution()
{
	RandomCubeGenerator<Cubies> rnd(34987);
	std::vector<int> durations;
	for (int i = 0; i < 1'000'000; i++)
	{
		auto start = std::chrono::high_resolution_clock::now();
		solution(rnd());
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
		durations.push_back(duration.count());
	}
	std::cout << "Corner solution: " << average(durations) << " ns +- " << standard_deviation(durations) << " ns\n";
}

void cube3x3_solution()
{
	RandomCubeGenerator<Cube3x3> rnd(34987);
	std::vector<int> durations;
	for (int i = 0; i < 1'000'000; i++)
	{
		auto start = std::chrono::high_resolution_clock::now();
		solution(rnd());
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
		durations.push_back(duration.count());
	}
	std::cout << "Cube3x3 solution: " << average(durations) << " ns +- " << standard_deviation(durations) << " ns\n";
}

int main()
{
	corner_solution();
	cube3x3_solution();
}
