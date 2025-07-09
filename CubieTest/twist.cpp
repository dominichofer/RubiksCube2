#include "pch.h"

TEST(Twist, string)
{
	for (Twist t : all_twists)
		EXPECT_EQ(t, twist_from_string(to_string(t)));
}

// Tests that the inverse of the inverse of a twist is the twist itself.
TEST(Twist, inversed)
{
	for (Twist t : all_twists)
		EXPECT_EQ(t, inversed(inversed(t)));
}

TEST(Twists, inversed)
{
	Twist t0 = Twist::L1;
	Twist t1 = Twist::R2;
	Twist t2 = Twist::U3;
	Twists twists = { t0, t1, t2 };
	Twists ref = { inversed(t2), inversed(t1), inversed(t0) };
	EXPECT_EQ(inversed(twists), ref);
}

TEST(Twist, same_plane)
{
	EXPECT_TRUE(same_plane(Twist::L1, Twist::L2));
	EXPECT_FALSE(same_plane(Twist::L1, Twist::R1));
}
