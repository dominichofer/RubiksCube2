#include "Solvers/solvers.h"
#include <chrono>
#include <iostream>
#include <vector>


int main()
{
	RandomCubeGenerator<Cube3x3> rnd(4829);
	CloseSolutionTable<Cube3x3> table(5);
	TwoPhaseOptimalSolver solver(table);
	for (int i = 0; i < 100; i++)
	{
		Cube3x3 cube = rnd();
		auto start = std::chrono::high_resolution_clock::now();
		auto solution = solver.solve(cube);
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		std::cout << "Solution: " << solution.size() << " Time: " << duration.count() << " ms (";
		for (auto r : solution)
			std::cout << " " << to_string(r);
		std::cout << " )\n";
	}
}
