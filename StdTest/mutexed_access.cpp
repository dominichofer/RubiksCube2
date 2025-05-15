#include "pch.h"

TEST(MutexedAccess, constructor_throws_on_zero_mutexes)
{
    std::vector<int> data(5, 0);
    EXPECT_THROW(MutexedAccess(data, 0), std::invalid_argument);
}

TEST(MutexedAccess, store_and_load)
{
    std::vector<int> data(5, 0);
    MutexedAccess access(data, 2);

    access.store(3, 42);
    EXPECT_EQ(access.load(3), 42);
}
