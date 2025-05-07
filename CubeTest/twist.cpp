#include "pch.h"

// Tests that the inverse of the inverse of a twist is the twist itself.
TEST(Twist, inversed_is_involution)
{
	for (Twist t : all_twists)
		EXPECT_EQ(t, inversed(inversed(t)));
}
