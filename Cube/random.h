#pragma once
#include "Math/math.h"
#include "twist.h"
#include <random>

class RandomTwistGenerator
{
	std::mt19937_64 rng;
	std::uniform_int_distribution<std::size_t> dist;
	std::vector<Twist> twists;
public:
	RandomTwistGenerator(std::vector<Twist> twists, unsigned int seed = std::random_device{}())
		: rng(seed)
		, twists(std::move(twists))
		, dist(0, twists.size() - 1)
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
	RandomCubeGenerator(unsigned int seed = std::random_device{}())
		: RandomCubeGenerator(Cube::solved(), Cube::twists, seed)
	{}

	Cube operator()(int twist_count = 100)
	{
		Cube cube = origin;
		for (int i = 0; i < twist_count; i++)
			cube = cube.twisted(rnd_twists());
		return cube;
	}
};

template <typename Cube>
Cube RandomCube(Cube origin, std::vector<Twist> twists, unsigned int seed = std::random_device{}())
{
	return RandomCubeGenerator{ origin, twists, seed }();
}

template <typename Cube>
Cube RandomCube(unsigned int seed = std::random_device{}())
{
	return RandomCubeGenerator<Cube>{ seed }();
}
