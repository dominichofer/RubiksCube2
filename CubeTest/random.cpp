#include "pch.h"

TEST(RandomCubeGenerator, does_not_throw)
{
	RandomCubeGenerator<Corners> rnd_c;
	RandomCubeGenerator<EdgesCenter> rnd_ec;
	RandomCubeGenerator<EdgesSide> rnd_es;
	RandomCubeGenerator<FacesCenter> rnd_fc;
	RandomCubeGenerator<FacesSide> rnd_fs;
	RandomCubeGenerator<Cube2x2> rnd_2;
	RandomCubeGenerator<Cube3x3> rnd_3;
	RandomCubeGenerator<Cube4x4> rnd_4;
	RandomCubeGenerator<Cube5x5> rnd_5;
	EXPECT_NO_THROW(rnd_c());
	EXPECT_NO_THROW(rnd_ec());
	EXPECT_NO_THROW(rnd_es());
	EXPECT_NO_THROW(rnd_fc());
	EXPECT_NO_THROW(rnd_fs());
	EXPECT_NO_THROW(rnd_2());
	EXPECT_NO_THROW(rnd_3());
	EXPECT_NO_THROW(rnd_4());
	EXPECT_NO_THROW(rnd_5());
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

TEST(RandomCube, does_not_throw)
{
	EXPECT_NO_THROW(RandomCube<Corners>());
	EXPECT_NO_THROW(RandomCube<EdgesCenter>());
	EXPECT_NO_THROW(RandomCube<EdgesSide>());
	EXPECT_NO_THROW(RandomCube<FacesCenter>());
	EXPECT_NO_THROW(RandomCube<FacesSide>());
	EXPECT_NO_THROW(RandomCube<Cube2x2>());
	EXPECT_NO_THROW(RandomCube<Cube3x3>());
	EXPECT_NO_THROW(RandomCube<Cube4x4>());
	EXPECT_NO_THROW(RandomCube<Cube5x5>());
}

TEST(RandomCube, is_deterministic)
{
	EXPECT_EQ(RandomCube<Corners>(34987), RandomCube<Corners>(34987));
}

TEST(RandomCube, is_random)
{
	EXPECT_NE(RandomCube<Corners>(), RandomCube<Corners>());
}
