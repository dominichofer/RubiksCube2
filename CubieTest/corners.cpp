#include "pch.h"
#include <unordered_set>

TEST(Corners, from_index)
{
	RandomCubeGenerator<Corners> gen{ 928322 };
	for (int i = 0; i < 1'000'000; i++)
	{
		Corners c1 = gen();
		auto prm = c1.prm_index();
		auto ori = c1.ori_index();
		auto c2 = Corners::from_index(prm, ori);
		EXPECT_EQ(c1, c2) << "prm: " << prm << ", ori: " << ori;
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

TEST(Corners, prm_index)
{
	std::vector<int> pigeonhole(Corners::prm_size, 0);

	std::array<uint8_t, 8> p = { 0, 1, 2, 3, 4, 5, 6, 7 };
	do // For all permutations of the cubies.
	{
		Corners c{ p, { 0, 0, 0, 0, 0, 0, 0, 0 } };
		auto index = c.prm_index();
		ASSERT_GE(index, 0);
		ASSERT_LT(index, Corners::prm_size);

		pigeonhole[index]++;
	} while (std::next_permutation(p.begin(), p.end()));

	for (int pigeons : pigeonhole)
		ASSERT_EQ(pigeons, 1);
}

static std::array<uint8_t, 8> ori_from_index(uint64_t index)
{
	std::array<uint8_t, 8> o;
	for (auto& x : o)
	{
		x = index % 3;
		index /= 3;
	}
	return o;
}

TEST(Corners, ori_index)
{
	// This generates all possible orientations of the cubies.
	// Some are only rechable by disassembling the cube.
	// Thus each index is generated 3 times.
	std::vector<int> pigeonhole(Corners::ori_size, 0);

	for (int i = 0; i < Corners::ori_size * 3; i++)
	{
		Corners c{ { 0, 0, 0, 0, 0, 0, 0, 0 }, ori_from_index(i) };
		auto index = c.ori_index();
		ASSERT_GE(index, 0);
		ASSERT_LT(index, Corners::ori_size);

		pigeonhole[index]++;
	}

	for (int pigeons : pigeonhole)
		ASSERT_EQ(pigeons, 3);
}
