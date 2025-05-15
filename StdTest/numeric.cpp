#include "pch.h"

TEST(powi, small_numbers)
{
    EXPECT_EQ(powi(2, 3), 8);
    EXPECT_EQ(powi(3, 2), 9);
    EXPECT_EQ(powi(5, 4), 625);
}

TEST(powi, zero_exponent)
{
    EXPECT_EQ(powi(2, 0), 1);
    EXPECT_EQ(powi(0, 0), 1); // By convention, 0^0 = 1
    EXPECT_EQ(powi(12345, 0), 1);
}

TEST(powi, zero_base)
{
    EXPECT_EQ(powi(0, 1), 0);
    EXPECT_EQ(powi(0, 5), 0);
}

TEST(powi, one_base)
{
    EXPECT_EQ(powi(1, 100), 1);
    EXPECT_EQ(powi(1, 0), 1);
}

TEST(powi, edge_cases)
{
    EXPECT_EQ(powi(UINT64_MAX, 1), UINT64_MAX);
    EXPECT_EQ(powi(UINT64_MAX, 0), 1);
}
