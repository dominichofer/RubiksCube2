#include "pch.h"

TEST(Cube2x2, L2) { EXPECT_EQ(Cube2x2().L2(), Cube2x2().L1().L1()); }
TEST(Cube2x2, L3) { EXPECT_EQ(Cube2x2().L3(), Cube2x2().L1().L1().L1()); }

TEST(Cube2x2, R2) { EXPECT_EQ(Cube2x2().R2(), Cube2x2().R1().R1()); }
TEST(Cube2x2, R3) { EXPECT_EQ(Cube2x2().R3(), Cube2x2().R1().R1().R1()); }

TEST(Cube2x2, U2) { EXPECT_EQ(Cube2x2().U2(), Cube2x2().U1().U1()); }
TEST(Cube2x2, U3) { EXPECT_EQ(Cube2x2().U3(), Cube2x2().U1().U1().U1()); }

TEST(Cube2x2, D2) { EXPECT_EQ(Cube2x2().D2(), Cube2x2().D1().D1()); }
TEST(Cube2x2, D3) { EXPECT_EQ(Cube2x2().D3(), Cube2x2().D1().D1().D1()); }

TEST(Cube2x2, F2) { EXPECT_EQ(Cube2x2().F2(), Cube2x2().F1().F1()); }
TEST(Cube2x2, F3) { EXPECT_EQ(Cube2x2().F3(), Cube2x2().F1().F1().F1()); }

TEST(Cube2x2, B2) { EXPECT_EQ(Cube2x2().B2(), Cube2x2().B1().B1()); }
TEST(Cube2x2, B3) { EXPECT_EQ(Cube2x2().B3(), Cube2x2().B1().B1().B1()); }

TEST(Cube2x2, inverse_rotations)
{
	EXPECT_EQ(Cube2x2().L1().L3(), Cube2x2());
	EXPECT_EQ(Cube2x2().R1().R3(), Cube2x2());
	EXPECT_EQ(Cube2x2().U1().U3(), Cube2x2());
	EXPECT_EQ(Cube2x2().D1().D3(), Cube2x2());
	EXPECT_EQ(Cube2x2().F1().F3(), Cube2x2());
	EXPECT_EQ(Cube2x2().B1().B3(), Cube2x2());

	EXPECT_EQ(Cube2x2().L2().L2(), Cube2x2());
	EXPECT_EQ(Cube2x2().R2().R2(), Cube2x2());
	EXPECT_EQ(Cube2x2().U2().U2(), Cube2x2());
	EXPECT_EQ(Cube2x2().D2().D2(), Cube2x2());
	EXPECT_EQ(Cube2x2().F2().F2(), Cube2x2());
	EXPECT_EQ(Cube2x2().B2().B2(), Cube2x2());
}

TEST(Cube2x2, full_rotation)
{
	EXPECT_EQ(Cube2x2().L1().L1().L1().L1(), Cube2x2());
	EXPECT_EQ(Cube2x2().R1().R1().R1().R1(), Cube2x2());
	EXPECT_EQ(Cube2x2().U1().U1().U1().U1(), Cube2x2());
	EXPECT_EQ(Cube2x2().D1().D1().D1().D1(), Cube2x2());
	EXPECT_EQ(Cube2x2().F1().F1().F1().F1(), Cube2x2());
	EXPECT_EQ(Cube2x2().B1().B1().B1().B1(), Cube2x2());

	EXPECT_EQ(Cube2x2().L2().L2(), Cube2x2());
	EXPECT_EQ(Cube2x2().R2().R2(), Cube2x2());
	EXPECT_EQ(Cube2x2().U2().U2(), Cube2x2());
	EXPECT_EQ(Cube2x2().D2().D2(), Cube2x2());
	EXPECT_EQ(Cube2x2().F2().F2(), Cube2x2());
	EXPECT_EQ(Cube2x2().B2().B2(), Cube2x2());
}

TEST(Cube2x2, commutating_rotations)
{
	EXPECT_EQ(Cube2x2().L1().R1(), Cube2x2().R1().L1());
	EXPECT_EQ(Cube2x2().U1().D1(), Cube2x2().D1().U1());
	EXPECT_EQ(Cube2x2().F1().B1(), Cube2x2().B1().F1());
}
