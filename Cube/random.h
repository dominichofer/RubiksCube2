#pragma once
#include <random>

template <typename T>
class RandomCubeGenerator
{
	std::mt19937_64 rng;
	std::uniform_int_distribution<std::size_t> dist{ 0, T::twists.size() - 1 };
public:
	RandomCubeGenerator(unsigned int seed = std::random_device{}()) : rng(seed) {}

	T operator()(int rotations = 100)
	{
		T t;
		for (int i = 0; i < rotations; i++)
			t = t.twisted(T::twists[dist(rng)]);
		return t;
	}
};

template <typename T>
T RandomCube(unsigned int seed = std::random_device{}())
{
	return RandomCubeGenerator<T>{ seed }();
}
