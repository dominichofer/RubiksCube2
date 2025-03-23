#include "pch.h"
#include <random>

TEST(FacesCenter, prm_index)
{
	EXPECT_EQ(FacesCenter().prm_index(), 0);
}

//TEST(FacesCenter, rotation_fuzzing)
//{
//	std::mt19937_64 rng;
//	std::uniform_int_distribution<std::size_t> dist{ 0, FacesCenter::twists.size() - 1 };
//	FacesCenter c;
//	for (int i = 0; i < 1'000'000; i++)
//	{
//		auto old_c = c;
//		auto twist = FacesCenter::twists[dist(rng)];
//		c = c.twisted(twist);
//
//		bool is_legal = true;
//		// Check that the cubies are in the range [0, 5].
//		for (int i = 0; i < 24; i++)
//			if (c.cubie(i) < 0 || c.cubie(i) > 5)
//				is_legal = false;
//
//		// Check that each cubie occurs exactly 4 times.
//		for (int i = 0; i < 6; i++)
//		{
//			int count = 0;
//			for (int j = 0; j < 24; j++)
//				if (c.cubie(j) == i)
//					count++;
//			if (count != 4)
//				is_legal = false;
//		}
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
