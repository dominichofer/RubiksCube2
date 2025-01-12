#include "Core/core.h"
#include "Tables/tables.h"
#include <cstdint>
#include <chrono>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

std::vector<Rotation> operator+(const std::vector<Rotation>& vec, Rotation r)
{
	std::vector<Rotation> ret = vec;
	ret.push_back(r);
	return ret;
}

template <typename T>
void add_neighbours(std::unordered_map<T, std::vector<Rotation>>& map, const T& cube, const std::vector<Rotation>& rots, int max_distance)
{
	auto result = map.insert({ cube, rots });
	if (!result.second)
	{
		std::size_t a = rots.size();
		std::size_t b = result.first->second.size();
		if (a < b)
			result.first->second = rots;
		if (a > b)
			return;
	}

	if (max_distance == 0)
		return;

	add_neighbours(map, cube.L (), rots + Rotation::L , max_distance - 1);
	add_neighbours(map, cube.L2(), rots + Rotation::L2, max_distance - 1);
	add_neighbours(map, cube.Li(), rots + Rotation::Li, max_distance - 1);
	add_neighbours(map, cube.R (), rots + Rotation::R , max_distance - 1);
	add_neighbours(map, cube.R2(), rots + Rotation::R2, max_distance - 1);
	add_neighbours(map, cube.Ri(), rots + Rotation::Ri, max_distance - 1);
	add_neighbours(map, cube.U (), rots + Rotation::U , max_distance - 1);
	add_neighbours(map, cube.U2(), rots + Rotation::U2, max_distance - 1);
	add_neighbours(map, cube.Ui(), rots + Rotation::Ui, max_distance - 1);
	add_neighbours(map, cube.D (), rots + Rotation::D , max_distance - 1);
	add_neighbours(map, cube.D2(), rots + Rotation::D2, max_distance - 1);
	add_neighbours(map, cube.Di(), rots + Rotation::Di, max_distance - 1);
	add_neighbours(map, cube.F (), rots + Rotation::F , max_distance - 1);
	add_neighbours(map, cube.F2(), rots + Rotation::F2, max_distance - 1);
	add_neighbours(map, cube.Fi(), rots + Rotation::Fi, max_distance - 1);
	add_neighbours(map, cube.B (), rots + Rotation::B , max_distance - 1);
	add_neighbours(map, cube.B2(), rots + Rotation::B2, max_distance - 1);
	add_neighbours(map, cube.Bi(), rots + Rotation::Bi, max_distance - 1);
}

template <typename T>
std::unordered_map<T, std::vector<Rotation>> neighbours_with_rot(T cube, int max_distance)
{
	std::unordered_map<T, std::vector<Rotation>> map;
	add_neighbours(map, cube, {}, max_distance);
	return map;
}

//std::vector<Cube3x3, std::array<Rotation, 6>> neighbours_6;

//void main()
//{
//	auto n = neighbours(6);
//	neighbours_6.reserve(n.size());
//	for (const auto& [cube, rots] : n)
//		if (rots.size() == 6)
//			neighbours_6.push_back({ cube, rots });
//}


template <typename T>
void AddNeighbours(std::unordered_set<T>& set, T c, int max_distance)
{
	set.insert(c);
	if (max_distance == 0)
		return;
	for (Rotation r : rotations)
		AddNeighbours(set, c.twisted(r), max_distance - 1);
}

template <typename T>
std::unordered_set<T> neighbours(T c, int max_distance)
{
	std::unordered_set<T> set;
	AddNeighbours(set, c, max_distance);
	return set;
}


uint64_t index;

class Section
{
	uint64_t lower, upper;
	std::vector<uint8_t> data;
public:
	uint64_t set_count = 0;

	Section(uint64_t lower, uint64_t upper) noexcept
		: lower(lower), upper(upper), data(upper - lower, 0xFF)
	{}

	uint64_t size() const noexcept { return upper - lower; }
	bool all_set() const noexcept { return set_count == size(); }
	uint8_t get(uint64_t index) const
	{
		if (index < lower || index >= upper)
			return 0xFF;
		return data[index - lower];
	}
	void set(uint64_t index, uint8_t value)
	{
		if (index < lower || index >= upper)
			return;
		if (data[index - lower] != 0xFF)
			return;

		data[index - lower] = value;
		++set_count;
	}
};

uint64_t fill(Section& section, Cubies c, int distance, int remaining)
{
	uint64_t index = c.index();
	if (remaining == 0)
	{
		section.set(index, distance);
		return 1;
	}
	if (section.get(index) < distance - remaining)
		return 0;
	uint64_t sum = 0;
	for (Rotation r : rotations)
		sum += fill(section, c.twisted(r), distance, remaining - 1);
	return sum;
}
uint64_t fill(Section& section, Cubies c, int depth)
{
	return fill(section, c, depth, depth);
}

int main()
{
	std::cout.imbue(std::locale(""));

	std::unordered_map<Cubies, std::vector<Rotation>> seen, novel;
	seen.insert({ Cubies{}, {} });
	for (int d = 1; d < 13; d++)
	{
		novel.clear();
		auto start = std::chrono::high_resolution_clock::now();
		for (const auto& [cube, rots] : seen)
			for (Rotation r : rotations)
			{
				auto new_rots = rots;
				new_rots.push_back(r);
				novel.insert({ cube.twisted(r), std::move(new_rots) });
			}
		std::size_t pre = seen.size();
		seen.merge(novel);
		std::size_t post = seen.size();
		std::size_t n = post - pre;
		auto end = std::chrono::high_resolution_clock::now();
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		std::cout << "Depth " << d << ": " << n << " nodes and " << index << " set in " << ms << " ms";
		if (ms > 0)
		{
			auto MN_s = n / 1000 / ms;
			std::cout << " (" << MN_s << " MN/s)";
		}
		std::cout << std::endl;
	}
	//Section section(0, 32ULL*1024*1024*1024);
	//for (int d = 0; d <= 10; ++d)
	//{
	//	auto start = std::chrono::high_resolution_clock::now();
	//	auto n = fill(section, Cubies(), d);
	//	auto end = std::chrono::high_resolution_clock::now();
	//	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	//	std::cout << "Depth " << d << ": " << n << " nodes and " << section.set_count << " set in " << ms << " ms";
	//	if (ms > 0)
	//	{
	//		auto MN_s = n / 1000 / ms;
	//		std::cout << " (" << MN_s << " MN/s)";
	//	}
	//	std::cout << std::endl;
	//}
	//CreateCenterEdgesTable("D:\\center_edges_table.bin");
}