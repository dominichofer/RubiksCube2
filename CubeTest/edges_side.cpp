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
TEST(EdgesSide, L2) { EXPECT_EQ(EdgesSide().L2(), EdgesSide().L1().L1()); }
TEST(EdgesSide, L3) { EXPECT_EQ(EdgesSide().L3(), EdgesSide().L1().L1().L1()); }
TEST(EdgesSide, l1) {
	EXPECT_EQ(
		EdgesSide().l1(),
		EdgesSide(
			a2, a1, a4, a3, a6, a5, a0, a7,
			b0, b1, b2, b3, b4, b5, b6, b7,
			c0, c1, c2, c3, c4, c5, c6, c7)
	);
}
TEST(EdgesSide, l2) { EXPECT_EQ(EdgesSide().l2(), EdgesSide().l1().l1()); }
TEST(EdgesSide, l3) { EXPECT_EQ(EdgesSide().l3(), EdgesSide().l1().l1().l1()); }
TEST(EdgesSide, R1) {
	EXPECT_EQ(
		EdgesSide().R1(),
		EdgesSide(
			a0, a1, a2, a3, a4, a5, a6, a7,
			b0, b1, c4, c5, c6, c7, b6, b7,
			c0, c1, c2, c3, b5, b4, b3, b2)
	);
}
TEST(EdgesSide, R2) { EXPECT_EQ(EdgesSide().R2(), EdgesSide().R1().R1()); }
TEST(EdgesSide, R3) { EXPECT_EQ(EdgesSide().R3(), EdgesSide().R1().R1().R1()); }
TEST(EdgesSide, r1) {
	EXPECT_EQ(
		EdgesSide().r1(),
		EdgesSide(
			a0, a7, a2, a1, a4, a3, a6, a5,
			b0, b1, b2, b3, b4, b5, b6, b7,
			c0, c1, c2, c3, c4, c5, c6, c7)
	);
}
TEST(EdgesSide, r2) { EXPECT_EQ(EdgesSide().r2(), EdgesSide().r1().r1()); }
TEST(EdgesSide, r3) { EXPECT_EQ(EdgesSide().r3(), EdgesSide().r1().r1().r1()); }
TEST(EdgesSide, U1) {
	EXPECT_EQ(
		EdgesSide().U1(),
		EdgesSide(
			c6, c7, c0, c1, a4, a5, a6, a7,
			b0, b1, b2, b3, b4, b5, b6, b7,
			a1, a0, c2, c3, c4, c5, a3, a2)
	);
}
TEST(EdgesSide, U2) { EXPECT_EQ(EdgesSide().U2(), EdgesSide().U1().U1()); }
TEST(EdgesSide, U3) { EXPECT_EQ(EdgesSide().U3(), EdgesSide().U1().U1().U1()); }
TEST(EdgesSide, u1) {
	EXPECT_EQ(
		EdgesSide().u1(),
		EdgesSide(
			a0, a1, a2, a3, a4, a5, a6, a7,
			b2, b1, b4, b3, b6, b5, b0, b7,
			c0, c1, c2, c3, c4, c5, c6, c7)
	);
}
TEST(EdgesSide, u2) { EXPECT_EQ(EdgesSide().u2(), EdgesSide().u1().u1()); }
TEST(EdgesSide, u3) { EXPECT_EQ(EdgesSide().u3(), EdgesSide().u1().u1().u1()); }
TEST(EdgesSide, D1) {
	EXPECT_EQ(
		EdgesSide().D1(),
		EdgesSide(
			a0, a1, a2, a3, c5, c4, c3, c2,
			b0, b1, b2, b3, b4, b5, b6, b7,
			c0, c1, a4, a5, a6, a7, c6, c7)
	);
}
TEST(EdgesSide, D2) { EXPECT_EQ(EdgesSide().D2(), EdgesSide().D1().D1()); }
TEST(EdgesSide, D3) { EXPECT_EQ(EdgesSide().D3(), EdgesSide().D1().D1().D1()); }
TEST(EdgesSide, d1) {
	EXPECT_EQ(
		EdgesSide().d1(),
		EdgesSide(
			a0, a1, a2, a3, a4, a5, a6, a7,
			b0, b7, b2, b1, b4, b3, b6, b5,
			c0, c1, c2, c3, c4, c5, c6, c7)
	);
}
TEST(EdgesSide, d2) { EXPECT_EQ(EdgesSide().d2(), EdgesSide().d1().d1()); }
TEST(EdgesSide, d3) { EXPECT_EQ(EdgesSide().d3(), EdgesSide().d1().d1().d1()); }
TEST(EdgesSide, F1) {
	EXPECT_EQ(
		EdgesSide().F1(),
		EdgesSide(
			b1, b0, a2, a3, a4, a5, b3, b2,
			a6, a7, a0, a1, b4, b5, b6, b7,
			c0, c1, c2, c3, c4, c5, c6, c7)
	);
}
TEST(EdgesSide, F2) { EXPECT_EQ(EdgesSide().F2(), EdgesSide().F1().F1()); }
TEST(EdgesSide, F3) { EXPECT_EQ(EdgesSide().F3(), EdgesSide().F1().F1().F1()); }
TEST(EdgesSide, f1) {
	EXPECT_EQ(
		EdgesSide().f1(),
		EdgesSide(
			a0, a1, a2, a3, a4, a5, a6, a7,
			b0, b1, b2, b3, b4, b5, b6, b7,
			c2, c1, c4, c3, c6, c5, c0, c7)
	);
}
TEST(EdgesSide, f2) { EXPECT_EQ(EdgesSide().f2(), EdgesSide().f1().f1()); }
TEST(EdgesSide, f3) { EXPECT_EQ(EdgesSide().f3(), EdgesSide().f1().f1().f1()); }
TEST(EdgesSide, B1) {
	EXPECT_EQ(
		EdgesSide().B1(),
		EdgesSide(
			a0, a1, b4, b5, b6, b7, a6, a7,
			b0, b1, b2, b3, a5, a4, a3, a2,
			c0, c1, c2, c3, c4, c5, c6, c7)
	);
}
TEST(EdgesSide, B2) { EXPECT_EQ(EdgesSide().B2(), EdgesSide().B1().B1()); }
TEST(EdgesSide, B3) { EXPECT_EQ(EdgesSide().B3(), EdgesSide().B1().B1().B1()); }
TEST(EdgesSide, b1) {
	EXPECT_EQ(
		EdgesSide().b1(),
		EdgesSide(
			a0, a1, a2, a3, a4, a5, a6, a7,
			b0, b1, b2, b3, b4, b5, b6, b7,
			c0, c7, c2, c1, c4, c3, c6, c5)
	);
}

