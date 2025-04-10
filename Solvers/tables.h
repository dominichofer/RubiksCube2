#pragma once
#include "Math/math.h"
#include "Cube/cube.h"
#include "neighbours.h"
#include <iostream>
#include <execution>

template <typename Cube>
std::vector<Cube> operator+(std::vector<Cube> a, const std::vector<Cube>& b)
{
	a.insert(a.end(), b.begin(), b.end());
	return a;
}

#include <chrono>
template <typename Cube>
class DistanceTable
{
	std::vector<uint8_t> table;
	std::function<uint64_t(Cube)> index;
	std::vector<Twist> twists;
	int max_distance_;
public:
	DistanceTable(
		const Cube& origin,
		std::vector<Twist> twists,
		std::function<uint64_t(Cube)> index_fkt,
		std::size_t index_size)
		: table(index_size, 0xFF)
		, index(std::move(index_fkt))
		, twists(std::move(twists))
	{
		table[index(origin)] = 0;
		bool changed = true;
		while (changed)
		{
			for (int64_t i = 0; i < static_cast<int64_t>(table.size()); ++i)
			{
				if (table[i] == 0xFF)
					continue;
				Cube cube = Cube::from_index(i);
				for (auto twist : twists)
				{
					Cube n = cube.twisted(twist);
					uint8_t d = table[index(n)];
					if (d == 0xFF)
					{
						table[index(n)] = table[i] + 1;
						changed = true;
					}
				}
			}
		}
		auto start = std::chrono::high_resolution_clock::now();
		max_distance_ = *std::max_element(table.begin(), table.end());
	}
	DistanceTable() : DistanceTable(Cube{}, Cube::twists, &Cube::index, Cube::index_size) {}

	auto begin() const { return table.begin(); }
	auto end() const { return table.end(); }
	int max_distance() const { return max_distance_; }
	int operator[](const Cube& cube) const { return table[index(cube)]; }

	std::vector<Twist> solution(Cube cube) const
	{
		std::vector<Twist> path;
		uint8_t distance = table[index(cube)];
		while (distance > 0)
			for (auto twist : twists)
			{
				Cube n = cube.twisted(twist);
				uint8_t d = table[index(n)];
				if (d == distance - 1)
				{
					path.push_back(twist);
					cube = n;
					--distance;
					break;
				}
			}
		return path;
	}
};

template <typename Cube>
class SolutionTable
{
	std::unordered_map<Cube, std::vector<Twist>> table;
	int max_distance_;
public:
	SolutionTable(
		const Cube& origin,
		std::vector<Twist> twists,
		int max_distance)
		: max_distance_(max_distance)
	{
		table = path_to_neighbours(0, max_distance, origin, twists);
		for (auto& [node, path] : table)
			path = inversed(path);
	}
	SolutionTable(int max_distance) : SolutionTable(Cube{}, Cube::twists, max_distance) {}

	std::optional<std::vector<Twist>> operator[](const Cube& cube) const
	{
		auto it = table.find(cube);
		if (it == table.end())
			return std::nullopt;
		return it->second;
	}

	int max_distance() const { return max_distance_; }
	auto begin() const { return table.begin(); }
	auto end() const { return table.end(); }
};
