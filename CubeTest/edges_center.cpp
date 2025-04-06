#include "pch.h"

TEST(EdgesCenter, ud_slice_location_index)
{
	// H0 twists preserve the UD slice location.
	for (Twist twits : H0::twists)
		EXPECT_EQ(
			EdgesCenter::solved().twisted(twits).ud_slice_location(),
			EdgesCenter::solved().ud_slice_location());

	// non-H0 twists change preserve the UD slice location.
	for (Twist twits : {Twist::L1, Twist::L3, Twist::R1, Twist::R3, Twist::F1, Twist::F3, Twist::B1, Twist::B3})
		EXPECT_EQ(
			EdgesCenter::solved().twisted(twits).ud_slice_location(),
			EdgesCenter::solved().ud_slice_location());
}
