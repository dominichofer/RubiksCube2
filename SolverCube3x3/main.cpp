#include "Core/core.h"
#include "Tables/tables.h"
#include <chrono>
#include <iostream>
#include <vector>

class Solver
{
	Cube3x3 scrambled;
	std::vector<Rotation> rots;
public:
	Solver() noexcept
	{
		rots.reserve(20);
	}

	void solve(const Cube3x3& c, int depth, Rotation last)
	{
		if (depth == 0)
		{
			if (c.is_solved())
			{
				if (last != Rotation::None)
					rots.push_back(last);
				throw std::runtime_error("Solution found");
			}
			return;
		}

		if (solution_distance(c.corners) > depth)
			return;

		if (depth == 6)
		{
			if (auto s = solution(c); s.has_value())
			{
				if (last != Rotation::None)
					rots.push_back(last);
				rots.insert(rots.end(), s->begin(), s->end());
				throw std::runtime_error("Solution found");
			}
			return;
		}

		if (last != Rotation::None)
			rots.push_back(last);
		auto l = std::to_underlying(last) / 3;
		if (l != 0) {
			solve(c.L(), depth - 1, Rotation::L);
			solve(c.L2(), depth - 1, Rotation::L2);
			solve(c.Li(), depth - 1, Rotation::Li);
		}
		if (l != 1) {
			solve(c.R(), depth - 1, Rotation::R);
			solve(c.R2(), depth - 1, Rotation::R2);
			solve(c.Ri(), depth - 1, Rotation::Ri);
		}
		if (l != 2) {
			solve(c.U(), depth - 1, Rotation::U);
			solve(c.U2(), depth - 1, Rotation::U2);
			solve(c.Ui(), depth - 1, Rotation::Ui);
		}
		if (l != 3) {
			solve(c.D(), depth - 1, Rotation::D);
			solve(c.D2(), depth - 1, Rotation::D2);
			solve(c.Di(), depth - 1, Rotation::Di);
		}
		if (l != 4) {
			solve(c.F(), depth - 1, Rotation::F);
			solve(c.F2(), depth - 1, Rotation::F2);
			solve(c.Fi(), depth - 1, Rotation::Fi);
		}
		if (l != 5) {
			solve(c.B(), depth - 1, Rotation::B);
			solve(c.B2(), depth - 1, Rotation::B2);
			solve(c.Bi(), depth - 1, Rotation::Bi);
		}
		if (last != Rotation::None)
			rots.pop_back();
	}

	std::vector<Rotation> solve(Cube3x3 scrambled)
	{
		this->scrambled = scrambled;
		rots.clear();
		try
		{
			for (int d = 0; d <= 20; d++)
			{
				auto start = std::chrono::high_resolution_clock::now();
				solve(scrambled, d, Rotation::None);
				auto stop = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
				std::cout << "Depth: " << d << " Time: " << duration.count() << " ms\n";
			}
		}
		catch (...)
		{
			return rots;
		}
		throw;
	}
};

int main()
{
	RandomCubeGenerator<Cube3x3> rnd(4829);
	Solver solver;
	for (int i = 0; i < 100; i++)
	{
		Cube3x3 cube = rnd();
		auto start = std::chrono::high_resolution_clock::now();
		auto solution = solver.solve(cube);
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		std::cout << "Solution: " << solution.size() << " Time: " << duration.count() << " ms   (";
		for (auto r : solution)
			std::cout << " " << to_string(r);
		std::cout << " )\n";
	}
}
