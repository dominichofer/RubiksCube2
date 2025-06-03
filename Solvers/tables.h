#pragma once
#include "Math/math.h"
#include "Cube/cube.h"
#include "neighbours.h"
#include <array>
#include <fstream>
#include <string>
#include <chrono>
#include <iostream>

template <typename Cube>
class DistanceTable
{
	std::vector<uint8_t> table;
	std::function<int64_t(Cube)> index;
public:
	DistanceTable() = default;
	DistanceTable(
		std::function<int64_t(Cube)> index_fkt,
		std::size_t index_space)
		: table(index_space)
		, index(std::move(index_fkt))
	{}

	void fill(const Cube& origin, const std::vector<Twist>& twists, std::function<Cube(int64_t)> from_index)
	{
		int64_t size = static_cast<int64_t>(table.size());
		std::ranges::fill(table, 0xFF);
		table[index(origin)] = 0;
		for (uint8_t d = 0; d < 0xFE; d++)
		{
			bool changed = false;
			#pragma omp parallel for reduction(||: changed) schedule(static, 64)
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
			if (not changed)
				break;
		}
	}

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

	uint8_t operator[](const Cube& cube) const { return table[index(cube)]; }
};

template <typename Cube>
std::vector<Twist> solution(const DistanceTable<Cube>& table, const std::vector<Twist>& twists, Cube cube)
{
	uint8_t d = table[cube];
	std::vector<Twist> path;
	path.reserve(d);
	for (; d > 0; d--)
		for (Twist t : twists)
		{
			Cube n = cube.twisted(t);
			if (table[n] == d - 1)
			{
				path.push_back(t);
				cube = n;
				break;
			}
		}
	return path;
}

// Distance of a Cube3x3 in the H0 subset to the origin (solved state).
const DistanceTable<Cube3x3>& H0_subset_distance_table();

// Distance of a Cube3x3 to the H0 subset.
const DistanceTable<Cube3x3>& H0_coset_distance_table();

//template <typename Cube>
//class DirectionTable
//{
//	std::vector<std::pair<uint8_t, Twist>> table;
//	std::function<int64_t(Cube)> index;
//	std::function<Cube(int64_t)> from_index;
//	int8_t max_distance_;
//public:
//	DirectionTable() = default;
//	DirectionTable(
//		std::function<int64_t(Cube)> index_fkt,
//		std::function<Cube(int64_t)> from_index_fkt,
//		std::size_t index_space)
//		: table(index_space)
//		, index(std::move(index_fkt))
//		, from_index(std::move(from_index_fkt))
//		, max_distance_(INT8_MAX)
//	{
//	}
//
//	void fill(const Cube& origin, const std::vector<Twist>& twists)
//	{
//		const int64_t size = static_cast<int64_t>(table.size());
//		const std::pair<uint8_t, Twist> sentinel{ 0xFF, Twist::None };
//		std::ranges::fill(table, sentinel);
//		table[index(origin)] = { 0, Twist::None };
//		auto start = std::chrono::high_resolution_clock::now();
//		for (uint8_t d = 0; d < 0xFE; d++)
//		{
//			bool changed = false;
//			#pragma omp parallel for reduction(||: changed)
//			for (int64_t i = 0; i < size; i++)
//				if (table[i].first == d)
//				{
//					Cube cube = from_index(i);
//					for (Twist t : twists)
//					{
//						Cube n = cube.twisted(t);
//						auto& next = table[index(n)];
//						if (next == sentinel)
//						{
//							next = { d + 1, inversed(t) };
//							changed = true;
//						}
//					}
//				}
//			std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - start;
//			std::cout << std::format("d = {}, elapsed = {:.2f} seconds", d, elapsed.count()) << std::endl;
//			if (not changed)
//			{
//				max_distance_ = d;
//				break;
//			}
//		}
//	}
//
//	uint8_t operator[](const Cube& cube) const { return table[index(cube)].first; }
//
//	std::vector<Twist> solution(Cube cube) const
//	{
//		auto current = table[index(cube)];
//		std::vector<Twist> path;
//		path.reserve(current.first);
//		while (current.first > 0)
//		{
//			path.push_back(current.second);
//			cube = cube.twisted(current.second);
//			current = table[index(cube)];
//		}
//		return path;
//	}
//};