TEST(EdgesSide, inverse_rotations)
{
	EXPECT_EQ(EdgesSide().L1().L3(), EdgesSide());
	EXPECT_EQ(EdgesSide().l1().l3(), EdgesSide());
	EXPECT_EQ(EdgesSide().R1().R3(), EdgesSide());
	EXPECT_EQ(EdgesSide().r1().r3(), EdgesSide());
	EXPECT_EQ(EdgesSide().U1().U3(), EdgesSide());
	EXPECT_EQ(EdgesSide().u1().u3(), EdgesSide());
	EXPECT_EQ(EdgesSide().D1().D3(), EdgesSide());
	EXPECT_EQ(EdgesSide().d1().d3(), EdgesSide());
	EXPECT_EQ(EdgesSide().F1().F3(), EdgesSide());
	EXPECT_EQ(EdgesSide().f1().f3(), EdgesSide());
	EXPECT_EQ(EdgesSide().B1().B3(), EdgesSide());
	EXPECT_EQ(EdgesSide().b1().b3(), EdgesSide());

	EXPECT_EQ(EdgesSide().L2().L2(), EdgesSide());
	EXPECT_EQ(EdgesSide().l2().l2(), EdgesSide());
	EXPECT_EQ(EdgesSide().R2().R2(), EdgesSide());
	EXPECT_EQ(EdgesSide().r2().r2(), EdgesSide());
	EXPECT_EQ(EdgesSide().U2().U2(), EdgesSide());
	EXPECT_EQ(EdgesSide().u2().u2(), EdgesSide());
	EXPECT_EQ(EdgesSide().D2().D2(), EdgesSide());
	EXPECT_EQ(EdgesSide().d2().d2(), EdgesSide());
	EXPECT_EQ(EdgesSide().F2().F2(), EdgesSide());
	EXPECT_EQ(EdgesSide().f2().f2(), EdgesSide());
	EXPECT_EQ(EdgesSide().B2().B2(), EdgesSide());
	EXPECT_EQ(EdgesSide().b2().b2(), EdgesSide());
}

