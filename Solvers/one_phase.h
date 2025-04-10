#pragma once
#include "Cube/cube.h"
#include "tables.h"
#include "transposition_table.h"
#include <vector>

class OnePhaseOptimalSolver
{
	std::vector<Twist> twists;
	const DistanceTable<Corners>& corners_dst;
	const SolutionTable<Cube3x3>& solution_table;
	TranspositionTable<Cube3x3, int>& tt;

	void solve(const Cube3x3&, int depth, Twist last);
public:
	OnePhaseOptimalSolver(
		const DistanceTable<Corners>&,
		const SolutionTable<Cube3x3>&,
		TranspositionTable<Cube3x3, int>&
	) noexcept;

	std::vector<Twist> solve(const Cube3x3&, int max_depth = 20);
};

//template <typename Cube>
//class DistanceTable
//{
//	std::vector<uint8_t> table;
//	std::function<uint64_t(Cube)> index;
//	std::vector<Twist> twists;
//	int max_distance_;
//public:
//	DistanceTable(
//		const Cube& origin,
//		std::vector<Twist> twists,
//		std::function<uint64_t(Cube)> index_fkt,
//		std::size_t index_size)
//		: table(index_size, 0xFF)
//		, index(std::move(index_fkt))
//		, twists(std::move(twists))
//	{
//		table[index(origin)] = 0;
//		std::vector<Cube> last = { origin };
//		std::vector<Cube> next;
//		uint8_t distance = 1;
//		auto start = std::chrono::high_resolution_clock::now();
//		while(!last.empty())
//		{
//			auto end = std::chrono::high_resolution_clock::now();
//			std::cout << "Distance " << (int)distance << " has " << last.size() << " elements and took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
//			next.clear();
//			#pragma omp parallel
//			{
//				std::vector<Cube> next_private;
//				#pragma omp for nowait
//				for (int i = 0; i < last.size(); ++i)
//					for (auto twist : this->twists)
//					{
//						Cube n = last[i].twisted(twist);
//						uint64_t i = index(n);
//						if (table[i] == 0xFF)
//						{
//							table[i] = distance;
//							next_private.push_back(n);
//						}
//					}
//				#pragma omp critical
//				next.insert(next.end(), next_private.begin(), next_private.end());
//			}
//			std::swap(last, next);
//			++distance;
//		}
//		max_distance_ = distance - 2;
//	}
//	DistanceTable() : DistanceTable(Cube{}, Cube::twists, &Cube::index, Cube::index_size) {}
//
//	auto begin() const { return table.begin(); }
//	auto end() const { return table.end(); }
//	int max_distance() const { return max_distance_; }
//	int operator[](const Cube& cube) const { return table[index(cube)]; }
//
//	std::vector<Twist> solution(Cube cube) const
//	{
//		std::vector<Twist> path;
//		uint8_t distance = table[index(cube)];
//		while (distance > 0)
//			for (auto twist : twists)
//			{
//				Cube n = cube.twisted(twist);
//				uint8_t d = table[index(n)];
//				if (d == distance - 1)
//				{
//					path.push_back(twist);
//					cube = n;
//					--distance;
//					break;
//				}
//			}
//		return path;
//	}
//};