//template <typename Cube, std::size_t TWISTS>
//class PathTable
//{
//	std::vector<nTwists<TWISTS>> table;
//	std::function<int64_t(Cube)> index;
//	std::function<Cube(int64_t)> from_index;
//	int8_t max_distance_;
//public:
//	PathTable() = default;
//	PathTable(
//		std::function<int64_t(Cube)> index_fkt,
//		std::function<Cube(int64_t)> from_index_fkt,
//		std::size_t index_space)
//		: table(index_space)
//		, index(std::move(index_fkt))
//		, from_index(std::move(from_index_fkt))
//		, max_distance_(INT8_MAX)
//	{}
//
//	void fill(const Cube& origin, const std::vector<Twist>& twists)
//	{
//		const int64_t size = static_cast<int64_t>(table.size());
//		const nTwists<TWISTS> sentinel{ -1 };
//		std::ranges::fill(table, sentinel);
//		table[index(origin)] = nTwists<TWISTS>{};
//		auto start = std::chrono::high_resolution_clock::now();
//		for (int8_t d = 0; d <= TWISTS; d++)
//		{
//			bool changed = false;
//			#pragma omp parallel for reduction(||: changed)
//			for (int64_t i = 0; i < size; i++)
//			{
//				if (table[i].size() != d)
//					continue;
//				Cube cube = from_index(i);
//				for (Twist t : twists)
//				{
//					auto& next = table[index(cube.twisted(t))];
//					if (next == sentinel)
//					{
//						#pragma omp critical
//						{
//							next = table[i];
//							next.append(t);
//						}
//						changed = true;
//					}
//				}
//			}
//			std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - start;
//			std::cout << std::format("d = {}, elapsed = {:.2f} seconds", d, elapsed.count()) << std::endl;
//			if (not changed)
//			{
//				max_distance_ = d;
//				#pragma omp parallel for reduction(||: changed)
//				for (int64_t i = 0; i < size; i++)
//					table[i].inverse();
//				break;
//			}
//		}
//	}
//
//	void read(std::fstream& file)
//	{
//		file.read(reinterpret_cast<char*>(table.data()), sizeof(nTwists<TWISTS>) * table.size());
//		file.read(reinterpret_cast<char*>(&max_distance_), sizeof(max_distance_));
//	}
//	void read(const std::string& file)
//	{
//		std::fstream f(file, std::ios::binary | std::ios::in);
//		if (!f.is_open())
//			throw std::runtime_error("Failed to open file: " + file);
//		read(f);
//	}
//
//	void write(std::fstream& file) const
//	{
//		for (const auto& t : table)
//		{
//			int8_t size = t.size();
//			file.write(reinterpret_cast<const char*>(&size), sizeof(size));
//			file.write(reinterpret_cast<const char*>(t.data()), sizeof(Twist) * TWISTS);
//		}
//		file.write(reinterpret_cast<const char*>(&max_distance_), sizeof(max_distance_));
//	}
//	void write(const std::string& file) const
//	{
//		std::fstream f(file, std::ios::binary | std::ios::out);
//		if (!f.is_open())
//			throw std::runtime_error("Failed to open file: " + file);
//		write(f);
//	}
//
//	auto begin() const { return table.begin(); }
//	auto end() const { return table.end(); }
//	uint8_t max_distance() const { return max_distance_; }
//	uint8_t operator[](const Cube& cube) const { return table[index(cube)].size(); }
//	const nTwists<TWISTS>& solution(const Cube& cube) const
//	{
//		return table[index(cube)];
//	}
//};

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
	int max_distance_ = -1;
public:
	SolutionTable() = default;

	void clear()
	{
		table.clear();
		max_distance_ = -1;
	}

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
