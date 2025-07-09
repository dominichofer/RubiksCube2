#include "pch.h"
#include <unordered_set>

TEST(RandomTwistGenerator, is_deterministic)
{
	RandomTwistGenerator gen1{ 34987 }; // arbitrary seed
	RandomTwistGenerator gen2{ 34987 }; // arbitrary seed
	for (int i = 0; i < 1'000; i++)
		EXPECT_EQ(gen1(), gen2());
}

TEST(RandomTwistGenerator, generates_all_twists)
{
	RandomTwistGenerator gen{ 34987 };
	std::unordered_set<Twist> generated_twists;
	for (int i = 0; i < 1'000; i++)
		generated_twists.insert(gen());
	EXPECT_EQ(generated_twists.size(), all_twists.size());
}

TEST(RandomCubeGenerator, is_deterministic)
{
	RandomCubeGenerator<Corners> gen1{ 34987 }; // arbitrary seed
	RandomCubeGenerator<Corners> gen2{ 34987 }; // arbitrary seed
	for (int i = 0; i < 1'000; i++)
		EXPECT_EQ(gen1(), gen2());
}

TEST(RandomCube, is_deterministic)
{
	auto c1 = RandomCube<Corners>(34987); // arbitrary seed
	auto c2 = RandomCube<Corners>(34987); // arbitrary seed
	EXPECT_EQ(c1, c2);
}
