#include "Solvers/solvers.h"
#include <iostream>
#include <chrono>

void time(auto func, const std::string& name)
{
	auto start = std::chrono::high_resolution_clock::now();
	const auto& table = func();
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	std::cout << name << " took " << elapsed.count() << " seconds." << std::endl;

	for (int i = 0; i <= 20; i++)
	{
		auto count = std::ranges::count(table, i);
		if (count == 0)
			break;
		std::cout << "Distance " << i << ": " << count << " cubes." << std::endl;
	}
}

int main()
{
	time(&Corners_distance_table, "Corners distance table generation");
	time(&H0_coset_distance_table, "H0 coset distance table generation");
	time(&H0_subset_distance_table, "H0 subset distance table generation");
}
