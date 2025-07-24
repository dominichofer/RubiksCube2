#include "pch.h"

TEST(EdgesCenter, index)
{
	RandomCubeGenerator<EdgesCenter> gen{ 928322 };
	for (int i = 0; i < 1'000'000; i++)
	{
		EdgesCenter e1 = gen();

		auto slice_prm = e1.slice_prm_index();
		ASSERT_GE(slice_prm, 0);
		ASSERT_LT(slice_prm, EdgesCenter::slice_prm_size);

		auto non_slice_prm = e1.non_slice_prm_index();
		ASSERT_GE(non_slice_prm, 0);
		ASSERT_LT(non_slice_prm, EdgesCenter::non_slice_prm_size);

		auto slice_loc = e1.slice_loc_index();
		ASSERT_GE(slice_loc, 0);
		ASSERT_LT(slice_loc, EdgesCenter::slice_loc_size);

		auto ori = e1.ori_index();
		ASSERT_GE(ori, 0);
		ASSERT_LT(ori, EdgesCenter::ori_size);

		auto e2 = EdgesCenter::from_index(slice_prm, non_slice_prm, slice_loc, ori);
		EXPECT_EQ(e1, e2);
	}
}

TEST(EdgesCenter, L1) { EXPECT_EQ(EdgesCenter{}.twisted(Twist::L1), EdgesCenter({ 0, 1, 2, 3, 11, 5, 6, 8, 4, 9, 10, 7 }, { 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1 })); }
TEST(EdgesCenter, R1) { EXPECT_EQ(EdgesCenter{}.twisted(Twist::R1), EdgesCenter({ 0, 1, 2, 3, 4, 9, 10, 7, 8, 6, 5, 11 }, { 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0 })); }
TEST(EdgesCenter, U1) { EXPECT_EQ(EdgesCenter{}.twisted(Twist::U1), EdgesCenter({ 5, 4, 2, 3, 0, 1, 6, 7, 8, 9, 10, 11 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 })); }
TEST(EdgesCenter, D1) { EXPECT_EQ(EdgesCenter{}.twisted(Twist::D1), EdgesCenter({ 0, 1, 6, 7, 4, 5, 3, 2, 8, 9, 10, 11 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 })); }
TEST(EdgesCenter, F1) { EXPECT_EQ(EdgesCenter{}.twisted(Twist::F1), EdgesCenter({ 8, 1, 2, 9, 4, 5, 6, 7, 3, 0, 10, 11 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 })); }
TEST(EdgesCenter, B1) { EXPECT_EQ(EdgesCenter{}.twisted(Twist::B1), EdgesCenter({ 0, 10, 11, 3, 4, 5, 6, 7, 8, 9, 2, 1 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 })); }

TEST(EdgesCenter, composed_twists)
{
	const auto c = EdgesCenter{};
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

TEST(EdgesCenter, inverse_twists)
{
	for (Twist t : all_twists)
		EXPECT_TRUE(EdgesCenter{}.twisted({ t, inversed(t) }).is_solved());
}

TEST(EdgesCenter, twists_cycle)
{
	for (Twist t : all_twists)
		EXPECT_TRUE(EdgesCenter{}.twisted({ t, t, t, t }).is_solved());
}

static void expect_twists_commutate(Twist a, Twist b)
{
	EXPECT_EQ(EdgesCenter{}.twisted({ a, b }), EdgesCenter{}.twisted({ b, a }));
}

TEST(EdgesCenter, twist_commutation)
{
	expect_twists_commutate(Twist::L1, Twist::R1);
	expect_twists_commutate(Twist::U1, Twist::D1);
	expect_twists_commutate(Twist::F1, Twist::B1);
}

TEST(EdgesCenter, is_solved)
{
	EXPECT_TRUE(EdgesCenter{}.is_solved());
	EXPECT_FALSE(EdgesCenter{}.twisted(Twist::L1).is_solved());
}
