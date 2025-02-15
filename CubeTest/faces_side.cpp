#include "pch.h"
#include <random>

TEST(FacesSide, default_is_solved)
{
	EXPECT_TRUE(FacesSide().is_solved());
}

TEST(FacesSide, twisted_is_not_solved)
{
	EXPECT_FALSE(FacesSide().l1().is_solved());
}

// Fuzz test
TEST(FacesSide, cubies)
{
	std::mt19937_64 rng;
	std::uniform_int_distribution<> dist(0, 23);
	std::vector<uint8_t> c(23);
	for (int i = 0; i < 1'000'000; i++)
	{
		for (int j = 0; j < 23; j++)
			c[j] = dist(rng);
		FacesSide faces(c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8], c[9], c[10], c[11], c[12], c[13], c[14], c[15], c[16], c[17], c[18], c[19], c[20], c[21], c[22], c[23]);
		for (int j = 0; j < 23; j++)
			EXPECT_EQ(faces.cubie(j), c[j]);
	}
}

const FacesSide X = FacesSide(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23);
const uint8_t a0 = 0, a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7;
const uint8_t b0 = 8, b1 = 9, b2 = 10, b3 = 11, b4 = 12, b5 = 13, b6 = 14, b7 = 15;
const uint8_t c0 = 16, c1 = 17, c2 = 18, c3 = 19, c4 = 20, c5 = 21, c6 = 22, c7 = 23;

TEST(FacesSide, L1) {
	EXPECT_EQ(
		X.L1(),
		FacesSide(
			a2, a0, a3, a1, a4, a5, a6, a7,
			b0, b1, b2, b3, b4, b5, b6, b7,
			c0, c1, c2, c3, c4, c5, c6, c7)
	);
}
TEST(FacesSide, L2) { EXPECT_EQ(X.L2(), X.L1().L1()); }
TEST(FacesSide, L3) { EXPECT_EQ(X.L3(), X.L1().L1().L1()); }
TEST(FacesSide, l1) {
	EXPECT_EQ(
		X.l1(),
		FacesSide(
			a0, a1, a2, a3, a4, a5, a6, a7,
			c7, b1, c5, b3, c0, b5, c2, b7,
			b0, c1, b2, c3, c4, b6, c6, b4)
	);
}
TEST(FacesSide, l2) { EXPECT_EQ(X.l2(), X.l1().l1()); }
TEST(FacesSide, l3) { EXPECT_EQ(X.l3(), X.l1().l1().l1()); }
TEST(FacesSide, r1) {
	EXPECT_EQ(
		X.r1(),
		FacesSide(
			a0, a1, a2, a3, a4, a5, a6, a7,
			b0, c1, b2, c3, b4, c6, b6, c4,
			c0, b5, c2, b7, b3, c5, b1, c7)
	);
}
TEST(FacesSide, r2) { EXPECT_EQ(X.r2(), X.r1().r1()); }
TEST(FacesSide, r3) { EXPECT_EQ(X.r3(), X.r1().r1().r1()); }
TEST(FacesSide, u1) {
	EXPECT_EQ(
		X.u1(),
		FacesSide(
			c0, c1, a2, a3, c4, c5, a6, a7,
			b0, b1, b2, b3, b4, b5, b6, b7,
			a4, a5, c2, c3, a0, a1, c6, c7)
	);
}
TEST(FacesSide, u2) { EXPECT_EQ(X.u2(), X.u1().u1()); }
TEST(FacesSide, u3) { EXPECT_EQ(X.u3(), X.u1().u1().u1()); }
TEST(FacesSide, d1) {
	EXPECT_EQ(
		X.d1(),
		FacesSide(
			a0, a1, c6, c7, a4, a5, c2, c3,
			b0, b1, b2, b3, b4, b5, b6, b7,
			c0, c1, a2, a3, c4, c5, a6, a7)
	);
}
TEST(FacesSide, d2) { EXPECT_EQ(X.d2(), X.d1().d1()); }
TEST(FacesSide, d3) { EXPECT_EQ(X.d3(), X.d1().d1().d1()); }
TEST(FacesSide, F1) {
	EXPECT_EQ(
		X.F1(),
		FacesSide(
			a0, a1, a2, a3, a4, a5, a6, a7,
			b0, b1, b2, b3, b4, b5, b6, b7,
			c2, c0, c3, c1, c4, c5, c6, c7)
	);
}
TEST(FacesSide, F2) { EXPECT_EQ(X.F2(), X.F1().F1()); }
TEST(FacesSide, F3) { EXPECT_EQ(X.F3(), X.F1().F1().F1()); }
TEST(FacesSide, f1) {
	EXPECT_EQ(
		X.f1(),
		FacesSide(
			a0, b4, a2, b5, b2, a5, b3, a7,
			b0, b1, a3, a1, a6, a4, b6, b7,
			c0, c1, c2, c3, c4, c5, c6, c7)
	);
}
TEST(FacesSide, f2) { EXPECT_EQ(X.f2(), X.f1().f1()); }
TEST(FacesSide, f3) { EXPECT_EQ(X.f3(), X.f1().f1().f1()); }
TEST(FacesSide, B1) {
	EXPECT_EQ(
		X.B1(),
		FacesSide(
			a0, a1, a2, a3, a4, a5, a6, a7,
			b0, b1, b2, b3, b4, b5, b6, b7,
			c0, c1, c2, c3, c6, c4, c7, c5)
	);
}
TEST(FacesSide, B2) { EXPECT_EQ(X.B2(), X.B1().B1()); }
TEST(FacesSide, B3) { EXPECT_EQ(X.B3(), X.B1().B1().B1()); }
TEST(FacesSide, b1) {
	EXPECT_EQ(
		X.b1(),
		FacesSide(
			b1, a1, b0, a3, a4, b7, a6, b6,
			a5, a7, b2, b3, b4, b5, a0, a2,
			c0, c1, c2, c3, c4, c5, c6, c7)
	);
}
TEST(FacesSide, b2) { EXPECT_EQ(X.b2(), X.b1().b1()); }
TEST(FacesSide, b3) { EXPECT_EQ(X.b3(), X.b1().b1().b1()); }

