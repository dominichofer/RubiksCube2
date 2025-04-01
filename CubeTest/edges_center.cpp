#include "pch.h"

TEST(EdgesCenter, ud_slice_location_index)
{
	const auto e = EdgesCenter::solved();

	// H0 twists preserve the UD slice location.
	EXPECT_EQ(e.ud_slice_location_index(), EdgesCenter::ud_slice_location_size - 1);
	for (Twist twits : H0::twists)
		EXPECT_EQ(e.twisted(twits).ud_slice_location_index(), EdgesCenter::ud_slice_location_size - 1);

	EXPECT_EQ(EdgesCenter(11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1).ud_slice_location_index(), 0);
}
