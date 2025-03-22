#include "pch.h"

template <typename Twistable>
class TwistableTest : public testing::Test {};

using Twistables = ::testing::Types<Corners, EdgesCenter>;
TYPED_TEST_CASE(TwistableTest, Twistables);

TYPED_TEST(TwistableTest, is_solved)
{
	EXPECT_TRUE(TypeParam::solved().is_solved());
	EXPECT_FALSE(TypeParam::impossible().is_solved());
}