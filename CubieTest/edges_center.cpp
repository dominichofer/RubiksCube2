#include "pch.h"

TEST(EdgesCenter, from_index)
{
	RandomCubeGenerator<EdgesCenter> gen{ 928322 };
	for (int i = 0; i < 1'000'000; i++)
	{
		EdgesCenter e1 = gen();
		auto prm = e1.prm_index();
		auto slice_loc = e1.slice_loc_index();
		auto ori = e1.ori_index();
		auto e2 = EdgesCenter::from_index(prm, slice_loc, ori);
		EXPECT_EQ(e1, e2) << "prm: " << prm << ", slice_loc: " << slice_loc << ", ori: " << ori;
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

TEST(EdgesCenter, prm_and_slice_loc_index)
{
	std::vector<int> prm_pigeonhole(EdgesCenter::prm_size, 0);
	std::vector<int> slice_loc_pigeonhole(EdgesCenter::slice_loc_size, 0);
	std::vector<int> full_pigeonhole(EdgesCenter::prm_size * EdgesCenter::slice_loc_size, 0);
	std::array<uint8_t, 12> p = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	do // For all permutations of the cubies.
	{
		EdgesCenter c{ p, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

		auto prm_index = c.prm_index();
		ASSERT_GE(prm_index, 0);
		ASSERT_LT(prm_index, EdgesCenter::prm_size);

		auto slice_loc_index = c.slice_loc_index();
		ASSERT_GE(slice_loc_index, 0);
		ASSERT_LT(slice_loc_index, EdgesCenter::slice_loc_size);

		prm_pigeonhole[prm_index]++;
		slice_loc_pigeonhole[slice_loc_index]++;
		full_pigeonhole[prm_index * EdgesCenter::slice_loc_size + slice_loc_index]++;
	} while (std::next_permutation(p.begin(), p.end()));

	for (int pigeons : prm_pigeonhole)
		ASSERT_EQ(pigeons, EdgesCenter::slice_loc_size);

	for (int pigeons : slice_loc_pigeonhole)
		ASSERT_EQ(pigeons, EdgesCenter::prm_size);

	for (int pigeons : full_pigeonhole)
		ASSERT_EQ(pigeons, 1);
}

static std::array<uint8_t, 12> ori_from_index(uint64_t index)
{
	std::array<uint8_t, 12> o;
	for (auto& x : o)
	{
		x = index % 2;
		index /= 2;
	}
	return o;
}

TEST(EdgesCenter, ori_index)
{
	// This generates all possible orientations of the cubies.
	// Some are only rechable by disassembling the cube.
	// Thus each index is generated 2 times.
	std::vector<int> pigeonhole(EdgesCenter::ori_size, 0);

	for (int i = 0; i < EdgesCenter::ori_size * 2; i++)
	{
		EdgesCenter c{ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, ori_from_index(i) };
		auto index = c.ori_index();
		ASSERT_GE(index, 0);
		ASSERT_LT(index, EdgesCenter::ori_size);

		pigeonhole[index]++;
	}

	for (int pigeons : pigeonhole)
		ASSERT_EQ(pigeons, 2);
}