TEST(EdgesSide, full_rotation)
{
	EXPECT_EQ(EdgesSide().L1().L1().L1().L1(), EdgesSide());
	EXPECT_EQ(EdgesSide().l1().l1().l1().l1(), EdgesSide());
	EXPECT_EQ(EdgesSide().R1().R1().R1().R1(), EdgesSide());
	EXPECT_EQ(EdgesSide().r1().r1().r1().r1(), EdgesSide());
	EXPECT_EQ(EdgesSide().U1().U1().U1().U1(), EdgesSide());
	EXPECT_EQ(EdgesSide().u1().u1().u1().u1(), EdgesSide());
	EXPECT_EQ(EdgesSide().D1().D1().D1().D1(), EdgesSide());
	EXPECT_EQ(EdgesSide().d1().d1().d1().d1(), EdgesSide());
	EXPECT_EQ(EdgesSide().F1().F1().F1().F1(), EdgesSide());
	EXPECT_EQ(EdgesSide().f1().f1().f1().f1(), EdgesSide());
	EXPECT_EQ(EdgesSide().B1().B1().B1().B1(), EdgesSide());
	EXPECT_EQ(EdgesSide().b1().b1().b1().b1(), EdgesSide());

	EXPECT_EQ(EdgesSide().L2().L2(), EdgesSide());
	EXPECT_EQ(EdgesSide().l2().l2(), EdgesSide());
	EXPECT_EQ(EdgesSide().R2().R2(), EdgesSide());
	EXPECT_EQ(EdgesSide().r2().r2(), EdgesSide());
	EXPECT_EQ(EdgesSide().U2().U2(), EdgesSide());
	EXPECT_EQ(EdgesSide().u2().u2(), EdgesSide());
	EXPECT_EQ(EdgesSide().D2().D2(), EdgesSide());
	EXPECT_EQ(EdgesSide().d2().d2(), EdgesSide());
	EXPECT_EQ(EdgesSide().F2().F2(), EdgesSide());
	EXPECT_EQ(EdgesSide().f2().f2(), EdgesSide());
	EXPECT_EQ(EdgesSide().B2().B2(), EdgesSide());
	EXPECT_EQ(EdgesSide().b2().b2(), EdgesSide());
}

TEST(EdgesSide, commutating_rotations)
{
	EXPECT_EQ(EdgesSide().L1().l1(), EdgesSide().l1().L1());
	EXPECT_EQ(EdgesSide().L1().r1(), EdgesSide().r1().L1());
	EXPECT_EQ(EdgesSide().L1().R1(), EdgesSide().R1().L1());
	EXPECT_EQ(EdgesSide().l1().r1(), EdgesSide().r1().l1());
	EXPECT_EQ(EdgesSide().l1().R1(), EdgesSide().R1().l1());
	EXPECT_EQ(EdgesSide().r1().R1(), EdgesSide().R1().r1());

	EXPECT_EQ(EdgesSide().U1().u1(), EdgesSide().u1().U1());
	EXPECT_EQ(EdgesSide().U1().d1(), EdgesSide().d1().U1());
	EXPECT_EQ(EdgesSide().U1().D1(), EdgesSide().D1().U1());
	EXPECT_EQ(EdgesSide().u1().d1(), EdgesSide().d1().u1());
	EXPECT_EQ(EdgesSide().u1().D1(), EdgesSide().D1().u1());
	EXPECT_EQ(EdgesSide().d1().D1(), EdgesSide().D1().d1());

	EXPECT_EQ(EdgesSide().F1().f1(), EdgesSide().f1().F1());
	EXPECT_EQ(EdgesSide().F1().b1(), EdgesSide().b1().F1());
	EXPECT_EQ(EdgesSide().F1().B1(), EdgesSide().B1().F1());
	EXPECT_EQ(EdgesSide().f1().b1(), EdgesSide().b1().f1());
	EXPECT_EQ(EdgesSide().f1().B1(), EdgesSide().B1().f1());
	EXPECT_EQ(EdgesSide().b1().B1(), EdgesSide().B1().b1());
}
