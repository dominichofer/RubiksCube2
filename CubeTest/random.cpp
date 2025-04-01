#include "pch.h"
#include <unordered_set>

TEST(RandomTwistGenerator, is_deterministic)
{
	RandomTwistGenerator gen1{ Cube5x5::twists, 34987 }; // arbitrary seed
	RandomTwistGenerator gen2{ Cube5x5::twists, 34987 }; // arbitrary seed
	for (int i = 0; i < 1'000; i++)
		EXPECT_EQ(gen1(), gen2());
}

TEST(RandomTwistGenerator, generates_all_twists)
{
	RandomTwistGenerator gen{ Cube5x5::twists };
	std::unordered_set<Twist> generated_twists;
	for (int i = 0; i < 1'000; i++)
		generated_twists.insert(gen());
	EXPECT_EQ(generated_twists.size(), Cube5x5::twists.size());
}

TEST(RandomCubeGenerator, is_deterministic)
{
	RandomCubeGenerator<Cube5x5> gen1{ 34987 }; // arbitrary seed
	RandomCubeGenerator<Cube5x5> gen2{ 34987 }; // arbitrary seed
	for (int i = 0; i < 1'000; i++)
		EXPECT_EQ(gen1(), gen2());
}

TEST(RandomCubeGenerator, generates_different_states)
{
	RandomCubeGenerator<Cube5x5> gen;
	std::unordered_set<Cube5x5> states;
	for (int i = 0; i < 1'000; i++)
		states.insert(gen());
	EXPECT_GT(states.size(), 1);
}

TEST(RandomCube, is_deterministic)
{
	auto c1 = RandomCube<Cube5x5>(34987); // arbitrary seed
	auto c2 = RandomCube<Cube5x5>(34987); // arbitrary seed
	EXPECT_EQ(c1, c2);
}

TEST(RandomCube, generates_different_states)
{
	std::unordered_set<Cube5x5> states;
	for (int i = 0; i < 1'000; i++)
		states.insert(RandomCube<Cube5x5>());
	EXPECT_GT(states.size(), 1);
}
