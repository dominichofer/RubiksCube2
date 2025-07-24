#include "pch.h"

TEST(Cube3x3, coset_index)
{
	RandomCubeGenerator<Cube3x3> gen{ 571543 };
	for (int i = 0; i < 1'000'000; i++)
	{
		auto cube = gen();
		auto index = cube.coset_index();
		EXPECT_GE(index, 0);
		EXPECT_LT(index, Cube3x3::set_size);
	}
}

TEST(Cube3x3, coset_number)
{
	RandomCubeGenerator<Cube3x3> gen{ 217635 };
	for (int i = 0; i < 1'000'000; i++)
	{
		auto cube = gen();
		auto index = cube.coset_number();
		EXPECT_GE(index, 0);
		EXPECT_LT(index, Cube3x3::cosets);
	}
}

static void test_twist(Twist t)
{
	auto n = Cube3x3{}.twisted(t);
	auto c = Corners{}.twisted(t);
	auto e = EdgesCenter{}.twisted(t);
	EXPECT_EQ(n.c_ori, c.ori_index());
	EXPECT_EQ(n.c_prm, c.prm_index());
	EXPECT_EQ(n.e_ori, e.ori_index());
	EXPECT_EQ(n.e_slice_prm, e.slice_prm_index());
	EXPECT_EQ(n.e_non_slice_prm, e.non_slice_prm_index());
	EXPECT_EQ(n.e_slice_loc, e.slice_loc_index());
}

TEST(Cube3x3, L1) { test_twist(Twist::L1); }
TEST(Cube3x3, R1) { test_twist(Twist::R1); }
TEST(Cube3x3, U1) { test_twist(Twist::U1); }
TEST(Cube3x3, D1) { test_twist(Twist::D1); }
TEST(Cube3x3, F1) { test_twist(Twist::F1); }
TEST(Cube3x3, B1) { test_twist(Twist::B1); }

TEST(Cube3x3, composed_twists)
{
	const auto c = Cube3x3{};
	EXPECT_EQ(c.twisted(Twist::L2), c.twisted({ Twist::L1, Twist::L1 }));
	EXPECT_EQ(c.twisted(Twist::L3), c.twisted({ Twist::L1, Twist::L1, Twist::L1 }));
	EXPECT_EQ(c.twisted(Twist::R2), c.twisted({ Twist::R1, Twist::R1 }));
	EXPECT_EQ(c.twisted(Twist::R3), c.twisted({ Twist::R1, Twist::R1, Twist::R1 }));
	EXPECT_EQ(c.twisted(Twist::U2), c.twisted({ Twist::U1, Twist::U1 }));
	EXPECT_EQ(c.twisted(Twist::U3), c.twisted({ Twist::U1, Twist::U1, Twist::U1 }));
	EXPECT_EQ(c.twisted(Twist::D2), c.twisted({ Twist::D1, Twist::D1 }));
	EXPECT_EQ(c.twisted(Twist::D3), c.twisted({ Twist::D1, Twist::D1, Twist::D1 }));
	EXPECT_EQ(c.twisted(Twist::F2), c.twisted({ Twist::F1, Twist::F1 }));
	EXPECT_EQ(c.twisted(Twist::F3), c.twisted({ Twist::F1, Twist::F1, Twist::F1 }));
	EXPECT_EQ(c.twisted(Twist::B2), c.twisted({ Twist::B1, Twist::B1 }));
	EXPECT_EQ(c.twisted(Twist::B3), c.twisted({ Twist::B1, Twist::B1, Twist::B1 }));
}

TEST(Cube3x3, inverse_twists)
{
	for (Twist t : all_twists)
		EXPECT_TRUE(Cube3x3{}.twisted({ t, inversed(t) }).is_solved());
}

TEST(Cube3x3, twists_cycle)
{
	for (Twist t : all_twists)
		EXPECT_TRUE(Cube3x3{}.twisted({ t, t, t, t }).is_solved());
}

static void expect_twists_commutate(Twist a, Twist b)
{
	EXPECT_EQ(Cube3x3{}.twisted({ a, b }), Cube3x3{}.twisted({ b, a }));
}

TEST(Cube3x3, twist_commutation)
{
	expect_twists_commutate(Twist::L1, Twist::R1);
	expect_twists_commutate(Twist::U1, Twist::D1);
	expect_twists_commutate(Twist::F1, Twist::B1);
}

TEST(Cube3x3, is_solved)
{
	EXPECT_TRUE(Cube3x3{}.is_solved());
	EXPECT_FALSE(Cube3x3{}.twisted(Twist::L1).is_solved());
}
