#include "Solvers/solvers.h"
#include <chrono>
#include <iostream>
#include <vector>
#include <unordered_set>

int main()
{
	RandomCubeGenerator<Cube3x3> rnd{ 4829 };
	DistanceTable<Corners> corners_dst{
		Corners::twists,
		[](const Corners& c) { return c.index(); },
		&Corners::from_index,
		Corners::index_space
	};
	corners_dst.fill(Corners::solved());
	PartialDistanceTable<Cube3x3> near{ Cube3x3::twists };
	near.fill(Cube3x3::solved(), 6);
	HashTable<Cube3x3, int> tt{ 10'000'000, Cube3x3::impossible() };
	std::unordered_set<std::string> set;
	for (int d = 1; d < 30; d++)
	{
		std::cout << "Distance: " << d << std::endl;
		#pragma omp parallel for
		for (int i = 0; i < 100; i++)
		{
			OnePhaseOptimalSolver solver{ Cube3x3::twists, corners_dst, near, tt };
			Cube3x3 cube = rnd(d);
			auto start = std::chrono::high_resolution_clock::now();
			auto solution = solver.solve(cube, d);
			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
			#pragma omp critical
			{
				if (cube.twisted(solution).is_solved())
					std::cout << "Solution: " << solution.size() << " Time: " << duration.count() << " ms (" << to_string(solution) << ")\n";
				else
					std::cerr << "Solution not found" << std::endl;
				set.insert(to_string(solution));
			}
		}
		auto file = std::ofstream("irreducible.3x3");
		std::vector<std::string> vec(set.begin(), set.end());
        std::ranges::sort(vec, [](const std::string& a, const std::string& b) {
            return a.size() < b.size() || (a.size() == b.size() && a < b);
        });
		for (const auto& s : vec)
			file << s << '\n';
		file.close();
		std::cout << "Saved " << set.size() << " solutions to irreducible.3x3 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
	}

	//TwoPhaseSolver solver{ Cube3x3::twists };
	//for (int i = 0; i < 100; i++)
	//{
	//	Cube3x3 cube = rnd();
	//	auto start = std::chrono::high_resolution_clock::now();
	//	auto solution = solver.solve(cube);
	//	auto stop = std::chrono::high_resolution_clock::now();
	//	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	//	std::cout << "Solution: " << solution.size() << " Time: " << duration.count() << " ms (" << to_string(solution) << " )\n";
	//}
}
