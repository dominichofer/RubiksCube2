#include "pch.h"
#include <array>
#include <numeric>
#include <vector>

// Number of positions of the Rubik's cube at a distance of n moves from the solved state, in the half-turn metric.
// From https://oeis.org/A080601
const std::vector<std::size_t> pos_at_dst_HT = {
	1,
	18,
	243,
	3240,
	43239,
	574908,
	7618438,
	100803036,
	1332343288,
	17596479795,
	232248063316,
	3063288809012,
	40374425656248,
	531653418284628,
	6989320578825358,
	91365146187124313,
};

std::size_t sum_pos_at_dst_HT(std::size_t min, std::size_t max)
{
	return std::accumulate(pos_at_dst_HT.begin() + min, pos_at_dst_HT.begin() + max + 1, 0);
}

TEST(neighbours, num_distance_0_HTM) { EXPECT_EQ(neighbours(Cube3x3(), 0, 0).size(), pos_at_dst_HT[0]); }
TEST(neighbours, num_distance_1_HTM) { EXPECT_EQ(neighbours(Cube3x3(), 1, 1).size(), pos_at_dst_HT[1]); }
TEST(neighbours, num_distance_2_HTM) { EXPECT_EQ(neighbours(Cube3x3(), 2, 2).size(), pos_at_dst_HT[2]); }
TEST(neighbours, num_distance_3_HTM) { EXPECT_EQ(neighbours(Cube3x3(), 3, 3).size(), pos_at_dst_HT[3]); }
TEST(neighbours, num_distance_4_HTM) { EXPECT_EQ(neighbours(Cube3x3(), 4, 4).size(), pos_at_dst_HT[4]); }
TEST(neighbours, num_distance_5_HTM) { EXPECT_EQ(neighbours(Cube3x3(), 5, 5).size(), pos_at_dst_HT[5]); }

TEST(neighbours, num_max_distance_0_HTM) { EXPECT_EQ(neighbours(Cube3x3(), 0, 0).size(), sum_pos_at_dst_HT(0, 0)); }
TEST(neighbours, num_max_distance_1_HTM) { EXPECT_EQ(neighbours(Cube3x3(), 0, 1).size(), sum_pos_at_dst_HT(0, 1)); }
TEST(neighbours, num_max_distance_2_HTM) { EXPECT_EQ(neighbours(Cube3x3(), 0, 2).size(), sum_pos_at_dst_HT(0, 2)); }
TEST(neighbours, num_max_distance_3_HTM) { EXPECT_EQ(neighbours(Cube3x3(), 0, 3).size(), sum_pos_at_dst_HT(0, 3)); }
TEST(neighbours, num_max_distance_4_HTM) { EXPECT_EQ(neighbours(Cube3x3(), 0, 4).size(), sum_pos_at_dst_HT(0, 4)); }
TEST(neighbours, num_max_distance_5_HTM) { EXPECT_EQ(neighbours(Cube3x3(), 0, 5).size(), sum_pos_at_dst_HT(0, 5)); }

TEST(neighbours, num_distance_2_to_5) { EXPECT_EQ(neighbours(Cube3x3(), 2, 5).size(), sum_pos_at_dst_HT(2, 5)); }
TEST(neighbours, num_distance_3_to_4) { EXPECT_EQ(neighbours(Cube3x3(), 3, 4).size(), sum_pos_at_dst_HT(3, 4)); }

TEST(neighbours, twists_match_cube_of_max_distance_5)
{
	auto n = neighbours(Cube3x3(), 0, 5);
	for (const auto& [cube, twists] : n)
		EXPECT_EQ(Cube3x3().twisted(twists), cube);
}

TEST(neighbours, twists_match_cube_of_distance_2_to_5)
{
	auto n = neighbours(Cube3x3(), 2, 5);
	for (const auto& [cube, twists] : n)
		EXPECT_EQ(Cube3x3().twisted(twists), cube);
}

