#include "pch.h"
#include <string>
#include <vector>

TEST(join, empty) { EXPECT_EQ(join(",", std::vector<int>{}), ""); }
TEST(join, one_element) { EXPECT_EQ(join(",", std::vector<int>{ 1 }), "1"); }
TEST(join, two_elements) { EXPECT_EQ(join(",", std::vector<int>{ 1, 2 }), "1,2"); }
TEST(join, with_projection) { EXPECT_EQ(join("-", std::vector<int>{ 1, 2, 3 }, [](int i) { return i * 10; }), "10-20-30"); }

TEST(join, char_separator) { EXPECT_EQ(join(',', std::vector<int>{ 1, 2 }), "1,2"); }
TEST(join, char_arr_separator) { EXPECT_EQ(join(",", std::vector<int>{ 1, 2 }), "1,2"); }
TEST(join, string_separator) { EXPECT_EQ(join(std::string(","), std::vector<int>{ 1, 2 }), "1,2"); }
TEST(join, string_view_separator) { EXPECT_EQ(join(std::string_view(","), std::vector<int>{ 1, 2 }), "1,2"); }