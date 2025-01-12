#pragma once
#include "Cube/cube.h"
#include <unordered_map>
#include <vector>

namespace
{
	template <typename Cube>
	void add_neighbours(
		std::unordered_map<Cube, std::vector<typename Cube::Twist>>& map,
		const Cube& cube,
		const std::vector<typename Cube::Twist>& twists,
		int max_distance)
	{
		auto result = map.insert({ cube, twists });

		if (max_distance == 0)
			return;

		if (!result.second) // already exists in map
		{
			std::size_t current_size = result.first->second.size();
			std::size_t new_size = twists.size();
			if (new_size >= current_size)
				return;
			result.first->second = twists;
		}

		for (typename Cube::Twist t : Cube::twists)
		{
			auto new_twists = twists;
			new_twists.push_back(t);
			add_neighbours(map, cube.twisted(t), new_twists, max_distance - 1);
		}
	}
}

// Returns a map of all possible cubes and their solutions, up to a certain distance.
template <typename Cube>
std::unordered_map<Cube, std::vector<typename Cube::Twist>> neighbours(Cube origin, int max_distance)
{
	std::unordered_map<Cube, std::vector<typename Cube::Twist>> map;
	add_neighbours(map, origin, {}, max_distance);
	return map;
}
