#include "pch.h"

TEST(Corners, index_1)
{
	for (uint16_t prm = 0; prm < Corners::prm_size; prm++)
		for (uint16_t ori = 0; ori < Corners::ori_size; ori++)
		{
			Corners c1 = Corners::from_index(prm, ori);

			auto prm2 = c1.prm_index();
			ASSERT_GE(prm2, 0);
			ASSERT_LT(prm2, Corners::prm_size);
			EXPECT_EQ(prm, prm2);

			auto ori2 = c1.ori_index();
			ASSERT_GE(ori2, 0);
			ASSERT_LT(ori2, Corners::ori_size);
			EXPECT_EQ(ori, ori2);
		}
}

TEST(Corners, index_2)
{
	for (uint32_t index = 0; index < Corners::size; index++)
	{
		Corners c1 = Corners::from_index(index);
		auto index2 = c1.index();
		ASSERT_GE(index2, 0);
		ASSERT_LT(index2, Corners::size);
		EXPECT_EQ(index, index2);
	}
}

TEST(Corners, L1) { EXPECT_EQ(Corners{}.twisted(Twist::L1), Corners({ 2, 1, 6, 3, 0, 5, 4, 7 }, { 2, 0, 2, 0, 2, 0, 2, 0 })); }
TEST(Corners, R1) { EXPECT_EQ(Corners{}.twisted(Twist::R1), Corners({ 0, 5, 2, 1, 4, 7, 6, 3 }, { 0, 2, 0, 2, 0, 2, 0, 2 })); }
TEST(Corners, U1) { EXPECT_EQ(Corners{}.twisted(Twist::U1), Corners({ 1, 3, 0, 2, 4, 5, 6, 7 }, { 0, 0, 0, 0, 0, 0, 0, 0 })); }
TEST(Corners, D1) { EXPECT_EQ(Corners{}.twisted(Twist::D1), Corners({ 0, 1, 2, 3, 6, 4, 7, 5 }, { 0, 0, 0, 0, 0, 0, 0, 0 })); }
TEST(Corners, F1) { EXPECT_EQ(Corners{}.twisted(Twist::F1), Corners({ 4, 0, 2, 3, 5, 1, 6, 7 }, { 1, 1, 0, 0, 1, 1, 0, 0 })); }
TEST(Corners, B1) { EXPECT_EQ(Corners{}.twisted(Twist::B1), Corners({ 0, 1, 3, 7, 4, 5, 2, 6 }, { 0, 0, 1, 1, 0, 0, 1, 1 })); }

TEST(Corners, composed_twists)
{
	const auto c = Corners{};
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

TEST(Corners, inverse_twists)
{
	for (Twist t : all_twists)
		EXPECT_TRUE(Corners{}.twisted({ t, inversed(t) }).is_solved());
}

TEST(Corners, twists_cycle)
{
	for (Twist t : all_twists)
		EXPECT_TRUE(Corners{}.twisted({ t, t, t, t }).is_solved());
}

static void expect_twists_commutate(Twist a, Twist b)
{
	EXPECT_EQ(Corners{}.twisted({ a, b }), Corners{}.twisted({ b, a }));
}

TEST(Corners, twist_commutation)
{
	expect_twists_commutate(Twist::L1, Twist::R1);
	expect_twists_commutate(Twist::U1, Twist::D1);
	expect_twists_commutate(Twist::F1, Twist::B1);
}

TEST(Corners, is_solved)
{
	EXPECT_TRUE(Corners{}.is_solved());
	EXPECT_FALSE(Corners{}.twisted(Twist::L1).is_solved());
}
