#include "pch.h"

TEST(hash, one_arg)
{
	EXPECT_NE(hash(0), hash(1));
}

TEST(hash, two_args)
{
	EXPECT_NE(hash(0, 1), hash(1, 0));
}

TEST(hash, three_args)
{
	EXPECT_NE(hash(0, 1, 2), hash(2, 1, 0));
}
