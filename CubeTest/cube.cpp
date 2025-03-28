#include "pch.h"
#include <vector>

template <typename CubeType>
class CubeTest : public testing::Test {};

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

using CubeTypes = ::testing::Types<Corners, EdgesCenter, EdgesSide, FacesCenter, FacesSide, Cube2x2, Cube3x3, Cube4x4, Cube5x5>;
TYPED_TEST_CASE(CubeTest, CubeTypes, NameGenerator);

TYPED_TEST(CubeTest, is_solved)
{
	EXPECT_TRUE(TypeParam::solved().is_solved());
	EXPECT_FALSE(TypeParam::impossible().is_solved());
}

TYPED_TEST(CubeTest, composed_twists)
{
	const auto c = TypeParam::solved();
	EXPECT_EQ(c.L2(), c.L1().L1());
	EXPECT_EQ(c.L3(), c.L1().L1().L1());
	EXPECT_EQ(c.R2(), c.R1().R1());
	EXPECT_EQ(c.R3(), c.R1().R1().R1());
	EXPECT_EQ(c.U2(), c.U1().U1());
	EXPECT_EQ(c.U3(), c.U1().U1().U1());
	EXPECT_EQ(c.D2(), c.D1().D1());
	EXPECT_EQ(c.D3(), c.D1().D1().D1());
	EXPECT_EQ(c.F2(), c.F1().F1());
	EXPECT_EQ(c.F3(), c.F1().F1().F1());
	EXPECT_EQ(c.B2(), c.B1().B1());
	EXPECT_EQ(c.B3(), c.B1().B1().B1());
	EXPECT_EQ(c.l2(), c.l1().l1());
	EXPECT_EQ(c.l3(), c.l1().l1().l1());
	EXPECT_EQ(c.r2(), c.r1().r1());
	EXPECT_EQ(c.r3(), c.r1().r1().r1());
	EXPECT_EQ(c.u2(), c.u1().u1());
	EXPECT_EQ(c.u3(), c.u1().u1().u1());
	EXPECT_EQ(c.d2(), c.d1().d1());
	EXPECT_EQ(c.d3(), c.d1().d1().d1());
	EXPECT_EQ(c.f2(), c.f1().f1());
	EXPECT_EQ(c.f3(), c.f1().f1().f1());
	EXPECT_EQ(c.b2(), c.b1().b1());
	EXPECT_EQ(c.b3(), c.b1().b1().b1());
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
	EXPECT_EQ(t.twisted(a).twisted(b), t.twisted(b).twisted(a));
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
	std::vector<uint8_t> c = { 2, 3, 4, 5, 6, 7, 0, 1 }; // arbitrary
	std::vector<uint8_t> o = { 1, 2, 0, 1, 2, 0, 1, 2 }; // arbitrary
	Corners obj(
		c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7],
		o[0], o[1], o[2], o[3], o[4], o[5], o[6], o[7]);
	for (int i = 0; i < c.size(); i++)
		EXPECT_EQ(obj.cubie(i), c[i]);
	for (int i = 0; i < o.size(); i++)
		EXPECT_EQ(obj.orientation(i), o[i]);
}

TEST(EdgesCenter, state)
{
	std::vector<uint8_t> c = { 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3 }; // arbitrary
	std::vector<uint8_t> o = { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }; // arbitrary
	EdgesCenter obj(
		c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8], c[9], c[10], c[11],
		o[0], o[1], o[2], o[3], o[4], o[5], o[6], o[7], o[8], o[9], o[10], o[11]);
	for (int i = 0; i < c.size(); i++)
		EXPECT_EQ(obj.cubie(i), c[i]);
	for (int i = 0; i < o.size(); i++)
		EXPECT_EQ(obj.orientation(i), o[i]);
}

TEST(EdgesSide, state)
{
	std::vector<uint8_t> c = { 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3 }; // arbitrary
	EdgesSide obj(
		c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8], c[9], c[10], c[11],
		c[12], c[13], c[14], c[15], c[16], c[17], c[18], c[19], c[20], c[21], c[22], c[23]);
	for (int i = 0; i < c.size(); i++)
		EXPECT_EQ(obj.cubie(i), c[i]);
}

