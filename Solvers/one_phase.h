#pragma once
#include "Std/std.h"
#include "Cubie/cubie.h"
#include "tables.h"
#include <chrono>
#include <stdexcept>
#include <iostream>

//class OnePhaseSolver
//{
//	PartialDistanceTable table{ all_twists };
//	HashTable<Cube3x3, uint8_t> tt{ 1'000'000, Cube3x3::impossible(), 0 };
//	Twists twists;
//
//	void search(const Cube3x3& cube, int depth, Twist last = Twist::None)
//	{
//		if (cube.is_solved())
//			throw twists;
//
//		if (tt.lookup(cube).value_or(0) >= depth)
//			return;
//
//		auto dst = table.distance(cube);
//		if (dst.has_value() and *dst <= depth)
//		{
//			twists.append_range(table.solution(cube));
//			throw twists;
//		}
//
//		for (Twist t : all_twists)
//		{
//			if (same_plane(t, last))
//				continue;
//			twists.push_back(t);
//			search(cube.twisted(t), depth - 1, t);
//			twists.pop_back();
//		}
//
//		tt.insert_if_greater(cube, depth);
//	}
//
//public:
//	OnePhaseSolver()
//	{
//		table.fill(Cube3x3{}, 6);
//		twists.reserve(20);
//	}
//
//	Twists solve(const Cube3x3& cube, uint8_t max_solution_length)
//	{
//		twists.clear();
//		try
//		{
//			for (int d = 0; d <= max_solution_length; d++)
//			{
//				auto start = std::chrono::high_resolution_clock::now();
//				search(cube, d);
//				auto end = std::chrono::high_resolution_clock::now();
//				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//				std::cout << "Depth " << d << ": " << duration.count() << " ms\n";
//			}
//		}
//		catch (const Twists& solution)
//		{
//			return solution;
//		}
//		throw std::runtime_error("No solution found");
//	}
//};