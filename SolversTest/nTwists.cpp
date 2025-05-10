#include "pch.h"

TEST(nTwistsTests, DefaultConstructor)
{
	nTwists<5> twists;
	EXPECT_EQ(twists.size(), 0);
	for (int i = 0; i < 5; ++i)
		EXPECT_EQ(twists[i], Twist::None);
}

TEST(nTwistsTests, SizeConstructor)
{
	nTwists<5> twists{ -1 };
	EXPECT_EQ(twists.size(), -1);
	for (int i = 0; i < 5; ++i)
		EXPECT_EQ(twists[i], Twist::None);
}

TEST(nTwistsTests, Append)
{
	nTwists<5> twists;
	twists.append(Twist::D1);
	EXPECT_EQ(twists.size(), 1);
	EXPECT_EQ(twists[0], Twist::D1);
}
