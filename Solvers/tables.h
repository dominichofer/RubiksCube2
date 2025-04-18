#pragma once
#include "Math/math.h"
#include "Cube/cube.h"
#include "neighbours.h"
#include <iostream>
#include <fstream>
#include <chrono>

template <typename Cube>
class DistanceTable
{
	std::vector<uint8_t> table;
	std::vector<Twist> twists;
	std::function<int64_t(Cube)> index;
	std::function<Cube(int64_t)> from_index;
	uint8_t max_distance_;
public:
	DistanceTable() = default;
	DistanceTable(
		std::vector<Twist> twists,
		std::function<int64_t(Cube)> index_fkt,
		std::function<Cube(int64_t)> from_index_fkt,
		std::size_t index_space)
		: table(index_space)
		, twists(std::move(twists))
		, index(std::move(index_fkt))
		, from_index(std::move(from_index_fkt))
		, max_distance_(0xFF)
	{}

	void fill(const Cube& origin)
	{
		int64_t size = static_cast<int64_t>(table.size());
		std::ranges::fill(table, 0xFF);
		table[index(origin)] = 0;
		auto start = std::chrono::high_resolution_clock::now();
		for (uint8_t d = 0; d < 0xFE; d++)
		{
			bool changed = false;
			#pragma omp parallel for reduction(||: changed)
			for (int64_t i = 0; i < size; i++)
				if (table[i] == d)
				{
					Cube cube = from_index(i);
					for (Twist t : twists)
					{
						Cube n = cube.twisted(t);
						uint8_t& n_d = table[index(n)];
						if (n_d == 0xFF)
						{
							n_d = d + 1;
							changed = true;
						}
					}
				}
			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
			std::cout << "Distance " << static_cast<int>(d) << ": " << std::ranges::count(table, d) << " (" << duration.count() << "s)" << std::endl;
			if (not changed)
			{
				max_distance_ = d;
				break;
			}
		}
	}

	void read(std::ifstream& file)
	{
		file.read(reinterpret_cast<char*>(table.data()), table.size());
		file.read(reinterpret_cast<char*>(&max_distance_), sizeof(max_distance_));
	}

	void write(std::ofstream& file) const
	{
		file.write(reinterpret_cast<const char*>(table.data()), table.size());
		file.write(reinterpret_cast<const char*>(&max_distance_), sizeof(max_distance_));
	}

	auto begin() const { return table.begin(); }
	auto end() const { return table.end(); }
	uint8_t max_distance() const { return max_distance_; }
	uint8_t operator[](const Cube& cube) const { return table[index(cube)]; }

	std::vector<Twist> solution(Cube cube) const
	{
		std::vector<Twist> path;
		for (uint8_t d = table[index(cube)]; d > 0; d--)
			for (Twist t : twists)
			{
				Cube n = cube.twisted(t);
				if (table[index(n)] == d - 1)
				{
					path.push_back(t);
					cube = n;
					break;
				}
			}
		return path;
	}
};

template <typename Cube>
class PartialDistanceTable
{
	std::unordered_map<Cube, uint8_t> table;
	std::vector<Twist> twists;
	int max_distance_;
public:
	PartialDistanceTable(std::vector<Twist> twists) : twists(std::move(twists)), max_distance_(-1) {}

	void fill(const Cube& origin, int max_distance)
	{
		auto paths = path_to_neighbours(0, max_distance, origin, twists);
		max_distance_ = -1;
		for (auto& [cube, path] : paths)
		{
			table[cube] = path.size();
			max_distance_ = std::max(max_distance_, static_cast<int>(path.size()));
		}
	}

	std::optional<uint8_t> operator[](const Cube& cube) const
	{
		auto it = table.find(cube);
		if (it == table.end())
			return std::nullopt;
		return it->second;
	}
	std::vector<Twist> solution(Cube cube) const
	{
		auto it = table.find(cube);
		if (it == table.end())
			return {};
		std::vector<Twist> path;
		for (int d = it->second; d > 0; d--)
			for (Twist t : twists)
			{
				Cube n = cube.twisted(t);
				auto it_n = table.find(n);
				if (it_n != table.end() && it_n->second == d - 1)
				{
					path.push_back(t);
					cube = n;
					break;
				}
			}
		return path;
	}

	int max_distance() const { return max_distance_; }
	auto begin() const { return table.begin(); }
	auto end() const { return table.end(); }
};

template <typename Cube>
class SolutionTable
{
	std::unordered_map<Cube, std::vector<Twist>> table;
	int max_distance_;
public:
	SolutionTable() = default;

	void fill(const Cube& origin, const std::vector<Twist>& twists, int max_distance)
	{
		table = path_to_neighbours(0, max_distance, origin, twists);
		max_distance_ = -1;
		for (auto& [cube, path] : table)
		{
			path = inversed(path);
			max_distance_ = std::max(max_distance_, static_cast<int>(path.size()));
		}
	}

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
