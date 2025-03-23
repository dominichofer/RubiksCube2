#include "pch.h"
#include <random>
#include <vector>

TEST(Corners, prm_index)
{
	std::vector<uint64_t> indices;
	std::array<int, 8> p = { 0, 1, 2, 3, 4, 5, 6, 7 };
	do
	{
		Corners c(p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], 0, 0, 0, 0, 0, 0, 0, 0);
		indices.push_back(c.prm_index());
	} while (std::next_permutation(p.begin(), p.end()));

	// Check that the indices cover {0, 1, 2, ..., 40319}.
	std::sort(indices.begin(), indices.end());
	EXPECT_EQ(indices.size(), factorial(8));
	for (int i = 0; i < factorial(8); i++)
		EXPECT_EQ(indices[i], i);
}

TEST(Corners, ori_index)
{
	// This generates all possible orientations of the cubies.
	// Some are only rechable by disassembling the cube.
	// Thus each index is generated 3 times.
	std::vector<uint64_t> indices;
	for (int i = 0; i < std::pow(3, 8); i++)
	{
		std::array<int, 8> o;
		int n = i;
		for (int j = 0; j < 8; j++)
		{
			o[j] = n % 3;
			n /= 3;
		}
		Corners c(0, 1, 2, 3, 4, 5, 6, 7, o[0], o[1], o[2], o[3], o[4], o[5], o[6], o[7]);
		indices.push_back(c.ori_index());
	}

	// Check that each index is contained 3 times.
	std::sort(indices.begin(), indices.end());
	EXPECT_EQ(indices.size(), std::pow(3, 8));
	for (int i = 0; i < std::pow(3, 7); i++)
	{
		EXPECT_EQ(indices[i * 3], i);
		EXPECT_EQ(indices[i * 3 + 1], i);
		EXPECT_EQ(indices[i * 3 + 2], i);
	}
}

//TEST(Corners, rotation_fuzzing)
//{
//	std::mt19937_64 rng;
//	std::uniform_int_distribution<std::size_t> dist{ 0, Corners::twists.size() - 1 };
//	Corners c;
//	for (int i = 0; i < 1'000'000; i++)
//	{
//		auto old_c = c;
//		auto twist = Corners::twists[dist(rng)];
//		c = c.twisted(twist);
//
//		bool is_legal = true;
//		// Check that the cubies are in the range [0, 7].
//		for (int i = 0; i < 8; i++)
//			if (c.cubie(i) < 0 || c.cubie(i) > 7)
//				is_legal = false;
//
//		// Check that the orientation of each cubie is in the range [0, 2].
//		for (int i = 0; i < 8; i++)
//			if (c.orientation(i) < 0 || c.orientation(i) > 2)
//				is_legal = false;
//
//		// Check that each cubie is unique.
//		for (int i = 0; i < 8; i++)
//			for (int j = i + 1; j < 8; j++)
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
