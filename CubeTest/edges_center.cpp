#include "pch.h"

TEST(EdgesCenter, ud_slice_location_index)
{
	for (Twist twits : EdgesCenter::twists)
	{
		auto solved_loc = EdgesCenter::solved().ud_slice_location();
		auto twisted_loc = EdgesCenter::solved().twisted(twits).ud_slice_location();
		if (std::ranges::contains(H0::twists, twits))
		{
			// H0 twists preserve the UD slice location.
			EXPECT_EQ(twisted_loc, solved_loc);
		}
		else
		{
			// non-H0 twists change the UD slice location.
			EXPECT_NE(twisted_loc, solved_loc);
		}
	}
}
