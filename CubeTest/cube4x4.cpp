#include "pch.h"

TEST(Cube4x4, L2) { EXPECT_EQ(Cube4x4().L2(), Cube4x4().L1().L1()); }
TEST(Cube4x4, L3) { EXPECT_EQ(Cube4x4().L3(), Cube4x4().L1().L1().L1()); }

TEST(Cube4x4, l2) { EXPECT_EQ(Cube4x4().l2(), Cube4x4().l1().l1()); }
TEST(Cube4x4, l3) { EXPECT_EQ(Cube4x4().l3(), Cube4x4().l1().l1().l1()); }

TEST(Cube4x4, R2) { EXPECT_EQ(Cube4x4().R2(), Cube4x4().R1().R1()); }
TEST(Cube4x4, R3) { EXPECT_EQ(Cube4x4().R3(), Cube4x4().R1().R1().R1()); }

TEST(Cube4x4, r2) { EXPECT_EQ(Cube4x4().r2(), Cube4x4().r1().r1()); }
TEST(Cube4x4, r3) { EXPECT_EQ(Cube4x4().r3(), Cube4x4().r1().r1().r1()); }

TEST(Cube4x4, U2) { EXPECT_EQ(Cube4x4().U2(), Cube4x4().U1().U1()); }
TEST(Cube4x4, U3) { EXPECT_EQ(Cube4x4().U3(), Cube4x4().U1().U1().U1()); }

TEST(Cube4x4, u2) { EXPECT_EQ(Cube4x4().u2(), Cube4x4().u1().u1()); }
TEST(Cube4x4, u3) { EXPECT_EQ(Cube4x4().u3(), Cube4x4().u1().u1().u1()); }

TEST(Cube4x4, D2) { EXPECT_EQ(Cube4x4().D2(), Cube4x4().D1().D1()); }
TEST(Cube4x4, D3) { EXPECT_EQ(Cube4x4().D3(), Cube4x4().D1().D1().D1()); }

TEST(Cube4x4, d2) { EXPECT_EQ(Cube4x4().d2(), Cube4x4().d1().d1()); }
TEST(Cube4x4, d3) { EXPECT_EQ(Cube4x4().d3(), Cube4x4().d1().d1().d1()); }

TEST(Cube4x4, F2) { EXPECT_EQ(Cube4x4().F2(), Cube4x4().F1().F1()); }
TEST(Cube4x4, F3) { EXPECT_EQ(Cube4x4().F3(), Cube4x4().F1().F1().F1()); }

TEST(Cube4x4, f2) { EXPECT_EQ(Cube4x4().f2(), Cube4x4().f1().f1()); }
TEST(Cube4x4, f3) { EXPECT_EQ(Cube4x4().f3(), Cube4x4().f1().f1().f1()); }

TEST(Cube4x4, B2) { EXPECT_EQ(Cube4x4().B2(), Cube4x4().B1().B1()); }
TEST(Cube4x4, B3) { EXPECT_EQ(Cube4x4().B3(), Cube4x4().B1().B1().B1()); }

TEST(Cube4x4, b2) { EXPECT_EQ(Cube4x4().b2(), Cube4x4().b1().b1()); }
TEST(Cube4x4, b3) { EXPECT_EQ(Cube4x4().b3(), Cube4x4().b1().b1().b1()); }

TEST(Cube4x4, inverse_rotations)
{
	EXPECT_EQ(Cube4x4().L1().L3(), Cube4x4());
	EXPECT_EQ(Cube4x4().l1().l3(), Cube4x4());
	EXPECT_EQ(Cube4x4().R1().R3(), Cube4x4());
	EXPECT_EQ(Cube4x4().r1().r3(), Cube4x4());
	EXPECT_EQ(Cube4x4().U1().U3(), Cube4x4());
	EXPECT_EQ(Cube4x4().u1().u3(), Cube4x4());
	EXPECT_EQ(Cube4x4().D1().D3(), Cube4x4());
	EXPECT_EQ(Cube4x4().d1().d3(), Cube4x4());
	EXPECT_EQ(Cube4x4().F1().F3(), Cube4x4());
	EXPECT_EQ(Cube4x4().f1().f3(), Cube4x4());
	EXPECT_EQ(Cube4x4().B1().B3(), Cube4x4());
	EXPECT_EQ(Cube4x4().b1().b3(), Cube4x4());

	EXPECT_EQ(Cube4x4().L2().L2(), Cube4x4());
	EXPECT_EQ(Cube4x4().l2().l2(), Cube4x4());
	EXPECT_EQ(Cube4x4().R2().R2(), Cube4x4());
	EXPECT_EQ(Cube4x4().r2().r2(), Cube4x4());
	EXPECT_EQ(Cube4x4().U2().U2(), Cube4x4());
	EXPECT_EQ(Cube4x4().u2().u2(), Cube4x4());
	EXPECT_EQ(Cube4x4().D2().D2(), Cube4x4());
	EXPECT_EQ(Cube4x4().d2().d2(), Cube4x4());
	EXPECT_EQ(Cube4x4().F2().F2(), Cube4x4());
	EXPECT_EQ(Cube4x4().f2().f2(), Cube4x4());
	EXPECT_EQ(Cube4x4().B2().B2(), Cube4x4());
	EXPECT_EQ(Cube4x4().b2().b2(), Cube4x4());
}

