#include "pch.h"
#include <vector>

const uint8_t a0 = 0, a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7;
const uint8_t b0 = 8, b1 = 9, b2 = 10, b3 = 11, b4 = 12, b5 = 13, b6 = 14, b7 = 15;
const uint8_t c0 = 16, c1 = 17, c2 = 18, c3 = 19, c4 = 20, c5 = 21, c6 = 22, c7 = 23;
const FacesCenter X = FacesCenter(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23);
const FacesSide Y = FacesSide(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23);

TEST(Corners, L1) { EXPECT_EQ(Corners::solved().twisted(Twist::L1), Corners({ 2, 1, 6, 3, 0, 5, 4, 7 }, { 2, 0, 2, 0, 2, 0, 2, 0 })); }
TEST(Corners, R1) { EXPECT_EQ(Corners::solved().twisted(Twist::R1), Corners({ 0, 5, 2, 1, 4, 7, 6, 3 }, { 0, 2, 0, 2, 0, 2, 0, 2 })); }
TEST(Corners, U1) { EXPECT_EQ(Corners::solved().twisted(Twist::U1), Corners({ 1, 3, 0, 2, 4, 5, 6, 7 }, { 0, 0, 0, 0, 0, 0, 0, 0 })); }
TEST(Corners, D1) { EXPECT_EQ(Corners::solved().twisted(Twist::D1), Corners({ 0, 1, 2, 3, 6, 4, 7, 5 }, { 0, 0, 0, 0, 0, 0, 0, 0 })); }
TEST(Corners, F1) { EXPECT_EQ(Corners::solved().twisted(Twist::F1), Corners({ 4, 0, 2, 3, 5, 1, 6, 7 }, { 1, 1, 0, 0, 1, 1, 0, 0 })); }
TEST(Corners, B1) { EXPECT_EQ(Corners::solved().twisted(Twist::B1), Corners({ 0, 1, 3, 7, 4, 5, 2, 6 }, { 0, 0, 1, 1, 0, 0, 1, 1 })); }

TEST(EdgesCenter, L1) { EXPECT_EQ(EdgesCenter::solved().twisted(Twist::L1), EdgesCenter({ 0, 1, 2, 3, 11, 5, 6, 8, 4, 9, 10, 7 }, { 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1 })); }
TEST(EdgesCenter, R1) { EXPECT_EQ(EdgesCenter::solved().twisted(Twist::R1), EdgesCenter({ 0, 1, 2, 3, 4, 9, 10, 7, 8, 6, 5, 11 }, { 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0 })); }
TEST(EdgesCenter, U1) { EXPECT_EQ(EdgesCenter::solved().twisted(Twist::U1), EdgesCenter({ 5, 4, 2, 3, 0, 1, 6, 7, 8, 9, 10, 11 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 })); }
TEST(EdgesCenter, D1) { EXPECT_EQ(EdgesCenter::solved().twisted(Twist::D1), EdgesCenter({ 0, 1, 6, 7, 4, 5, 3, 2, 8, 9, 10, 11 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 })); }
TEST(EdgesCenter, F1) { EXPECT_EQ(EdgesCenter::solved().twisted(Twist::F1), EdgesCenter({ 8, 1, 2, 9, 4, 5, 6, 7, 3, 0, 10, 11 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 })); }
TEST(EdgesCenter, B1) { EXPECT_EQ(EdgesCenter::solved().twisted(Twist::B1), EdgesCenter({ 0, 10, 11, 3, 4, 5, 6, 7, 8, 9, 2, 1 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 })); }

