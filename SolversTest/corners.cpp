#include "pch.h"
#include <algorithm>

TEST(CornerSolution, fuzzing)
{
	RandomCubeGenerator<Corners> gen(53412); // arbitrary seed
	for (int i = 0; i < 100'000; i++)
	{
		Corners c = gen();
		std::vector<Corners::Twist> sol = solution(c);
		EXPECT_TRUE(c.twisted(sol).is_solved());
		EXPECT_EQ(solution_distance(c), sol.size());
	}
}

//std::vector<uint8_t> table = CreateCornerTable();
//
//TEST(CornerTable, max_value)
//{
//	EXPECT_EQ(*std::max_element(table.begin(), table.end()), 11);
//}
//
//int count(uint8_t n)
//{
//	return std::count(table.begin(), table.end(), n);
//}
//
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
