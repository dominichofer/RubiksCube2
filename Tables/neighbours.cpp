#include "neighbours.h"
#include <algorithm>
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
		std::size_t current_size = result.first->second.size();
		std::size_t new_size = rots.size();
		if (new_size < current_size)
			result.first->second = rots;
		if (new_size > current_size)
			return;
	}

	if (max_distance == 0)
		return;

	add_neighbours(map, cube.L(), rots + Rotation::L, max_distance - 1);
	add_neighbours(map, cube.L2(), rots + Rotation::L2, max_distance - 1);
	add_neighbours(map, cube.Li(), rots + Rotation::Li, max_distance - 1);
	add_neighbours(map, cube.R(), rots + Rotation::R, max_distance - 1);
	add_neighbours(map, cube.R2(), rots + Rotation::R2, max_distance - 1);
	add_neighbours(map, cube.Ri(), rots + Rotation::Ri, max_distance - 1);
	add_neighbours(map, cube.U(), rots + Rotation::U, max_distance - 1);
	add_neighbours(map, cube.U2(), rots + Rotation::U2, max_distance - 1);
	add_neighbours(map, cube.Ui(), rots + Rotation::Ui, max_distance - 1);
	add_neighbours(map, cube.D(), rots + Rotation::D, max_distance - 1);
	add_neighbours(map, cube.D2(), rots + Rotation::D2, max_distance - 1);
	add_neighbours(map, cube.Di(), rots + Rotation::Di, max_distance - 1);
	add_neighbours(map, cube.F(), rots + Rotation::F, max_distance - 1);
	add_neighbours(map, cube.F2(), rots + Rotation::F2, max_distance - 1);
	add_neighbours(map, cube.Fi(), rots + Rotation::Fi, max_distance - 1);
	add_neighbours(map, cube.B(), rots + Rotation::B, max_distance - 1);
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

struct CubeRotation
{
	Cube3x3 cube;
	std::array<Rotation, 6> rots;

	bool operator<(const CubeRotation& other) const { return cube < other.cube; }
};

class Neighbours
{
	std::vector<std::vector<CubeRotation>> n;

	static int index(const Cube3x3& cube)
	{
		return cube.corner_orientation_index() * 2048 + cube.edge_orientation_index();
	}
public:
	Neighbours()
	{
		n.resize(2'187 * 2048);
		auto map = neighbours_with_rot(Cube3x3(), 6);
		for (const auto& [cube, rots] : map)
			if (rots.size() == 6)
				n[index(cube)].push_back({ cube, {rots[0], rots[1], rots[2], rots[3], rots[4], rots[5]} });
		for (auto& m : n)
			std::sort(m.begin(), m.end());
	}

	std::optional<std::array<Rotation, 6>> operator[](const Cube3x3& cube) const
	{
		auto& m = n[index(cube)];
		auto it = std::lower_bound(m.begin(), m.end(), CubeRotation{ cube, {} });
		if (it == m.end() || it->cube != cube)
			return std::nullopt;
		return it->rots;
	}
};

static Neighbours neighbours_6;

std::optional<std::array<Rotation, 6>> solution(const Cube3x3& cube)
{
	return neighbours_6[cube];
}