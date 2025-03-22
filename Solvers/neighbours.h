#pragma once
#include "Math/math.h"
#include "Cube/cube.h"

template <typename Cube>
std::unordered_map<Cube, std::vector<typename Cube::Twist>> path_to_neighbours(
	int min_length,
	int max_length,
	const Cube& origin,
	std::vector<typename Cube::Twist> twists = Cube::twists)
{
	return path_to_neighbours(
		min_length,
		max_length,
		origin,
		twists,
		[](const Cube& cube, const Cube::Twist& twist) { return cube.twisted(twist); });
}

template <typename Cube>
std::unordered_map<Cube, std::vector<typename Cube::Twist>> path_to_neighbours(
	int max_length,
	const Cube& origin,
	std::vector<typename Cube::Twist> twists = Cube::twists)
{
	return path_to_neighbours(0, max_length, origin, twists);
}

template <typename Cube>
std::unordered_set<Cube> neighbours(
	int min_length,
	int max_length,
	const Cube& origin,
	std::vector<typename Cube::Twist> twists = Cube::twists)
{
	return neighbours(
		min_length,
		max_length,
		origin,
		twists,
		[](const Cube& cube, const Cube::Twist& twist) { return cube.twisted(twist); });
}

template <typename Cube>
std::unordered_set<Cube> neighbours(
	int max_length,
	const Cube& origin,
	std::vector<typename Cube::Twist> twists = Cube::twists)
{
	return neighbours(0, max_length, origin, twists);
}