TEST(neighbours, twists_match_cube_max_of_distance_3_to_4)
{
	auto n = neighbours(Cube3x3(), 3, 4);
	for (const auto& [cube, twists] : n)
		EXPECT_EQ(Cube3x3().twisted(twists), cube);
}

// Number of positions of the Rubik's cube at a distance of n moves from the solved state, in the half-turn metric.
// From https://oeis.org/A080601
const std::vector<std::size_t> pos_at_dst_QT = {
	1,
	12,
	114,
	1068,
	10011,
	93840,
	878880,
	8221632,
	76843595,
	717789576,
	6701836858,
	62549615248,
	583570100997,
	5442351625028,
	50729620202582,
	472495678811004,
	4393570406220123,
	40648181519827392,
	368071526203620348,
};

std::size_t sum_pos_at_dst_QT(std::size_t min, std::size_t max)
{
	return std::accumulate(pos_at_dst_QT.begin() + min, pos_at_dst_QT.begin() + max + 1, 0);
}

std::array<Cube3x3::Twist, 12> QT = {
	Cube3x3::Twist::L1, Cube3x3::Twist::L3,
	Cube3x3::Twist::R1, Cube3x3::Twist::R3,
	Cube3x3::Twist::U1, Cube3x3::Twist::U3,
	Cube3x3::Twist::D1, Cube3x3::Twist::D3,
	Cube3x3::Twist::F1, Cube3x3::Twist::F3,
	Cube3x3::Twist::B1, Cube3x3::Twist::B3,
};

TEST(neighbours, num_distance_0_QTM) { EXPECT_EQ(neighbours(Cube3x3(), 0, 0, QT).size(), pos_at_dst_QT[0]); }
TEST(neighbours, num_distance_1_QTM) { EXPECT_EQ(neighbours(Cube3x3(), 1, 1, QT).size(), pos_at_dst_QT[1]); }
TEST(neighbours, num_distance_2_QTM) { EXPECT_EQ(neighbours(Cube3x3(), 2, 2, QT).size(), pos_at_dst_QT[2]); }
TEST(neighbours, num_distance_3_QTM) { EXPECT_EQ(neighbours(Cube3x3(), 3, 3, QT).size(), pos_at_dst_QT[3]); }
TEST(neighbours, num_distance_4_QTM) { EXPECT_EQ(neighbours(Cube3x3(), 4, 4, QT).size(), pos_at_dst_QT[4]); }
TEST(neighbours, num_distance_5_QTM) { EXPECT_EQ(neighbours(Cube3x3(), 5, 5, QT).size(), pos_at_dst_QT[5]); }
TEST(neighbours, num_distance_6_QTM) { EXPECT_EQ(neighbours(Cube3x3(), 6, 6, QT).size(), pos_at_dst_QT[6]); }

TEST(neighbours, num_max_distance_0_QTM) { EXPECT_EQ(neighbours(Cube3x3(), 0, 0, QT).size(), sum_pos_at_dst_QT(0, 0)); }
TEST(neighbours, num_max_distance_1_QTM) { EXPECT_EQ(neighbours(Cube3x3(), 0, 1, QT).size(), sum_pos_at_dst_QT(0, 1)); }
TEST(neighbours, num_max_distance_2_QTM) { EXPECT_EQ(neighbours(Cube3x3(), 0, 2, QT).size(), sum_pos_at_dst_QT(0, 2)); }
TEST(neighbours, num_max_distance_3_QTM) { EXPECT_EQ(neighbours(Cube3x3(), 0, 3, QT).size(), sum_pos_at_dst_QT(0, 3)); }
TEST(neighbours, num_max_distance_4_QTM) { EXPECT_EQ(neighbours(Cube3x3(), 0, 4, QT).size(), sum_pos_at_dst_QT(0, 4)); }
TEST(neighbours, num_max_distance_5_QTM) { EXPECT_EQ(neighbours(Cube3x3(), 0, 5, QT).size(), sum_pos_at_dst_QT(0, 5)); }
