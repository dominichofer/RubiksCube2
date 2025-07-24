#pragma once
#include "Cubie/cubie.h"
#include "neighbours.h"
#include <fstream>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

class DistanceTable
{
	Twists twists;
	std::vector<uint8_t> table;
public:
	DistanceTable() = default;
	DistanceTable(Twists twists, std::size_t index_space)
		: twists(std::move(twists)), table(index_space)
	{}

	template <typename Cube, typename F1, typename F2>
	void fill(const Cube& origin, F1 index, F2 from_index)
	{
		const int64_t size = static_cast<int64_t>(table.size());
		constexpr uint8_t sentinel = std::numeric_limits<uint8_t>::max();
		std::ranges::fill(table, sentinel);
		table[index(origin)] = 0;
		for (uint8_t d = 0; d < sentinel - 1; d++)
		{
			bool changed = false;
			#pragma omp parallel for reduction(||: changed) schedule(static, 128)
			for (int64_t i = 0; i < size; i++)
				if (table[i] == d)
				{
					Cube cube = from_index(i);
					for (Twist t : twists)
					{
						Cube n = cube.twisted(t);
						uint8_t& n_d = table[index(n)];
						if (n_d == sentinel)
						{
							n_d = d + 1;
							changed = true;
						}
					}
				}
			if (not changed)
				break;
		}
	}

	uint8_t distance(std::size_t index) const { return table[index]; }

	void read(std::fstream& file)
	{
		file.read(reinterpret_cast<char*>(table.data()), table.size());
	}
	void read(const std::string& file)
	{
		std::fstream f(file, std::ios::binary | std::ios::in);
		if (!f.is_open())
			throw std::runtime_error("Failed to open file: " + file);
		read(f);
	}

	void write(std::fstream& file) const
	{
		file.write(reinterpret_cast<const char*>(table.data()), table.size());
	}
	void write(const std::string& file) const
	{
		std::fstream f(file, std::ios::binary | std::ios::out);
		if (!f.is_open())
			throw std::runtime_error("Failed to open file: " + file);
		write(f);
	}
	auto begin() const { return table.begin(); }
	auto end() const { return table.end(); }

	template <typename Cube, typename F1>
	Twists solution(Cube cube, F1 index) const
	{
		Twists ret;
		for (uint8_t d = distance(index(cube)); d > 0; d--)
			for (Twist t : twists)
			{
				Cube n = cube.twisted(t);
				if (distance(index(n)) == d - 1)
				{
					ret.push_back(t);
					cube = n;
					break;
				}
			}
		return ret;
	}
};

// Distance to the solved state of a Cube3x3.
const DistanceTable& Corners_distance_table();

// Distance to the solved state of a Cube3x3 in the H0 subset.
const DistanceTable& H0_solution_distance_table();

// Distance to the H0 subset.
const DistanceTable& H0_subset_distance_table();


template <typename Cube>
class PartialDistanceTable
{
	std::unordered_map<Cube, uint8_t> table;
	Twists twists;
	int max_distance_;
public:
	PartialDistanceTable(Twists twists) : twists(std::move(twists)), max_distance_(-1) {}

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

	std::optional<uint8_t> distance(const Cube& cube) const
	{
		auto it = table.find(cube);
		if (it == table.end())
			return std::nullopt;
		return it->second;
	}
	std::optional<uint8_t> operator[](const Cube& cube) const { return distance(cube); }

	Twists solution(Cube cube) const
	{
		auto it = table.find(cube);
		if (it == table.end())
			return {};
		Twists path;
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


//template <typename Cube>
//class SolutionTable
//{
//	std::unordered_map<Cube, Twists> table;
//	int max_distance_ = -1;
//public:
//	SolutionTable() = default;
//
//	void clear()
//	{
//		table.clear();
//		max_distance_ = -1;
//	}
//
//	void fill(const Cube& origin, const Twists& twists, int max_distance)
//	{
//		table = path_to_neighbours(0, max_distance, origin, twists);
//		max_distance_ = -1;
//		for (auto& [cube, path] : table)
//		{
//			path = inversed(path);
//			max_distance_ = std::max(max_distance_, static_cast<int>(path.size()));
//		}
//	}
//
//	std::optional<Twists> operator[](const Cube& cube) const
//	{
//		auto it = table.find(cube);
//		if (it == table.end())
//			return std::nullopt;
//		return it->second;
//	}
//
//	int max_distance() const { return max_distance_; }
//	auto begin() const { return table.begin(); }
//	auto end() const { return table.end(); }
//};
