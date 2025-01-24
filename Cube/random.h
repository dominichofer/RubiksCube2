#pragma once
#include <random>
#include <vector>

template <typename T>
class RandomCubeGenerator
{
	std::mt19937_64 rng;
	std::uniform_int_distribution<std::size_t> dist{ 0, T::twists.size() - 1 };
public:
	RandomCubeGenerator(unsigned int seed = std::random_device{}()) : rng(seed) {}

	T operator()(int rotations = 100)
	{
		T ret;
		for (int i = 0; i < rotations; i++)
			ret = ret.twisted(T::twists[dist(rng)]);
		return ret;
	}
};

template <typename T>
T RandomCube(unsigned int seed = std::random_device{}())
{
	return RandomCubeGenerator<T>{ seed }();
}

template <typename T>
std::vector<T> RandomCubes(std::size_t count, unsigned int seed = std::random_device{}())
{
	RandomCubeGenerator<T> rnd(seed);
	std::vector<T> cubes;
	cubes.reserve(count);
	for (std::size_t i = 0; i < count; i++)
		cubes.push_back(rnd());
	return cubes;
}