TEST(FacesCenter, state)
{
	std::vector<uint8_t> c = { 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3 }; // arbitrary
	FacesCenter obj(
		c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8], c[9], c[10], c[11],
		c[12], c[13], c[14], c[15], c[16], c[17], c[18], c[19], c[20], c[21], c[22], c[23]);
	for (int i = 0; i < c.size(); i++)
		EXPECT_EQ(obj.cubie(i), c[i]);
}

TEST(FacesSide, state)
{
	std::vector<uint8_t> c = { 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3 }; // arbitrary
	FacesSide obj(
		c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8], c[9], c[10], c[11],
		c[12], c[13], c[14], c[15], c[16], c[17], c[18], c[19], c[20], c[21], c[22], c[23]);
	for (int i = 0; i < c.size(); i++)
		EXPECT_EQ(obj.cubie(i), c[i]);
}

const uint8_t a0 = 0, a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6, a7 = 7;
const uint8_t b0 = 8, b1 = 9, b2 = 10, b3 = 11, b4 = 12, b5 = 13, b6 = 14, b7 = 15;
const uint8_t c0 = 16, c1 = 17, c2 = 18, c3 = 19, c4 = 20, c5 = 21, c6 = 22, c7 = 23;
const FacesCenter X = FacesCenter(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23);
const FacesSide Y = FacesSide(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23);

TEST(Corners, L1) { EXPECT_EQ(Corners::solved().L1(), Corners(2, 1, 6, 3, 0, 5, 4, 7, 2, 0, 2, 0, 2, 0, 2, 0)); }
TEST(Corners, R1) { EXPECT_EQ(Corners::solved().R1(), Corners(0, 5, 2, 1, 4, 7, 6, 3, 0, 2, 0, 2, 0, 2, 0, 2)); }
TEST(Corners, U1) { EXPECT_EQ(Corners::solved().U1(), Corners(1, 3, 0, 2, 4, 5, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0)); }
TEST(Corners, D1) { EXPECT_EQ(Corners::solved().D1(), Corners(0, 1, 2, 3, 6, 4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0)); }
TEST(Corners, F1) { EXPECT_EQ(Corners::solved().F1(), Corners(4, 0, 2, 3, 5, 1, 6, 7, 1, 1, 0, 0, 1, 1, 0, 0)); }
TEST(Corners, B1) { EXPECT_EQ(Corners::solved().B1(), Corners(0, 1, 3, 7, 4, 5, 2, 6, 0, 0, 1, 1, 0, 0, 1, 1)); }

TEST(EdgesCenter, L1) { EXPECT_EQ(EdgesCenter::solved().L1(), EdgesCenter(0, 1, 2, 11, 4, 5, 6, 8, 3, 9, 10, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)); }
TEST(EdgesCenter, R1) { EXPECT_EQ(EdgesCenter::solved().R1(), EdgesCenter(0, 9, 2, 3, 4, 10, 6, 7, 8, 5, 1, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)); }
TEST(EdgesCenter, U1) { EXPECT_EQ(EdgesCenter::solved().U1(), EdgesCenter(1, 2, 3, 0, 4, 5, 6, 7, 8, 9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)); }
TEST(EdgesCenter, D1) { EXPECT_EQ(EdgesCenter::solved().D1(), EdgesCenter(0, 1, 2, 3, 7, 4, 5, 6, 8, 9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)); }
TEST(EdgesCenter, F1) { EXPECT_EQ(EdgesCenter::solved().F1(), EdgesCenter(8, 1, 2, 3, 9, 5, 6, 7, 4, 0, 10, 11, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0)); }
TEST(EdgesCenter, B1) { EXPECT_EQ(EdgesCenter::solved().B1(), EdgesCenter(0, 1, 10, 3, 4, 5, 11, 7, 8, 9, 6, 2, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1)); }

