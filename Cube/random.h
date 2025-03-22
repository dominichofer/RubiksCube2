#pragma once
#include "Math/math.h"
#include "twist.h"
#include <random>
#include <vector>

class RandomTwistGenerator
{
	std::mt19937_64 rng;
	std::uniform_int_distribution<std::size_t> dist;
	std::vector<Twist> twists;
public:
	RandomTwistGenerator(std::vector<Twist> twists, unsigned int seed = std::random_device{}())
		: rng(seed)
		, twists(std::move(twists))
		, dist(0, this->twists.size() - 1)
	{}

	Twist operator()()
	{
		return twists[dist(rng)];
	}

	std::vector<Twist> operator()(int count)
	{
		std::vector<Twist> result;
		result.reserve(count);
		for (int i = 0; i < count; i++)
			result.push_back(this->operator()());
		return result;
	}
};

template <typename Cube>
class RandomCubeGenerator
{
	RandomTwistGenerator rnd_twists;
	Cube origin;
public:
	RandomCubeGenerator(Cube origin, std::vector<Twist> twists, unsigned int seed = std::random_device{}())
		: rnd_twists(twists, seed)
		, origin(origin)
	{}

	Cube operator()(int twist_count = 100)
	{
		return this->node(twist_count);
	}
};

template <typename Cube>
Cube RandomCube(unsigned int seed = std::random_device{}())
{
	return RandomCubeGenerator<Cube>{ seed }();
}

template <typename Cube>
std::vector<Cube> RandomCubes(std::size_t count, unsigned int seed = std::random_device{}())
{
	RandomCubeGenerator<Cube> rnd(seed);
	std::vector<Cube> cubes;
	cubes.reserve(count);
	for (std::size_t i = 0; i < count; i++)
		cubes.push_back(rnd());
	return cubes;
}
