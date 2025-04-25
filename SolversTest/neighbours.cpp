#include "pch.h"
#include <cstdint>
#include <numeric>
#include <vector>

// Number of positions of the Rubik's cube at a distance of n moves from the solved state, in the half-turn metric.
// From https://oeis.org/A080601
const std::vector<uint64_t> pos_at_dst_HT = {
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

uint64_t sum_pos_at_dst_HT(int min, int max)
{
	return std::accumulate(pos_at_dst_HT.begin() + min, pos_at_dst_HT.begin() + max + 1, 0);
}

TEST(neighbours, num_distance_0_HTM) { EXPECT_EQ(neighbours(0, 0, Cube3x3::solved()).size(), pos_at_dst_HT[0]); }
TEST(neighbours, num_distance_1_HTM) { EXPECT_EQ(neighbours(1, 1, Cube3x3::solved()).size(), pos_at_dst_HT[1]); }
TEST(neighbours, num_distance_2_HTM) { EXPECT_EQ(neighbours(2, 2, Cube3x3::solved()).size(), pos_at_dst_HT[2]); }
TEST(neighbours, num_distance_3_HTM) { EXPECT_EQ(neighbours(3, 3, Cube3x3::solved()).size(), pos_at_dst_HT[3]); }
TEST(neighbours, num_distance_4_HTM) { EXPECT_EQ(neighbours(4, 4, Cube3x3::solved()).size(), pos_at_dst_HT[4]); }
TEST(neighbours, num_distance_5_HTM) { EXPECT_EQ(neighbours(5, 5, Cube3x3::solved()).size(), pos_at_dst_HT[5]); }

TEST(neighbours, num_max_distance_0_HTM) { EXPECT_EQ(neighbours(0, 0, Cube3x3::solved()).size(), sum_pos_at_dst_HT(0, 0)); }
TEST(neighbours, num_max_distance_1_HTM) { EXPECT_EQ(neighbours(0, 1, Cube3x3::solved()).size(), sum_pos_at_dst_HT(0, 1)); }
TEST(neighbours, num_max_distance_2_HTM) { EXPECT_EQ(neighbours(0, 2, Cube3x3::solved()).size(), sum_pos_at_dst_HT(0, 2)); }
TEST(neighbours, num_max_distance_3_HTM) { EXPECT_EQ(neighbours(0, 3, Cube3x3::solved()).size(), sum_pos_at_dst_HT(0, 3)); }
TEST(neighbours, num_max_distance_4_HTM) { EXPECT_EQ(neighbours(0, 4, Cube3x3::solved()).size(), sum_pos_at_dst_HT(0, 4)); }
TEST(neighbours, num_max_distance_5_HTM) { EXPECT_EQ(neighbours(0, 5, Cube3x3::solved()).size(), sum_pos_at_dst_HT(0, 5)); }

TEST(neighbours, num_distance_2_to_5) { EXPECT_EQ(neighbours(2, 5, Cube3x3::solved()).size(), sum_pos_at_dst_HT(2, 5)); }
TEST(neighbours, num_distance_3_to_4) { EXPECT_EQ(neighbours(3, 4, Cube3x3::solved()).size(), sum_pos_at_dst_HT(3, 4)); }

TEST(path_to_neighbours, twists_match_cube_of_max_distance_5)
{
	auto map = path_to_neighbours(5, Cube3x3::solved());
	for (const auto& [cube, twists] : map)
		EXPECT_EQ(from_string("twisted(twists), cube);
}

TEST(path_to_neighbours, twists_match_cube_of_distance_2_to_5)
{
	auto map = path_to_neighbours(2, 5, Cube3x3::solved());
	for (const auto& [cube, twists] : map)
		EXPECT_EQ(from_string("twisted(twists), cube);
}

TEST(path_to_neighbours, twists_match_cube_max_of_distance_3_to_4)
{
	auto map = path_to_neighbours(3, 4, Cube3x3::solved());
	for (const auto& [cube, twists] : map)
		EXPECT_EQ(from_string("twisted(twists), cube);
}

// Number of positions of the Rubik's cube at a distance of n moves from the solved state, in the half-turn metric.
// From https://oeis.org/A080601
const std::vector<uint64_t> pos_at_dst_QT = {
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

uint64_t sum_pos_at_dst_QT(int min, int max)
{
	return std::accumulate(pos_at_dst_QT.begin() + min, pos_at_dst_QT.begin() + max + 1, 0);
}

std::vector<Twist> QT = {
	Twist::L1, Twist::L3,
	Twist::R1, Twist::R3,
	Twist::U1, Twist::U3,
	Twist::D1, Twist::D3,
	Twist::F1, Twist::F3,
	Twist::B1, Twist::B3,
};

TEST(neighbours, num_distance_0_QTM) { EXPECT_EQ(neighbours(0, 0, Cube3x3::solved(), QT).size(), pos_at_dst_QT[0]); }
TEST(neighbours, num_distance_1_QTM) { EXPECT_EQ(neighbours(1, 1, Cube3x3::solved(), QT).size(), pos_at_dst_QT[1]); }
TEST(neighbours, num_distance_2_QTM) { EXPECT_EQ(neighbours(2, 2, Cube3x3::solved(), QT).size(), pos_at_dst_QT[2]); }
TEST(neighbours, num_distance_3_QTM) { EXPECT_EQ(neighbours(3, 3, Cube3x3::solved(), QT).size(), pos_at_dst_QT[3]); }
TEST(neighbours, num_distance_4_QTM) { EXPECT_EQ(neighbours(4, 4, Cube3x3::solved(), QT).size(), pos_at_dst_QT[4]); }
TEST(neighbours, num_distance_5_QTM) { EXPECT_EQ(neighbours(5, 5, Cube3x3::solved(), QT).size(), pos_at_dst_QT[5]); }
TEST(neighbours, num_distance_6_QTM) { EXPECT_EQ(neighbours(6, 6, Cube3x3::solved(), QT).size(), pos_at_dst_QT[6]); }

TEST(neighbours, num_max_distance_0_QTM) { EXPECT_EQ(neighbours(0, 0, Cube3x3::solved(), QT).size(), sum_pos_at_dst_QT(0, 0)); }
TEST(neighbours, num_max_distance_1_QTM) { EXPECT_EQ(neighbours(0, 1, Cube3x3::solved(), QT).size(), sum_pos_at_dst_QT(0, 1)); }
TEST(neighbours, num_max_distance_2_QTM) { EXPECT_EQ(neighbours(0, 2, Cube3x3::solved(), QT).size(), sum_pos_at_dst_QT(0, 2)); }
TEST(neighbours, num_max_distance_3_QTM) { EXPECT_EQ(neighbours(0, 3, Cube3x3::solved(), QT).size(), sum_pos_at_dst_QT(0, 3)); }
TEST(neighbours, num_max_distance_4_QTM) { EXPECT_EQ(neighbours(0, 4, Cube3x3::solved(), QT).size(), sum_pos_at_dst_QT(0, 4)); }
TEST(neighbours, num_max_distance_5_QTM) { EXPECT_EQ(neighbours(0, 5, Cube3x3::solved(), QT).size(), sum_pos_at_dst_QT(0, 5)); }
