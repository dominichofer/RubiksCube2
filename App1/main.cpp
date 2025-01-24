#include "Solvers/solvers.h"
#include <vector>
#include <unordered_set>
#include <iostream>
#include <chrono>

struct Solution
{
	Cube3x3 cube;
	std::vector<Cube3x3::Twist> twists;

	bool operator==(const Solution& o) const
	{
		return cube == o.cube && twists == o.twists;
	}
};

namespace std
{
	template <>
	struct hash<Solution>
	{
		std::size_t operator()(const Solution& s) const
		{
			return s.cube.hash();
		}
	};
}

int main()
{
	RandomCubeGenerator<Cube3x3> rnd(2872312);
	const CornersDistanceTable corners_dst;
	const CloseSolutionTable<Cube3x3> solution_table(7, 0x10000000);

	for (int twists = 16; twists <= 20; twists++)
	{
		std::unordered_set<Solution> solutions;
		auto start = std::chrono::high_resolution_clock::now();
		#pragma omp parallel
		{
			TranspositionTable<Cube3x3, int> tt(10'000'000, Cube3x3::impossible(), 0);
			while (solutions.size() < 20)
			{
				tt.clear();
				OnePhaseOptimalSolver solver(corners_dst, solution_table, tt);
				Cube3x3 cube;

				#pragma omp critical
				cube = rnd();
				try
				{
					auto solution = solver.solve(cube, twists);
					if (solution.size() == twists)
					{
						#pragma omp critical
						{
							solutions.insert({ cube, solution });
							std::cout << solutions.size() << std::endl;
						}
					}
				}
				catch (const std::runtime_error&)
				{
				}
			}
		}
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
		std::cout << "Twists: " << twists << " Time: " << duration << std::endl;

		for (const Solution& s : solutions)
		{
			std::cout << "Cube3x3()";
			for (auto t : s.twists)
				std::cout << "." << to_string(t) << "()";
			std::cout << std::endl;
		}
	}
}