TEST(FacesSide, inverse_rotations)
{
	EXPECT_EQ(X.L1().L3(), X);
	EXPECT_EQ(X.l1().l3(), X);
	EXPECT_EQ(X.R1().R3(), X);
	EXPECT_EQ(X.r1().r3(), X);
	EXPECT_EQ(X.U1().U3(), X);
	EXPECT_EQ(X.u1().u3(), X);
	EXPECT_EQ(X.D1().D3(), X);
	EXPECT_EQ(X.d1().d3(), X);
	EXPECT_EQ(X.F1().F3(), X);
	EXPECT_EQ(X.f1().f3(), X);
	EXPECT_EQ(X.B1().B3(), X);
	EXPECT_EQ(X.b1().b3(), X);

	EXPECT_EQ(X.L2().L2(), X);
	EXPECT_EQ(X.l2().l2(), X);
	EXPECT_EQ(X.R2().R2(), X);
	EXPECT_EQ(X.r2().r2(), X);
	EXPECT_EQ(X.U2().U2(), X);
	EXPECT_EQ(X.u2().u2(), X);
	EXPECT_EQ(X.D2().D2(), X);
	EXPECT_EQ(X.d2().d2(), X);
	EXPECT_EQ(X.F2().F2(), X);
	EXPECT_EQ(X.f2().f2(), X);
	EXPECT_EQ(X.B2().B2(), X);
	EXPECT_EQ(X.b2().b2(), X);
}

