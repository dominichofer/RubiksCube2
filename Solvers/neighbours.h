#pragma once
#include "Math/math.h"
#include "Cubie/cubie.h"

template <typename Cube>
std::unordered_map<Cube, Twists> path_to_neighbours(
	int min_length,
	int max_length,
	const Cube& origin,
	Twists twists = all_twists)
{
	return path_to_neighbours(
		min_length,
		max_length,
		origin,
		twists,
		[](const Cube& cube, const Twist& twist) { return cube.twisted(twist); });
}

template <typename Cube>
std::unordered_map<Cube, Twists> path_to_neighbours(
	int max_length,
	const Cube& origin,
	Twists twists = all_twists)
{
	return path_to_neighbours(0, max_length, origin, twists);
}

template <typename Cube>
std::unordered_set<Cube> neighbours(
	int min_length,
	int max_length,
	const Cube& origin,
	Twists twists = all_twists)
{
	return neighbours(
		min_length,
		max_length,
		origin,
		twists,
		[](const Cube& cube, const Twist& twist) { return cube.twisted(twist); });
}

template <typename Cube>
std::unordered_set<Cube> neighbours(
	int max_length,
	const Cube& origin,
	Twists twists = all_twists)
{
	return neighbours(0, max_length, origin, twists);
}
