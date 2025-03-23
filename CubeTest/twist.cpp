#include "pch.h"
#include <vector>

TEST(Twist, inversed_is_involution)
{
	std::vector<Twist> all_twists = {
		Twist::L1, Twist::L2, Twist::L3, Twist::l1, Twist::l2, Twist::l3,
		Twist::R1, Twist::R2, Twist::R3, Twist::r1, Twist::r2, Twist::r3,
		Twist::U1, Twist::U2, Twist::U3, Twist::u1, Twist::u2, Twist::u3,
		Twist::D1, Twist::D2, Twist::D3, Twist::d1, Twist::d2, Twist::d3,
		Twist::F1, Twist::F2, Twist::F3, Twist::f1, Twist::f2, Twist::f3,
		Twist::B1, Twist::B2, Twist::B3, Twist::b1, Twist::b2, Twist::b3,
		Twist::None
	};

	for (auto twist : all_twists)
		EXPECT_EQ(twist, inversed(inversed(twist)));

	EXPECT_EQ(all_twists, inversed(inversed(all_twists)));
}

using CubeTypes = ::testing::Types<Cube3x3, Cube4x4, Cube5x5, EdgesCenter, FacesSide>;

template <typename CubeType>
class TwistTest : public ::testing::Test {};

TYPED_TEST_SUITE(TwistTest, CubeTypes);

TYPED_TEST(TwistTest, composed_twists)
{
	const auto t = Cube5x5::solved();
	EXPECT_EQ(t.L2(), t.L1().L1());
	EXPECT_EQ(t.L3(), t.L1().L1().L1());
	EXPECT_EQ(t.R2(), t.R1().R1());
	EXPECT_EQ(t.R3(), t.R1().R1().R1());
	EXPECT_EQ(t.U2(), t.U1().U1());
	EXPECT_EQ(t.U3(), t.U1().U1().U1());
	EXPECT_EQ(t.D2(), t.D1().D1());
	EXPECT_EQ(t.D3(), t.D1().D1().D1());
	EXPECT_EQ(t.F2(), t.F1().F1());
	EXPECT_EQ(t.F3(), t.F1().F1().F1());
	EXPECT_EQ(t.B2(), t.B1().B1());
	EXPECT_EQ(t.B3(), t.B1().B1().B1());
	EXPECT_EQ(t.l2(), t.l1().l1());
	EXPECT_EQ(t.l3(), t.l1().l1().l1());
	EXPECT_EQ(t.r2(), t.r1().r1());
	EXPECT_EQ(t.r3(), t.r1().r1().r1());
	EXPECT_EQ(t.u2(), t.u1().u1());
	EXPECT_EQ(t.u3(), t.u1().u1().u1());
	EXPECT_EQ(t.d2(), t.d1().d1());
	EXPECT_EQ(t.d3(), t.d1().d1().d1());
	EXPECT_EQ(t.f2(), t.f1().f1());
	EXPECT_EQ(t.f3(), t.f1().f1().f1());
	EXPECT_EQ(t.b2(), t.b1().b1());
	EXPECT_EQ(t.b3(), t.b1().b1().b1());
}

TYPED_TEST(TwistTest, inverse_twists)
{
	const auto t = Cube5x5::solved();
	EXPECT_EQ(t.L1().L3(), t);
	EXPECT_EQ(t.L2().L2(), t);
	EXPECT_EQ(t.R1().R3(), t);
	EXPECT_EQ(t.R2().R2(), t);
	EXPECT_EQ(t.U1().U3(), t);
	EXPECT_EQ(t.U2().U2(), t);
	EXPECT_EQ(t.D1().D3(), t);
	EXPECT_EQ(t.D2().D2(), t);
	EXPECT_EQ(t.F1().F3(), t);
	EXPECT_EQ(t.F2().F2(), t);
	EXPECT_EQ(t.B1().B3(), t);
	EXPECT_EQ(t.B2().B2(), t);
	EXPECT_EQ(t.l1().l3(), t);
	EXPECT_EQ(t.l2().l2(), t);
	EXPECT_EQ(t.r1().r3(), t);
	EXPECT_EQ(t.r2().r2(), t);
	EXPECT_EQ(t.u1().u3(), t);
	EXPECT_EQ(t.u2().u2(), t);
	EXPECT_EQ(t.d1().d3(), t);
	EXPECT_EQ(t.d2().d2(), t);
	EXPECT_EQ(t.f1().f3(), t);
	EXPECT_EQ(t.f2().f2(), t);
	EXPECT_EQ(t.b1().b3(), t);
	EXPECT_EQ(t.b2().b2(), t);
}

TYPED_TEST(TwistTest, full_rotation)
{
	const auto t = Cube5x5::solved();
	EXPECT_EQ(t, t.L1().L1().L1().L1());
	EXPECT_EQ(t, t.R1().R1().R1().R1());
	EXPECT_EQ(t, t.U1().U1().U1().U1());
	EXPECT_EQ(t, t.D1().D1().D1().D1());
	EXPECT_EQ(t, t.F1().F1().F1().F1());
	EXPECT_EQ(t, t.B1().B1().B1().B1());
	EXPECT_EQ(t, t.l1().l1().l1().l1());
	EXPECT_EQ(t, t.r1().r1().r1().r1());
	EXPECT_EQ(t, t.u1().u1().u1().u1());
	EXPECT_EQ(t, t.d1().d1().d1().d1());
	EXPECT_EQ(t, t.f1().f1().f1().f1());
	EXPECT_EQ(t, t.b1().b1().b1().b1());
}

template <typename Twistable>
void expect_pairwise_commutation(const Twistable& t, Twist a, Twist b)
{
	EXPECT_EQ(t.twisted(a).twisted(b), t.twisted(b).twisted(a));
}

template <typename Twistable>
void expect_pairwise_commutation(const Twistable& t, Twist a, Twist b, Twist c, Twist d)
{
	expect_pairwise_commutation(t, a, b);
	expect_pairwise_commutation(t, a, c);
	expect_pairwise_commutation(t, a, d);
	expect_pairwise_commutation(t, b, c);
	expect_pairwise_commutation(t, b, d);
	expect_pairwise_commutation(t, c, d);
}

TYPED_TEST(TwistTest, commutating_twists)
{
	const auto t = Cube5x5::solved();
	expect_pairwise_commutation(t, Twist::L1, Twist::l1, Twist::R1, Twist::r1);
	expect_pairwise_commutation(t, Twist::U1, Twist::u1, Twist::D1, Twist::d1);
	expect_pairwise_commutation(t, Twist::F1, Twist::f1, Twist::B1, Twist::b1);
}
