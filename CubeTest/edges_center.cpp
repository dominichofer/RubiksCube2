#include "pch.h"
#include <random>

TEST(EdgesCenter, default_is_solved)
{
    EXPECT_TRUE(EdgesCenter().is_solved());
}

TEST(EdgesCenter, twisted_is_not_solved)
{
    EXPECT_FALSE(EdgesCenter().L1().is_solved());
}

// Fuzz test
TEST(EdgesCenter, cubies)
{
	std::mt19937_64 rng;
	std::uniform_int_distribution<> dist(0, 11);
	std::vector<uint8_t> c(12);
	for (int i = 0; i < 1'000'000; i++)
	{
		for (int j = 0; j < 12; j++)
			c[j] = dist(rng);
		EdgesCenter edges(c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8], c[9], c[10], c[11], 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		for (int j = 0; j < 12; j++)
			EXPECT_EQ(edges.cubie(j), c[j]);
	}
}

// Fuzz test
TEST(EdgesCenter, orientations)
{
	std::mt19937_64 rng;
	std::uniform_int_distribution<> dist(0, 1);
	std::vector<uint8_t> o(12);
	for (int i = 0; i < 1'000'000; i++)
	{
		for (int j = 0; j < 12; j++)
			o[j] = dist(rng);
		EdgesCenter edges(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, o[0], o[1], o[2], o[3], o[4], o[5], o[6], o[7], o[8], o[9], o[10], o[11]);
		for (int j = 0; j < 12; j++)
			EXPECT_EQ(edges.orientation(j), o[j]);
	}
}

TEST(EdgesCenter, ud_slice_prm_index)
{
	EXPECT_EQ(EdgesCenter().ud_slice_prm_index(), EdgesCenter::ud_slice_size - 1);

	// H = { L2,R2,F2,B2,U,D } twists preserve the UD slice location.
	EXPECT_EQ(EdgesCenter().L2().ud_slice_prm_index(), EdgesCenter::ud_slice_size - 1);
	EXPECT_EQ(EdgesCenter().R2().ud_slice_prm_index(), EdgesCenter::ud_slice_size - 1);
	EXPECT_EQ(EdgesCenter().F2().ud_slice_prm_index(), EdgesCenter::ud_slice_size - 1);
	EXPECT_EQ(EdgesCenter().B2().ud_slice_prm_index(), EdgesCenter::ud_slice_size - 1);
	EXPECT_EQ(EdgesCenter().U1().ud_slice_prm_index(), EdgesCenter::ud_slice_size - 1);
	EXPECT_EQ(EdgesCenter().U2().ud_slice_prm_index(), EdgesCenter::ud_slice_size - 1);
	EXPECT_EQ(EdgesCenter().U3().ud_slice_prm_index(), EdgesCenter::ud_slice_size - 1);
	EXPECT_EQ(EdgesCenter().D1().ud_slice_prm_index(), EdgesCenter::ud_slice_size - 1);
	EXPECT_EQ(EdgesCenter().D2().ud_slice_prm_index(), EdgesCenter::ud_slice_size - 1);
	EXPECT_EQ(EdgesCenter().D3().ud_slice_prm_index(), EdgesCenter::ud_slice_size - 1);

	EXPECT_EQ(EdgesCenter(11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1).ud_slice_prm_index(), 0);
}

TEST(EdgesCenter, L1) {
	EXPECT_EQ(
		EdgesCenter().L1(),
		EdgesCenter(0, 1, 2, 11, 4, 5, 6, 8, 3, 9, 10, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
	);
}
TEST(EdgesCenter, R1) {
	EXPECT_EQ(
		EdgesCenter().R1(),
		EdgesCenter(0, 9, 2, 3, 4, 10, 6, 7, 8, 5, 1, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
	);
}
TEST(EdgesCenter, U1) {
	EXPECT_EQ(
		EdgesCenter().U1(),
		EdgesCenter(1, 2, 3, 0, 4, 5, 6, 7, 8, 9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
	);
}
TEST(EdgesCenter, D1) {
	EXPECT_EQ(
		EdgesCenter().D1(),
		EdgesCenter(0, 1, 2, 3, 7, 4, 5, 6, 8, 9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
	);
}
TEST(EdgesCenter, F1) {
	EXPECT_EQ(
		EdgesCenter().F1(),
		EdgesCenter(8, 1, 2, 3, 9, 5, 6, 7, 4, 0, 10, 11, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0)
	);
}
TEST(EdgesCenter, B1) {
	EXPECT_EQ(
		EdgesCenter().B1(),
		EdgesCenter(0, 1, 10, 3, 4, 5, 11, 7, 8, 9, 6, 2, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1)
	);
}

TEST(EdgesCenter, prm_index)
{
	EdgesCenter first(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	EXPECT_EQ(first.prm_index(), 0);

	EdgesCenter last(11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	EXPECT_EQ(last.prm_index(), factorial(12) - 1);
}

TEST(EdgesCenter, ori_index)
{
	// This generates all possible orientations of the cubies.
	// Some are only rechable by disassembling the cube.
	// Thus each index is generated 2 times.
	std::vector<uint64_t> indices;
	for (int i = 0; i < std::pow(2, 12); i++)
	{
		std::array<int, 12> o;
		int n = i;
		for (int j = 0; j < 12; j++)
		{
			o[j] = n % 2;
			n /= 2;
		}
		EdgesCenter c(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, o[0], o[1], o[2], o[3], o[4], o[5], o[6], o[7], o[8], o[9], o[10], o[11]);
		indices.push_back(c.ori_index());
	}

	// Check that each index is contained 2 times.
	std::sort(indices.begin(), indices.end());
	EXPECT_EQ(indices.size(), std::pow(2, 12));
	for (int i = 0; i < std::pow(2, 11); i++)
	{
		EXPECT_EQ(indices[i * 2], i);
		EXPECT_EQ(indices[i * 2 + 1], i);
	}
}

//TEST(EdgesCenter, rotation_fuzzing)
//{
//	std::mt19937_64 rng;
//	std::uniform_int_distribution<std::size_t> dist{ 0, EdgesCenter::twists.size() - 1 };
//	EdgesCenter c;
//	for (int i = 0; i < 1'000'000; i++)
//	{
//		auto old_c = c;
//		auto twist = EdgesCenter::twists[dist(rng)];
//		c = c.twisted(twist);
//
//		bool is_legal = true;
//		// Check that the edges are in the range [0, 11].
//		for (int i = 0; i < 12; i++)
//			if (c.cubie(i) < 0 || c.cubie(i) > 11)
//				is_legal = false;
//
//		// Check that the orientation of each cubie is in the range [0, 1].
//		for (int i = 0; i < 12; i++)
//			if (c.orientation(i) < 0 || c.orientation(i) > 1)
//				is_legal = false;
//
//		// Check that each cubie is unique.
//		for (int i = 0; i < 12; i++)
//			for (int j = i + 1; j < 12; j++)
//				if (c.cubie(i) == c.cubie(j))
//					is_legal = false;
//
//		if (!is_legal)
//		{
//			std::cout << "Old state:\n" << to_string(old_c) << std::endl;
//			std::cout << "Twist: " << to_string(twist) << std::endl;
//			std::cout << "New state:\n" << to_string(c) << std::endl;
//			ASSERT_TRUE(false);
//		}
//	}
//}