TEST(EdgesSide, L1) { EXPECT_EQ(EdgesSide::solved().L1(), EdgesSide(a0, a1, a2, a3, a4, a5, a6, a7, c1, c0, b2, b3, b4, b5, c3, c2, b6, b7, b0, b1, c4, c5, c6, c7)); }
TEST(EdgesSide, l1) { EXPECT_EQ(EdgesSide::solved().l1(), EdgesSide(a2, a1, a4, a3, a6, a5, a0, a7, b0, b1, b2, b3, b4, b5, b6, b7, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(EdgesSide, R1) { EXPECT_EQ(EdgesSide::solved().R1(), EdgesSide(a0, a1, a2, a3, a4, a5, a6, a7, b0, b1, c4, c5, c6, c7, b6, b7, c0, c1, c2, c3, b5, b4, b3, b2)); }
TEST(EdgesSide, r1) { EXPECT_EQ(EdgesSide::solved().r1(), EdgesSide(a0, a7, a2, a1, a4, a3, a6, a5, b0, b1, b2, b3, b4, b5, b6, b7, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(EdgesSide, U1) { EXPECT_EQ(EdgesSide::solved().U1(), EdgesSide(c6, c7, c0, c1, a4, a5, a6, a7, b0, b1, b2, b3, b4, b5, b6, b7, a1, a0, c2, c3, c4, c5, a3, a2)); }
TEST(EdgesSide, u1) { EXPECT_EQ(EdgesSide::solved().u1(), EdgesSide(a0, a1, a2, a3, a4, a5, a6, a7, b2, b1, b4, b3, b6, b5, b0, b7, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(EdgesSide, D1) { EXPECT_EQ(EdgesSide::solved().D1(), EdgesSide(a0, a1, a2, a3, c5, c4, c3, c2, b0, b1, b2, b3, b4, b5, b6, b7, c0, c1, a4, a5, a6, a7, c6, c7)); }
TEST(EdgesSide, d1) { EXPECT_EQ(EdgesSide::solved().d1(), EdgesSide(a0, a1, a2, a3, a4, a5, a6, a7, b0, b7, b2, b1, b4, b3, b6, b5, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(EdgesSide, F1) { EXPECT_EQ(EdgesSide::solved().F1(), EdgesSide(b1, b0, a2, a3, a4, a5, b3, b2, a6, a7, a0, a1, b4, b5, b6, b7, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(EdgesSide, f1) { EXPECT_EQ(EdgesSide::solved().f1(), EdgesSide(a0, a1, a2, a3, a4, a5, a6, a7, b0, b1, b2, b3, b4, b5, b6, b7, c2, c1, c4, c3, c6, c5, c0, c7)); }
TEST(EdgesSide, B1) { EXPECT_EQ(EdgesSide::solved().B1(), EdgesSide(a0, a1, b4, b5, b6, b7, a6, a7, b0, b1, b2, b3, a5, a4, a3, a2, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(EdgesSide, b1) { EXPECT_EQ(EdgesSide::solved().b1(), EdgesSide(a0, a1, a2, a3, a4, a5, a6, a7, b0, b1, b2, b3, b4, b5, b6, b7, c0, c7, c2, c1, c4, c3, c6, c5)); }

TEST(FacesCenter, L1) { EXPECT_EQ(X.L1(), FacesCenter(a1, a2, a3, a0, a4, a5, a6, a7, b0, b1, b2, b3, b4, b5, b6, b7, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(FacesCenter, l1) { EXPECT_EQ(X.l1(), FacesCenter(a0, a1, a2, a3, a4, a5, a6, a7, b0, b1, c4, b3, b4, b5, c2, b7, c0, c1, b2, c3, b6, c5, c6, c7)); }
TEST(FacesCenter, R1) { EXPECT_EQ(X.R1(), FacesCenter(a0, a1, a2, a3, a5, a6, a7, a4, b0, b1, b2, b3, b4, b5, b6, b7, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(FacesCenter, r1) { EXPECT_EQ(X.r1(), FacesCenter(a0, a1, a2, a3, a4, a5, a6, a7, c0, b1, b2, b3, c6, b5, b6, b7, b4, c1, c2, c3, c4, c5, b0, c7)); }
TEST(FacesCenter, U1) { EXPECT_EQ(X.U1(), FacesCenter(a0, a1, a2, a3, a4, a5, a6, a7, b1, b2, b3, b0, b4, b5, b6, b7, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(FacesCenter, u1) { EXPECT_EQ(X.u1(), FacesCenter(a0, c1, a2, a3, a4, c5, a6, a7, b0, b1, b2, b3, b4, b5, b6, b7, c0, a5, c2, c3, c4, a1, c6, c7)); }
TEST(FacesCenter, D1) { EXPECT_EQ(X.D1(), FacesCenter(a0, a1, a2, a3, a4, a5, a6, a7, b0, b1, b2, b3, b5, b6, b7, b4, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(FacesCenter, d1) { EXPECT_EQ(X.d1(), FacesCenter(a0, a1, a2, c7, a4, a5, a6, c3, b0, b1, b2, b3, b4, b5, b6, b7, c0, c1, c2, a3, c4, c5, c6, a7)); }
TEST(FacesCenter, F1) { EXPECT_EQ(X.F1(), FacesCenter(a0, a1, a2, a3, a4, a5, a6, a7, b0, b1, b2, b3, b4, b5, b6, b7, c1, c2, c3, c0, c4, c5, c6, c7)); }
TEST(FacesCenter, f1) { EXPECT_EQ(X.f1(), FacesCenter(b5, a1, a2, a3, a4, a5, b3, a7, b0, b1, b2, a0, b4, a6, b6, b7, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(FacesCenter, B1) { EXPECT_EQ(X.B1(), FacesCenter(a0, a1, a2, a3, a4, a5, a6, a7, b0, b1, b2, b3, b4, b5, b6, b7, c0, c1, c2, c3, c5, c6, c7, c4)); }
TEST(FacesCenter, b1) { EXPECT_EQ(X.b1(), FacesCenter(a0, a1, b1, a3, b7, a5, a6, a7, b0, a4, b2, b3, b4, b5, b6, a2, c0, c1, c2, c3, c4, c5, c6, c7)); }

TEST(FacesSide, L1) { EXPECT_EQ(Y.L1(), FacesSide(a2, a0, a3, a1, a4, a5, a6, a7, b0, b1, b2, b3, b4, b5, b6, b7, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(FacesSide, l1) { EXPECT_EQ(Y.l1(), FacesSide(a0, a1, a2, a3, a4, a5, a6, a7, c7, b1, c5, b3, c0, b5, c2, b7, b0, c1, b2, c3, c4, b6, c6, b4)); }
TEST(FacesSide, R1) { EXPECT_EQ(Y.R1(), FacesSide(a0, a1, a2, a3, a6, a4, a7, a5, b0, b1, b2, b3, b4, b5, b6, b7, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(FacesSide, r1) { EXPECT_EQ(Y.r1(), FacesSide(a0, a1, a2, a3, a4, a5, a6, a7, b0, c1, b2, c3, b4, c6, b6, c4, c0, b5, c2, b7, b3, c5, b1, c7)); }
TEST(FacesSide, U1) { EXPECT_EQ(Y.U1(), FacesSide(a0, a1, a2, a3, a4, a5, a6, a7, b2, b0, b3, b1, b4, b5, b6, b7, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(FacesSide, u1) { EXPECT_EQ(Y.u1(), FacesSide(c0, c1, a2, a3, c4, c5, a6, a7, b0, b1, b2, b3, b4, b5, b6, b7, a4, a5, c2, c3, a0, a1, c6, c7)); }
TEST(FacesSide, D1) { EXPECT_EQ(Y.D1(), FacesSide(a0, a1, a2, a3, a4, a5, a6, a7, b0, b1, b2, b3, b6, b4, b7, b5, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(FacesSide, d1) { EXPECT_EQ(Y.d1(), FacesSide(a0, a1, c6, c7, a4, a5, c2, c3, b0, b1, b2, b3, b4, b5, b6, b7, c0, c1, a2, a3, c4, c5, a6, a7)); }
TEST(FacesSide, F1) { EXPECT_EQ(Y.F1(), FacesSide(a0, a1, a2, a3, a4, a5, a6, a7, b0, b1, b2, b3, b4, b5, b6, b7, c2, c0, c3, c1, c4, c5, c6, c7)); }
TEST(FacesSide, f1) { EXPECT_EQ(Y.f1(), FacesSide(a0, b4, a2, b5, b2, a5, b3, a7, b0, b1, a3, a1, a6, a4, b6, b7, c0, c1, c2, c3, c4, c5, c6, c7)); }
TEST(FacesSide, B1) { EXPECT_EQ(Y.B1(), FacesSide(a0, a1, a2, a3, a4, a5, a6, a7, b0, b1, b2, b3, b4, b5, b6, b7, c0, c1, c2, c3, c6, c4, c7, c5)); }
TEST(FacesSide, b1) { EXPECT_EQ(Y.b1(), FacesSide(b1, a1, b0, a3, a4, b7, a6, b6, a5, a7, b2, b3, b4, b5, a0, a2, c0, c1, c2, c3, c4, c5, c6, c7)); }

template <typename CubeType>
void twist_fuzzing()