TEST(Cube4x4, full_rotation)
{
	EXPECT_EQ(Cube4x4().L1().L1().L1().L1(), Cube4x4());
	EXPECT_EQ(Cube4x4().l1().l1().l1().l1(), Cube4x4());
	EXPECT_EQ(Cube4x4().R1().R1().R1().R1(), Cube4x4());
	EXPECT_EQ(Cube4x4().r1().r1().r1().r1(), Cube4x4());
	EXPECT_EQ(Cube4x4().U1().U1().U1().U1(), Cube4x4());
	EXPECT_EQ(Cube4x4().u1().u1().u1().u1(), Cube4x4());
	EXPECT_EQ(Cube4x4().D1().D1().D1().D1(), Cube4x4());
	EXPECT_EQ(Cube4x4().d1().d1().d1().d1(), Cube4x4());
	EXPECT_EQ(Cube4x4().F1().F1().F1().F1(), Cube4x4());
	EXPECT_EQ(Cube4x4().f1().f1().f1().f1(), Cube4x4());
	EXPECT_EQ(Cube4x4().B1().B1().B1().B1(), Cube4x4());
	EXPECT_EQ(Cube4x4().b1().b1().b1().b1(), Cube4x4());

	EXPECT_EQ(Cube4x4().L2().L2(), Cube4x4());
	EXPECT_EQ(Cube4x4().l2().l2(), Cube4x4());
	EXPECT_EQ(Cube4x4().R2().R2(), Cube4x4());
	EXPECT_EQ(Cube4x4().r2().r2(), Cube4x4());
	EXPECT_EQ(Cube4x4().U2().U2(), Cube4x4());
	EXPECT_EQ(Cube4x4().u2().u2(), Cube4x4());
	EXPECT_EQ(Cube4x4().D2().D2(), Cube4x4());
	EXPECT_EQ(Cube4x4().d2().d2(), Cube4x4());
	EXPECT_EQ(Cube4x4().F2().F2(), Cube4x4());
	EXPECT_EQ(Cube4x4().f2().f2(), Cube4x4());
	EXPECT_EQ(Cube4x4().B2().B2(), Cube4x4());
	EXPECT_EQ(Cube4x4().b2().b2(), Cube4x4());
}

TEST(Cube4x4, commutating_rotations)
{
	EXPECT_EQ(Cube4x4().L1().l1(), Cube4x4().l1().L1());
	EXPECT_EQ(Cube4x4().L1().r1(), Cube4x4().r1().L1());
	EXPECT_EQ(Cube4x4().L1().R1(), Cube4x4().R1().L1());
	EXPECT_EQ(Cube4x4().l1().r1(), Cube4x4().r1().l1());
	EXPECT_EQ(Cube4x4().l1().R1(), Cube4x4().R1().l1());
	EXPECT_EQ(Cube4x4().r1().R1(), Cube4x4().R1().r1());

	EXPECT_EQ(Cube4x4().U1().u1(), Cube4x4().u1().U1());
	EXPECT_EQ(Cube4x4().U1().d1(), Cube4x4().d1().U1());
	EXPECT_EQ(Cube4x4().U1().D1(), Cube4x4().D1().U1());
	EXPECT_EQ(Cube4x4().u1().d1(), Cube4x4().d1().u1());
	EXPECT_EQ(Cube4x4().u1().D1(), Cube4x4().D1().u1());
	EXPECT_EQ(Cube4x4().d1().D1(), Cube4x4().D1().d1());

	EXPECT_EQ(Cube4x4().F1().f1(), Cube4x4().f1().F1());
	EXPECT_EQ(Cube4x4().F1().b1(), Cube4x4().b1().F1());
	EXPECT_EQ(Cube4x4().F1().B1(), Cube4x4().B1().F1());
	EXPECT_EQ(Cube4x4().f1().b1(), Cube4x4().b1().f1());
	EXPECT_EQ(Cube4x4().f1().B1(), Cube4x4().B1().f1());
	EXPECT_EQ(Cube4x4().b1().B1(), Cube4x4().B1().b1());
}
