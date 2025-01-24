#include "pch.h"

#define TEST_INVERSED(cls) \
TEST(inversed_##cls, is_involution) \
{ \
	for (auto twist : cls::twists) \
		EXPECT_EQ(inversed(inversed(twist)), twist); \
} \
\
TEST(inversed_##cls, is_inverse) \
{ \
	for (auto twist : cls::twists) \
		EXPECT_EQ(cls().twisted(twist).twisted(inversed(twist)), cls()); \
}

TEST_INVERSED(Corners)
TEST_INVERSED(EdgesCenter)
TEST_INVERSED(EdgesSide)
TEST_INVERSED(FacesCenter)
TEST_INVERSED(FacesSide)
TEST_INVERSED(Cube2x2)
TEST_INVERSED(Cube3x3)
TEST_INVERSED(Cube4x4)
TEST_INVERSED(Cube5x5)
