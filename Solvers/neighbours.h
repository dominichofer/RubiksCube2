#pragma once
#include "Cube/cube.h"
#include <unordered_map>
#include <vector>

template <typename Cube>
class NeighbourGenerator
{
	std::vector<typename Cube::Twist> possible_twists, twists;
	std::unordered_map<Cube, std::vector<typename Cube::Twist>> map;

	void add_neighbours(const Cube& cube, int max_distance)
	{
		bool inserted = map.insert({ cube, twists }).second;

		if (max_distance == 0)
			return;

		if (!inserted) // already exists in map
		{
			std::size_t current_size = map[cube].size();
			std::size_t new_size = twists.size();
			if (new_size < current_size)
				map[cube] = twists;
			else
				return;
		}

		for (const auto& t : possible_twists)
		{
			twists.push_back(t);
			add_neighbours(cube.twisted(t), max_distance - 1);
			twists.pop_back();
		}
	}
public:
	explicit NeighbourGenerator(std::vector<typename Cube::Twist> twists) : possible_twists(std::move(twists)) {}

	std::unordered_map<Cube, std::vector<typename Cube::Twist>> generate(const Cube& origin, int min_distance, int max_distance)
	{
		twists.clear();
		twists.reserve(max_distance);
		map.clear();

		add_neighbours(origin, max_distance);

		// Remove cubes that are too close
		for (auto it = map.begin(); it != map.end();)
		{
			if (it->second.size() < min_distance)
				it = map.erase(it);
			else
				++it;
		}
		return map;
	}
};

// Returns a map of all possible cubes and their solutions, with a distance between min_distance and max_distance.
template <typename Cube>
std::unordered_map<Cube, std::vector<typename Cube::Twist>>
neighbours(
	const Cube& origin,
	int min_distance,
	int max_distance,
	std::vector<typename Cube::Twist> twists = Cube::twists)
{
	return NeighbourGenerator<Cube>{ std::move(twists) }.generate(origin, min_distance, max_distance);
}
