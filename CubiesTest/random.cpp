#include "pch.h"

TEST(RandomCubeGenerator, with_corners)
{
	RandomCubeGenerator<Corners> rnd;
	EXPECT_NO_THROW(rnd());
}

TEST(RandomCubeGenerator, with_edges_center)
{
	RandomCubeGenerator<EdgesCenter> rnd;
	EXPECT_NO_THROW(rnd());
}

TEST(RandomCubeGenerator, is_deterministic)
{
	RandomCubeGenerator<Corners> rnd1(34987);
	RandomCubeGenerator<Corners> rnd2(34987);
	EXPECT_EQ(rnd1(), rnd2());
}

TEST(RandomCubeGenerator, is_random)
{
	RandomCubeGenerator<Corners> rnd;
	EXPECT_NE(rnd(), rnd());
}

TEST(RandomCube, with_corners)
{
	EXPECT_NO_THROW(RandomCube<Corners>());
}

TEST(RandomCube, with_edges_center)
{
	EXPECT_NO_THROW(RandomCube<EdgesCenter>());
}

TEST(RandomCube, is_deterministic)
{
	EXPECT_EQ(RandomCube<Corners>(34987), RandomCube<Corners>(34987));
}

TEST(RandomCube, is_random)
{
	EXPECT_NE(RandomCube<Corners>(), RandomCube<Corners>());
}
