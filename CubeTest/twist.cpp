#include "pch.h"

TEST(nTwists, default_constructor)
{
	nTwists<3> t;
	EXPECT_EQ(t.size(), 0);
	EXPECT_EQ(t[0], Twist::None);
	EXPECT_EQ(t[1], Twist::None);
	EXPECT_EQ(t[2], Twist::None);
}

TEST(nTwists, constructor)
{
	nTwists<3> t(2);
	EXPECT_EQ(t.size(), 2);
	EXPECT_EQ(t[0], Twist::None);
	EXPECT_EQ(t[1], Twist::None);
	EXPECT_EQ(t[2], Twist::None);
}

TEST(nTwists, append)
{
	nTwists<3> t;
	t.append(Twist::L1);
	EXPECT_EQ(t.size(), 1);
	EXPECT_EQ(t[0], Twist::L1);
	EXPECT_EQ(t[1], Twist::None);
	EXPECT_EQ(t[2], Twist::None);
}

TEST(nTwists, inverse)
{
	nTwists<3> t;
	Twist t0 = Twist::L1;
	Twist t1 = Twist::R2;
	Twist t2 = Twist::U3;
	t.append(t0);
	t.append(t1);
	t.append(t2);
	EXPECT_EQ(t[0], t0);
	EXPECT_EQ(t[1], t1);
	EXPECT_EQ(t[2], t2);
	t.inverse();
	EXPECT_EQ(t[0], inversed(t2));
	EXPECT_EQ(t[1], inversed(t1));
	EXPECT_EQ(t[2], inversed(t0));
}

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
	EXPECT_FALSE(same_plane(Twist::L1, Twist::l1));
}

TEST(Twist, commutative)
{
	EXPECT_TRUE(commutative(Twist::L1, Twist::L2));
	EXPECT_TRUE(commutative(Twist::L1, Twist::R2));
	EXPECT_TRUE(commutative(Twist::L1, Twist::l2));
	EXPECT_TRUE(commutative(Twist::L1, Twist::r1));
	EXPECT_FALSE(commutative(Twist::L1, Twist::B1));
}