TEST(EdgesSide, L1) { EXPECT_EQ(EdgesSide::solved().twisted(Twist::L1), EdgesSide(a0, a1, a2, a3, a4, a5, a6, a7, c1, c0, b2, b3, b4, b5, c3, c2, b6, b7, b0, b1, c4, c5, c6, c7)); }
TEST(EdgesSide, l1) { EXPECT_EQ(EdgesSide::solved().twisted(Twist::l1), EdgesSide(a2, a1, a4, a3, a6, a5, a0, a7, b0, b1, b2, b3, b4, b5, b6, b7, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(EdgesSide, R1) { EXPECT_EQ(EdgesSide::solved().twisted(Twist::R1), EdgesSide(a0, a1, a2, a3, a4, a5, a6, a7, b0, b1, c4, c5, c6, c7, b6, b7, c0, c1, c2, c3, b5, b4, b3, b2)); }
TEST(EdgesSide, r1) { EXPECT_EQ(EdgesSide::solved().twisted(Twist::r1), EdgesSide(a0, a7, a2, a1, a4, a3, a6, a5, b0, b1, b2, b3, b4, b5, b6, b7, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(EdgesSide, U1) { EXPECT_EQ(EdgesSide::solved().twisted(Twist::U1), EdgesSide(c6, c7, c0, c1, a4, a5, a6, a7, b0, b1, b2, b3, b4, b5, b6, b7, a1, a0, c2, c3, c4, c5, a3, a2)); }
TEST(EdgesSide, u1) { EXPECT_EQ(EdgesSide::solved().twisted(Twist::u1), EdgesSide(a0, a1, a2, a3, a4, a5, a6, a7, b2, b1, b4, b3, b6, b5, b0, b7, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(EdgesSide, D1) { EXPECT_EQ(EdgesSide::solved().twisted(Twist::D1), EdgesSide(a0, a1, a2, a3, c5, c4, c3, c2, b0, b1, b2, b3, b4, b5, b6, b7, c0, c1, a4, a5, a6, a7, c6, c7)); }
TEST(EdgesSide, d1) { EXPECT_EQ(EdgesSide::solved().twisted(Twist::d1), EdgesSide(a0, a1, a2, a3, a4, a5, a6, a7, b0, b7, b2, b1, b4, b3, b6, b5, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(EdgesSide, F1) { EXPECT_EQ(EdgesSide::solved().twisted(Twist::F1), EdgesSide(b1, b0, a2, a3, a4, a5, b3, b2, a6, a7, a0, a1, b4, b5, b6, b7, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(EdgesSide, f1) { EXPECT_EQ(EdgesSide::solved().twisted(Twist::f1), EdgesSide(a0, a1, a2, a3, a4, a5, a6, a7, b0, b1, b2, b3, b4, b5, b6, b7, c2, c1, c4, c3, c6, c5, c0, c7)); }
TEST(EdgesSide, B1) { EXPECT_EQ(EdgesSide::solved().twisted(Twist::B1), EdgesSide(a0, a1, b4, b5, b6, b7, a6, a7, b0, b1, b2, b3, a5, a4, a3, a2, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(EdgesSide, b1) { EXPECT_EQ(EdgesSide::solved().twisted(Twist::b1), EdgesSide(a0, a1, a2, a3, a4, a5, a6, a7, b0, b1, b2, b3, b4, b5, b6, b7, c0, c7, c2, c1, c4, c3, c6, c5)); }

TEST(FacesCenter, L1) { EXPECT_EQ(X.twisted(Twist::L1), FacesCenter(a1, a2, a3, a0, a4, a5, a6, a7, b0, b1, b2, b3, b4, b5, b6, b7, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(FacesCenter, l1) { EXPECT_EQ(X.twisted(Twist::l1), FacesCenter(a0, a1, a2, a3, a4, a5, a6, a7, b0, b1, c4, b3, b4, b5, c2, b7, c0, c1, b2, c3, b6, c5, c6, c7)); }
TEST(FacesCenter, R1) { EXPECT_EQ(X.twisted(Twist::R1), FacesCenter(a0, a1, a2, a3, a5, a6, a7, a4, b0, b1, b2, b3, b4, b5, b6, b7, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(FacesCenter, r1) { EXPECT_EQ(X.twisted(Twist::r1), FacesCenter(a0, a1, a2, a3, a4, a5, a6, a7, c0, b1, b2, b3, c6, b5, b6, b7, b4, c1, c2, c3, c4, c5, b0, c7)); }
TEST(FacesCenter, U1) { EXPECT_EQ(X.twisted(Twist::U1), FacesCenter(a0, a1, a2, a3, a4, a5, a6, a7, b1, b2, b3, b0, b4, b5, b6, b7, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(FacesCenter, u1) { EXPECT_EQ(X.twisted(Twist::u1), FacesCenter(a0, c1, a2, a3, a4, c5, a6, a7, b0, b1, b2, b3, b4, b5, b6, b7, c0, a5, c2, c3, c4, a1, c6, c7)); }
TEST(FacesCenter, D1) { EXPECT_EQ(X.twisted(Twist::D1), FacesCenter(a0, a1, a2, a3, a4, a5, a6, a7, b0, b1, b2, b3, b5, b6, b7, b4, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(FacesCenter, d1) { EXPECT_EQ(X.twisted(Twist::d1), FacesCenter(a0, a1, a2, c7, a4, a5, a6, c3, b0, b1, b2, b3, b4, b5, b6, b7, c0, c1, c2, a3, c4, c5, c6, a7)); }
TEST(FacesCenter, F1) { EXPECT_EQ(X.twisted(Twist::F1), FacesCenter(a0, a1, a2, a3, a4, a5, a6, a7, b0, b1, b2, b3, b4, b5, b6, b7, c1, c2, c3, c0, c4, c5, c6, c7)); }
TEST(FacesCenter, f1) { EXPECT_EQ(X.twisted(Twist::f1), FacesCenter(b5, a1, a2, a3, a4, a5, b3, a7, b0, b1, b2, a0, b4, a6, b6, b7, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(FacesCenter, B1) { EXPECT_EQ(X.twisted(Twist::B1), FacesCenter(a0, a1, a2, a3, a4, a5, a6, a7, b0, b1, b2, b3, b4, b5, b6, b7, c0, c1, c2, c3, c5, c6, c7, c4)); }
TEST(FacesCenter, b1) { EXPECT_EQ(X.twisted(Twist::b1), FacesCenter(a0, a1, b1, a3, b7, a5, a6, a7, b0, a4, b2, b3, b4, b5, b6, a2, c0, c1, c2, c3, c4, c5, c6, c7)); }

TEST(FacesSide, L1) { EXPECT_EQ(Y.twisted(Twist::L1), FacesSide(a2, a0, a3, a1, a4, a5, a6, a7, b0, b1, b2, b3, b4, b5, b6, b7, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(FacesSide, l1) { EXPECT_EQ(Y.twisted(Twist::l1), FacesSide(a0, a1, a2, a3, a4, a5, a6, a7, c7, b1, c5, b3, c0, b5, c2, b7, b0, c1, b2, c3, c4, b6, c6, b4)); }
TEST(FacesSide, R1) { EXPECT_EQ(Y.twisted(Twist::R1), FacesSide(a0, a1, a2, a3, a6, a4, a7, a5, b0, b1, b2, b3, b4, b5, b6, b7, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(FacesSide, r1) { EXPECT_EQ(Y.twisted(Twist::r1), FacesSide(a0, a1, a2, a3, a4, a5, a6, a7, b0, c1, b2, c3, b4, c6, b6, c4, c0, b5, c2, b7, b3, c5, b1, c7)); }
TEST(FacesSide, U1) { EXPECT_EQ(Y.twisted(Twist::U1), FacesSide(a0, a1, a2, a3, a4, a5, a6, a7, b2, b0, b3, b1, b4, b5, b6, b7, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(FacesSide, u1) { EXPECT_EQ(Y.twisted(Twist::u1), FacesSide(c0, c1, a2, a3, c4, c5, a6, a7, b0, b1, b2, b3, b4, b5, b6, b7, a4, a5, c2, c3, a0, a1, c6, c7)); }
TEST(FacesSide, D1) { EXPECT_EQ(Y.twisted(Twist::D1), FacesSide(a0, a1, a2, a3, a4, a5, a6, a7, b0, b1, b2, b3, b6, b4, b7, b5, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(FacesSide, d1) { EXPECT_EQ(Y.twisted(Twist::d1), FacesSide(a0, a1, c6, c7, a4, a5, c2, c3, b0, b1, b2, b3, b4, b5, b6, b7, c0, c1, a2, a3, c4, c5, a6, a7)); }
TEST(FacesSide, F1) { EXPECT_EQ(Y.twisted(Twist::F1), FacesSide(a0, a1, a2, a3, a4, a5, a6, a7, b0, b1, b2, b3, b4, b5, b6, b7, c2, c0, c3, c1, c4, c5, c6, c7)); }
TEST(FacesSide, f1) { EXPECT_EQ(Y.twisted(Twist::f1), FacesSide(a0, b4, a2, b5, b2, a5, b3, a7, b0, b1, a3, a1, a6, a4, b6, b7, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(FacesSide, B1) { EXPECT_EQ(Y.twisted(Twist::B1), FacesSide(a0, a1, a2, a3, a4, a5, a6, a7, b0, b1, b2, b3, b4, b5, b6, b7, c0, c1, c2, c3, c6, c4, c7, c5)); }
TEST(FacesSide, b1) { EXPECT_EQ(Y.twisted(Twist::b1), FacesSide(b1, a1, b0, a3, a4, b7, a6, b6, a5, a7, b2, b3, b4, b5, a0, a2, c0, c1, c2, c3, c4, c5, c6, c7)); }

class NameGenerator {
public:
	template <typename T>
	static std::string GetName(int) {
		if constexpr (std::is_same_v<T, Corners>)
			return "Corners";
		else if constexpr (std::is_same_v<T, EdgesCenter>)
			return "EdgesCenter";
		else if constexpr (std::is_same_v<T, EdgesSide>)
			return "EdgesSide";
		else if constexpr (std::is_same_v<T, FacesCenter>)
			return "FacesCenter";
		else if constexpr (std::is_same_v<T, FacesSide>)
			return "FacesSide";
		else if constexpr (std::is_same_v<T, Cube2x2>)
			return "Cube2x2";
		else if constexpr (std::is_same_v<T, Cube3x3>)
			return "Cube3x3";
		else if constexpr (std::is_same_v<T, Cube4x4>)
			return "Cube4x4";
		else if constexpr (std::is_same_v<T, Cube5x5>)
			return "Cube5x5";
		else
			static_assert(false);
	}
};

template <typename CubeType>
class CubeTest : public testing::Test {};

using CubeTypes = ::testing::Types<Corners, EdgesCenter, EdgesSide, FacesCenter, FacesSide, Cube2x2, Cube3x3, Cube4x4, Cube5x5>;
TYPED_TEST_CASE(CubeTest, CubeTypes, NameGenerator);

TYPED_TEST(CubeTest, is_solved)
{
	EXPECT_TRUE(TypeParam::solved().is_solved());
	EXPECT_FALSE(TypeParam::impossible().is_solved());
}

TYPED_TEST(CubeTest, twists)
{
	EXPECT_GT(TypeParam::twists.size(), 0);
}

TYPED_TEST(CubeTest, hash)
{
	std::hash<TypeParam> h;
	EXPECT_EQ(h(TypeParam::solved()), h(TypeParam::solved()));
	EXPECT_NE(h(TypeParam::solved()), h(TypeParam::impossible()));
}

TYPED_TEST(CubeTest, composed_twists)
{
	const auto c = TypeParam::solved();
	EXPECT_EQ(c.twisted(Twist::L2), c.twisted(Twist::L1, Twist::L1));
	EXPECT_EQ(c.twisted(Twist::L3), c.twisted(Twist::L1, Twist::L1, Twist::L1));
	EXPECT_EQ(c.twisted(Twist::R2), c.twisted(Twist::R1, Twist::R1));
	EXPECT_EQ(c.twisted(Twist::R3), c.twisted(Twist::R1, Twist::R1, Twist::R1));
	EXPECT_EQ(c.twisted(Twist::U2), c.twisted(Twist::U1, Twist::U1));
	EXPECT_EQ(c.twisted(Twist::U3), c.twisted(Twist::U1, Twist::U1, Twist::U1));
	EXPECT_EQ(c.twisted(Twist::D2), c.twisted(Twist::D1, Twist::D1));
	EXPECT_EQ(c.twisted(Twist::D3), c.twisted(Twist::D1, Twist::D1, Twist::D1));
	EXPECT_EQ(c.twisted(Twist::F2), c.twisted(Twist::F1, Twist::F1));
	EXPECT_EQ(c.twisted(Twist::F3), c.twisted(Twist::F1, Twist::F1, Twist::F1));
	EXPECT_EQ(c.twisted(Twist::B2), c.twisted(Twist::B1, Twist::B1));
	EXPECT_EQ(c.twisted(Twist::B3), c.twisted(Twist::B1, Twist::B1, Twist::B1));
	EXPECT_EQ(c.twisted(Twist::l2), c.twisted(Twist::l1, Twist::l1));
	EXPECT_EQ(c.twisted(Twist::l3), c.twisted(Twist::l1, Twist::l1, Twist::l1));
	EXPECT_EQ(c.twisted(Twist::r2), c.twisted(Twist::r1, Twist::r1));
	EXPECT_EQ(c.twisted(Twist::r3), c.twisted(Twist::r1, Twist::r1, Twist::r1));
	EXPECT_EQ(c.twisted(Twist::u2), c.twisted(Twist::u1, Twist::u1));
	EXPECT_EQ(c.twisted(Twist::u3), c.twisted(Twist::u1, Twist::u1, Twist::u1));
	EXPECT_EQ(c.twisted(Twist::d2), c.twisted(Twist::d1, Twist::d1));
	EXPECT_EQ(c.twisted(Twist::d3), c.twisted(Twist::d1, Twist::d1, Twist::d1));
	EXPECT_EQ(c.twisted(Twist::f2), c.twisted(Twist::f1, Twist::f1));
	EXPECT_EQ(c.twisted(Twist::f3), c.twisted(Twist::f1, Twist::f1, Twist::f1));
	EXPECT_EQ(c.twisted(Twist::b2), c.twisted(Twist::b1, Twist::b1));
	EXPECT_EQ(c.twisted(Twist::b3), c.twisted(Twist::b1, Twist::b1, Twist::b1));

}

TYPED_TEST(CubeTest, inverse_twists)
{
	for (Twist t : all_twists)
		EXPECT_TRUE(TypeParam::solved().twisted(t, inversed(t)).is_solved());
}

TYPED_TEST(CubeTest, twists_cycle)
{
	for (Twist t : all_twists)
		EXPECT_TRUE(TypeParam::solved().twisted(t, t, t, t).is_solved());
}

template <typename Twistable>
void expect_pairwise_commutation(const Twistable& t, Twist a, Twist b)
{
	EXPECT_EQ(t.twisted(a, b), t.twisted(b, a));
}

template <typename Twistable>
void expect_pairwise_commutation(const Twistable& t, Twist a, Twist b, Twist c, Twist d)
{
	expect_pairwise_commutation(t, a, b);
	expect_pairwise_commutation(t, a, c);
	expect_pairwise_commutation(t, a, d);
	expect_pairwise_commutation(t, b, c);
	expect_pairwise_commutation(t, b, d);
	expect_pairwise_commutation(t, c, d);
}

TYPED_TEST(CubeTest, commutation)
{
	const auto t = Cube5x5::solved();
	expect_pairwise_commutation(t, Twist::L1, Twist::l1, Twist::R1, Twist::r1);
	expect_pairwise_commutation(t, Twist::U1, Twist::u1, Twist::D1, Twist::d1);
	expect_pairwise_commutation(t, Twist::F1, Twist::f1, Twist::B1, Twist::b1);
}

TEST(Corners, state)
{
	std::array<uint8_t, 8> c = { 2, 3, 4, 5, 6, 7, 0, 1 }; // arbitrary
	std::array<uint8_t, 8> o = { 1, 2, 0, 1, 2, 0, 1, 2 }; // arbitrary
	Corners obj(c, o);
	for (int i = 0; i < c.size(); i++)
		EXPECT_EQ(obj.cubie(i), c[i]);
	for (int i = 0; i < o.size(); i++)
		EXPECT_EQ(obj.orientation(i), o[i]);
}

TEST(EdgesCenter, state)
{
	std::array<uint8_t, 12> c = { 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3 }; // arbitrary
	std::array<uint8_t, 12> o = { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }; // arbitrary
	EdgesCenter obj(c, o);
	for (int i = 0; i < c.size(); i++)
		EXPECT_EQ(obj.cubie(i), c[i]);
	for (int i = 0; i < o.size(); i++)
		EXPECT_EQ(obj.orientation(i), o[i]);
}

TEST(EdgesSide, state)
{
	std::vector<uint8_t> c = { 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5 }; // arbitrary
	EdgesSide obj(
		c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8], c[9], c[10], c[11],
		c[12], c[13], c[14], c[15], c[16], c[17], c[18], c[19], c[20], c[21], c[22], c[23]);
	for (int i = 0; i < c.size(); i++)
		EXPECT_EQ(obj.cubie(i), c[i]);
}

TEST(FacesCenter, state)
{
	std::vector<uint8_t> c = { 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5 }; // arbitrary
	FacesCenter obj(
		c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8], c[9], c[10], c[11],
		c[12], c[13], c[14], c[15], c[16], c[17], c[18], c[19], c[20], c[21], c[22], c[23]);
	for (int i = 0; i < c.size(); i++)
		EXPECT_EQ(obj.cubie(i), c[i]);
}

TEST(FacesSide, state)
{
	std::vector<uint8_t> c = { 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5 }; // arbitrary
	FacesSide obj(
		c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8], c[9], c[10], c[11],
		c[12], c[13], c[14], c[15], c[16], c[17], c[18], c[19], c[20], c[21], c[22], c[23]);
	for (int i = 0; i < c.size(); i++)
		EXPECT_EQ(obj.cubie(i), c[i]);
}

// Tests that all n cubies are in the range [0, max_value).
template <typename CubeType>
void cubie_twist_fuzzing(int n, int max_value)
{
	ASSERT_EQ(n % max_value, 0);
	RandomTwistGenerator gen(CubeType::twists, /*seed*/82349);
	CubeType c = CubeType::solved();
	for (int i = 0; i < 1'000'000; i++)
	{
		std::vector<int> cubie_count(max_value, 0);
		// Check that the cubies are in the range [0, max_value).
		for (int j = 0; j < n; j++)
		{
			auto cubie = c.cubie(j);
			EXPECT_GE(cubie, 0);
			EXPECT_LT(cubie, max_value);
			cubie_count[cubie]++;
		}

		// Check that each cubie occurs exactly cubies/max_value times.
		for (int count : cubie_count)
			EXPECT_EQ(count, n / max_value);

		c = c.twisted(gen());
	}
}

TEST(Corners, cubie_twist_fuzzing) { cubie_twist_fuzzing<Corners>(8, 8); }
TEST(EdgesCenter, cubie_twist_fuzzing) { cubie_twist_fuzzing<EdgesCenter>(12, 12); }
TEST(EdgesSide, cubie_twist_fuzzing) { cubie_twist_fuzzing<EdgesSide>(24, 24); }
TEST(FacesCenter, cubie_twist_fuzzing) { cubie_twist_fuzzing<FacesCenter>(24, 6); }
TEST(FacesSide, cubie_twist_fuzzing) { cubie_twist_fuzzing<FacesSide>(24, 6); }

// Tests that all n orientation of each cubie is in the range [0, max_value).
template <typename CubeType>
void orientation_twist_fuzzing(int n, int max_value)
{
	RandomTwistGenerator gen(CubeType::twists, /*seed*/82349);
	CubeType c = CubeType::solved();
	for (int i = 0; i < 1'000'000; i++)
	{
		// Check that the orientations are in the range [0, max_value).
		for (int j = 0; j < n; j++)
		{
			auto orientation = c.orientation(j);
			EXPECT_GE(orientation, 0);
			EXPECT_LT(orientation, max_value);
		}

		c = c.twisted(gen());
	}
}

TEST(Corners, orientation_twist_fuzzing) { orientation_twist_fuzzing<Corners>(8, 3); }
TEST(EdgesCenter, orientation_twist_fuzzing) { orientation_twist_fuzzing<EdgesCenter>(12, 2); }


TEST(Corners, prm_index)
{
	std::vector<uint64_t> indices;
	std::array<uint8_t, 8> p = { 0, 1, 2, 3, 4, 5, 6, 7 };
	do
	{
		Corners c(p, { 0, 0, 0, 0, 0, 0, 0, 0 });
		indices.push_back(c.prm_index());
	} while (std::next_permutation(p.begin(), p.end()));

	// Check that the indices cover {0, 1, 2, ..., 40319}.
	std::sort(indices.begin(), indices.end());
	EXPECT_EQ(indices.size(), factorial(8));
	for (int i = 0; i < factorial(8); i++)
		EXPECT_EQ(indices[i], i);
}

TEST(EdgesCenter, prm_index)
{
	EdgesCenter first({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
	EXPECT_EQ(first.prm_index(), 0);

	EdgesCenter last({ 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
	EXPECT_EQ(last.prm_index(), factorial(12) - 1);
}

TEST(EdgesSide, prm_index)
{
	EXPECT_EQ(EdgesSide::solved().prm_index(), 0);
}

TEST(FacesCenter, prm_index)
{
	EXPECT_EQ(FacesCenter::solved().prm_index(), 0);
}

TEST(FacesSide, prm_index)
{
	EXPECT_EQ(FacesSide::solved().prm_index(), 0);
}


TEST(Corners, ori_index)
{
	// This generates all possible orientations of the cubies.
	// Some are only rechable by disassembling the cube.
	// Thus each index is generated 3 times.
	std::vector<uint64_t> indices;
	for (int i = 0; i < std::pow(3, 8); i++)
	{
		std::array<uint8_t, 8> o;
		int n = i;
		for (int j = 0; j < 8; j++)
		{
			o[j] = n % 3;
			n /= 3;
		}
		Corners c({ 0, 1, 2, 3, 4, 5, 6, 7 }, o);
		indices.push_back(c.ori_index());
	}

	// Check that each index is contained 3 times.
	EXPECT_EQ(indices.size(), std::pow(3, 8));
	std::ranges::sort(indices);
	for (int i = 0; i < std::pow(3, 7); i++)
	{
		EXPECT_EQ(indices[i * 3], i);
		EXPECT_EQ(indices[i * 3 + 1], i);
		EXPECT_EQ(indices[i * 3 + 2], i);
	}
}

TEST(EdgesCenter, ori_index)
{
	// This generates all possible orientations of the cubies.
	// Some are only rechable by disassembling the cube.
	// Thus each index is generated 2 times.
	std::vector<uint64_t> indices;
	for (int i = 0; i < std::pow(2, 12); i++)
	{
		std::array<uint8_t, 12> o;
		int n = i;
		for (int j = 0; j < 12; j++)
		{
			o[j] = n % 2;
			n /= 2;
		}
		EdgesCenter c({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 }, o);
		indices.push_back(c.ori_index());
	}

	// Check that each index is contained 2 times.
	EXPECT_EQ(indices.size(), std::pow(2, 12));
	std::ranges::sort(indices);
	for (int i = 0; i < std::pow(2, 11); i++)
	{
		EXPECT_EQ(indices[i * 2], i);
		EXPECT_EQ(indices[i * 2 + 1], i);
	}
}