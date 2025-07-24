#include "pch.h"

using namespace std::chrono_literals;

TEST(to_string_nanoseconds, 1ns) { EXPECT_EQ(to_string(1ns), "1.00 ns"); }
TEST(to_string_nanoseconds, 10ns) { EXPECT_EQ(to_string(10ns), "10.0 ns"); }
TEST(to_string_nanoseconds, 100ns) { EXPECT_EQ(to_string(100ns), "100 ns"); }
TEST(to_string_nanoseconds, 1us) { EXPECT_EQ(to_string(1us), "1.00 us"); }
TEST(to_string_nanoseconds, 10us) { EXPECT_EQ(to_string(10us), "10.0 us"); }
TEST(to_string_nanoseconds, 100us) { EXPECT_EQ(to_string(100us), "100 us"); }
TEST(to_string_nanoseconds, 1ms) { EXPECT_EQ(to_string(1ms), "1.00 ms"); }
TEST(to_string_nanoseconds, 10ms) { EXPECT_EQ(to_string(10ms), "10.0 ms"); }
TEST(to_string_nanoseconds, 100ms) { EXPECT_EQ(to_string(100ms), "100 ms"); }
TEST(to_string_nanoseconds, 1s) { EXPECT_EQ(to_string(1s), "1.00 s"); }
TEST(to_string_nanoseconds, 10s) { EXPECT_EQ(to_string(10s), "10.0 s"); }
TEST(to_string_nanoseconds, 100s) { EXPECT_EQ(to_string(100s), "100 s"); }
TEST(to_string_nanoseconds, 1000s) { EXPECT_EQ(to_string(1000s), "1000 s"); }
