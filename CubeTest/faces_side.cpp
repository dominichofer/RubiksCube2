#include "pch.h"
#include <random>

TEST(FacesSide, default_is_solved)
{
	EXPECT_TRUE(FacesSide::solved().is_solved());
}

TEST(FacesSide, twisted_is_not_solved)
{
	EXPECT_FALSE(FacesSide::solved().l1().is_solved());
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
TEST(FacesSide, l1) {
	EXPECT_EQ(
		X.l1(),
		FacesSide(
			a0, a1, a2, a3, a4, a5, a6, a7,
			c7, b1, c5, b3, c0, b5, c2, b7,
			b0, c1, b2, c3, c4, b6, c6, b4)
	);
}
TEST(FacesSide, r1) {
	EXPECT_EQ(
		X.r1(),
		FacesSide(
			a0, a1, a2, a3, a4, a5, a6, a7,
			b0, c1, b2, c3, b4, c6, b6, c4,
			c0, b5, c2, b7, b3, c5, b1, c7)
	);
}
TEST(FacesSide, u1) {
	EXPECT_EQ(
		X.u1(),
		FacesSide(
			c0, c1, a2, a3, c4, c5, a6, a7,
			b0, b1, b2, b3, b4, b5, b6, b7,
			a4, a5, c2, c3, a0, a1, c6, c7)
	);
}
TEST(FacesSide, d1) {
	EXPECT_EQ(
		X.d1(),
		FacesSide(
			a0, a1, c6, c7, a4, a5, c2, c3,
			b0, b1, b2, b3, b4, b5, b6, b7,
			c0, c1, a2, a3, c4, c5, a6, a7)
	);
}
TEST(FacesSide, F1) {
	EXPECT_EQ(
		X.F1(),
		FacesSide(
			a0, a1, a2, a3, a4, a5, a6, a7,
			b0, b1, b2, b3, b4, b5, b6, b7,
			c2, c0, c3, c1, c4, c5, c6, c7)
	);
}
TEST(FacesSide, f1) {
	EXPECT_EQ(
		X.f1(),
		FacesSide(
			a0, b4, a2, b5, b2, a5, b3, a7,
			b0, b1, a3, a1, a6, a4, b6, b7,
			c0, c1, c2, c3, c4, c5, c6, c7)
	);
}
TEST(FacesSide, B1) {
	EXPECT_EQ(
		X.B1(),
		FacesSide(
			a0, a1, a2, a3, a4, a5, a6, a7,
			b0, b1, b2, b3, b4, b5, b6, b7,
			c0, c1, c2, c3, c6, c4, c7, c5)
	);
}
TEST(FacesSide, b1) {
	EXPECT_EQ(
		X.b1(),
		FacesSide(
			b1, a1, b0, a3, a4, b7, a6, b6,
			a5, a7, b2, b3, b4, b5, a0, a2,
			c0, c1, c2, c3, c4, c5, c6, c7)
	);
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