TEST(FacesSide, full_rotation)
{
	EXPECT_EQ(X.L1().L1().L1().L1(), X);
	EXPECT_EQ(X.l1().l1().l1().l1(), X);
	EXPECT_EQ(X.R1().R1().R1().R1(), X);
	EXPECT_EQ(X.r1().r1().r1().r1(), X);
	EXPECT_EQ(X.U1().U1().U1().U1(), X);
	EXPECT_EQ(X.u1().u1().u1().u1(), X);
	EXPECT_EQ(X.D1().D1().D1().D1(), X);
	EXPECT_EQ(X.d1().d1().d1().d1(), X);
	EXPECT_EQ(X.F1().F1().F1().F1(), X);
	EXPECT_EQ(X.f1().f1().f1().f1(), X);
	EXPECT_EQ(X.B1().B1().B1().B1(), X);
	EXPECT_EQ(X.b1().b1().b1().b1(), X);

	EXPECT_EQ(X.L2().L2(), X);
	EXPECT_EQ(X.l2().l2(), X);
	EXPECT_EQ(X.R2().R2(), X);
	EXPECT_EQ(X.r2().r2(), X);
	EXPECT_EQ(X.U2().U2(), X);
	EXPECT_EQ(X.u2().u2(), X);
	EXPECT_EQ(X.D2().D2(), X);
	EXPECT_EQ(X.d2().d2(), X);
	EXPECT_EQ(X.F2().F2(), X);
	EXPECT_EQ(X.f2().f2(), X);
	EXPECT_EQ(X.B2().B2(), X);
	EXPECT_EQ(X.b2().b2(), X);
}

TEST(FacesSide, commutating_rotations)
{
	EXPECT_EQ(X.L1().l1(), X.l1().L1());
	EXPECT_EQ(X.L1().r1(), X.r1().L1());
	EXPECT_EQ(X.L1().R1(), X.R1().L1());
	EXPECT_EQ(X.l1().r1(), X.r1().l1());
	EXPECT_EQ(X.l1().R1(), X.R1().l1());
	EXPECT_EQ(X.r1().R1(), X.R1().r1());

	EXPECT_EQ(X.U1().u1(), X.u1().U1());
	EXPECT_EQ(X.U1().d1(), X.d1().U1());
	EXPECT_EQ(X.U1().D1(), X.D1().U1());
	EXPECT_EQ(X.u1().d1(), X.d1().u1());
	EXPECT_EQ(X.u1().D1(), X.D1().u1());
	EXPECT_EQ(X.d1().D1(), X.D1().d1());

	EXPECT_EQ(X.F1().f1(), X.f1().F1());
	EXPECT_EQ(X.F1().b1(), X.b1().F1());
	EXPECT_EQ(X.F1().B1(), X.B1().F1());
	EXPECT_EQ(X.f1().b1(), X.b1().f1());
	EXPECT_EQ(X.f1().B1(), X.B1().f1());
	EXPECT_EQ(X.b1().B1(), X.B1().b1());
}

TEST(FacesSide, prm_index)
{
	EXPECT_EQ(FacesSide().prm_index(), 0);
}

TEST(FacesSide, rotation_fuzzing)
{
	std::mt19937_64 rng;
	std::uniform_int_distribution<std::size_t> dist{ 0, FacesSide::twists.size() - 1 };
	FacesSide c;
	for (int i = 0; i < 1'000'000; i++)
	{
		auto old_c = c;
		auto twist = FacesSide::twists[dist(rng)];
		c = c.twisted(twist);

		bool is_legal = true;
		// Check that the cubies are in the range [0, 5].
		for (int i = 0; i < 24; i++)
			if (c.cubie(i) < 0 || c.cubie(i) > 5)
				is_legal = false;

		// Check that each cubie occurs exactly 4 times.
		for (int i = 0; i < 6; i++)
		{
			int count = 0;
			for (int j = 0; j < 24; j++)
				if (c.cubie(j) == i)
					count++;
			if (count != 4)
				is_legal = false;
		}

		if (!is_legal)
		{
			std::cout << "Old state:\n" << to_string(old_c) << std::endl;
			std::cout << "Twist: " << to_string(twist) << std::endl;
			std::cout << "New state:\n" << to_string(c) << std::endl;
			ASSERT_TRUE(false);
		}
	}
}
