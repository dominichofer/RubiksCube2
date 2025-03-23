#include "pch.h"
#include <random>

TEST(EdgesSide, default_is_solved)
{
	EXPECT_TRUE(EdgesSide().is_solved());
}

TEST(EdgesSide, twisted_is_not_solved)
{
	EXPECT_FALSE(EdgesSide().L1().is_solved());
}

// Fuzz test
TEST(EdgesSide, cubies)
{
	std::mt19937_64 rng;
	std::uniform_int_distribution<> dist(0, 23);
	std::vector<uint8_t> c(23);
	for (int i = 0; i < 1'000'000; i++)
	{
		for (int j = 0; j < 23; j++)
			c[j] = dist(rng);
		EdgesSide edges(c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8], c[9], c[10], c[11], c[12], c[13], c[14], c[15], c[16], c[17], c[18], c[19], c[20], c[21], c[22], c[23]);
		for (int j = 0; j < 23; j++)
			EXPECT_EQ(edges.cubie(j), c[j]);
	}
}

const uint8_t a0 = 0, a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7;
const uint8_t b0 = 8, b1 = 9, b2 = 10, b3 = 11, b4 = 12, b5 = 13, b6 = 14, b7 = 15;
const uint8_t c0 = 16, c1 = 17, c2 = 18, c3 = 19, c4 = 20, c5 = 21, c6 = 22, c7 = 23;

TEST(EdgesSide, L1) {
	EXPECT_EQ(
		EdgesSide().L1(),
		EdgesSide(
			a0, a1, a2, a3, a4, a5, a6, a7,
			c1, c0, b2, b3, b4, b5, c3, c2,
			b6, b7, b0, b1, c4, c5, c6, c7)
	);
}
TEST(EdgesSide, l1) {
	EXPECT_EQ(
		EdgesSide().l1(),
		EdgesSide(
			a2, a1, a4, a3, a6, a5, a0, a7,
			b0, b1, b2, b3, b4, b5, b6, b7,
			c0, c1, c2, c3, c4, c5, c6, c7)
	);
}
TEST(EdgesSide, R1) {
	EXPECT_EQ(
		EdgesSide().R1(),
		EdgesSide(
			a0, a1, a2, a3, a4, a5, a6, a7,
			b0, b1, c4, c5, c6, c7, b6, b7,
			c0, c1, c2, c3, b5, b4, b3, b2)
	);
}
TEST(EdgesSide, r1) {
	EXPECT_EQ(
		EdgesSide().r1(),
		EdgesSide(
			a0, a7, a2, a1, a4, a3, a6, a5,
			b0, b1, b2, b3, b4, b5, b6, b7,
			c0, c1, c2, c3, c4, c5, c6, c7)
	);
}
TEST(EdgesSide, U1) {
	EXPECT_EQ(
		EdgesSide().U1(),
		EdgesSide(
			c6, c7, c0, c1, a4, a5, a6, a7,
			b0, b1, b2, b3, b4, b5, b6, b7,
			a1, a0, c2, c3, c4, c5, a3, a2)
	);
}
TEST(EdgesSide, u1) {
	EXPECT_EQ(
		EdgesSide().u1(),
		EdgesSide(
			a0, a1, a2, a3, a4, a5, a6, a7,
			b2, b1, b4, b3, b6, b5, b0, b7,
			c0, c1, c2, c3, c4, c5, c6, c7)
	);
}
TEST(EdgesSide, D1) {
	EXPECT_EQ(
		EdgesSide().D1(),
		EdgesSide(
			a0, a1, a2, a3, c5, c4, c3, c2,
			b0, b1, b2, b3, b4, b5, b6, b7,
			c0, c1, a4, a5, a6, a7, c6, c7)
	);
}
TEST(EdgesSide, d1) {
	EXPECT_EQ(
		EdgesSide().d1(),
		EdgesSide(
			a0, a1, a2, a3, a4, a5, a6, a7,
			b0, b7, b2, b1, b4, b3, b6, b5,
			c0, c1, c2, c3, c4, c5, c6, c7)
	);
}
TEST(EdgesSide, F1) {
	EXPECT_EQ(
		EdgesSide().F1(),
		EdgesSide(
			b1, b0, a2, a3, a4, a5, b3, b2,
			a6, a7, a0, a1, b4, b5, b6, b7,
			c0, c1, c2, c3, c4, c5, c6, c7)
	);
}
TEST(EdgesSide, f1) {
	EXPECT_EQ(
		EdgesSide().f1(),
		EdgesSide(
			a0, a1, a2, a3, a4, a5, a6, a7,
			b0, b1, b2, b3, b4, b5, b6, b7,
			c2, c1, c4, c3, c6, c5, c0, c7)
	);
}
TEST(EdgesSide, B1) {
	EXPECT_EQ(
		EdgesSide().B1(),
		EdgesSide(
			a0, a1, b4, b5, b6, b7, a6, a7,
			b0, b1, b2, b3, a5, a4, a3, a2,
			c0, c1, c2, c3, c4, c5, c6, c7)
	);
}
TEST(EdgesSide, b1) {
	EXPECT_EQ(
		EdgesSide().b1(),
		EdgesSide(
			a0, a1, a2, a3, a4, a5, a6, a7,
			b0, b1, b2, b3, b4, b5, b6, b7,
			c0, c7, c2, c1, c4, c3, c6, c5)
	);
}
