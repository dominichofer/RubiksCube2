#include "pch.h"
//#include <algorithm>
//
//class DistanceTable_Corners : public ::testing::Test
//{
//protected:
//	const DistanceTable<Corners> table{ 5 };
//};
//
//const auto table = DistanceTable_Corners();
//
//TEST(DistanceTable_Corners, fuzzing)
//{
//	RandomCubeGenerator<Corners> gen(53412); // arbitrary seed
//	for (int i = 0; i < 100'000; i++)
//	{
//		Corners c = gen();
//		auto sol = table.solution(c);
//		EXPECT_TRUE(c.twisted(sol).is_solved());
//		EXPECT_EQ(table[c], sol.size());
//	}
//}
//
//TEST(DistanceTable_Corners, max_distance)
//{
//	EXPECT_EQ(table.max_distance(), 11);
//}
//
//auto count(uint8_t n)
//{
//	return std::count(table.begin(), table.end(), n);
//}
//
//// According to https://oeis.org/A080629
//TEST(CornerTable, 0s) { EXPECT_EQ(count(0), 1); }
//TEST(CornerTable, 1s) { EXPECT_EQ(count(1), 18); }
//TEST(CornerTable, 2s) { EXPECT_EQ(count(2), 243); }
//TEST(CornerTable, 3s) { EXPECT_EQ(count(3), 2'874); }
//TEST(CornerTable, 4s) { EXPECT_EQ(count(4), 28'000); }
//TEST(CornerTable, 5s) { EXPECT_EQ(count(5), 205'416); }
//TEST(CornerTable, 6s) { EXPECT_EQ(count(6), 1'168'516); }
//TEST(CornerTable, 7s) { EXPECT_EQ(count(7), 5'402'628); }
//TEST(CornerTable, 8s) { EXPECT_EQ(count(8), 20'776'176); }
//TEST(CornerTable, 9s) { EXPECT_EQ(count(9), 45'391'616); }
//TEST(CornerTable, 10s) { EXPECT_EQ(count(10), 15'139'616); }
//TEST(CornerTable, 11s) { EXPECT_EQ(count(11), 64'736); }
