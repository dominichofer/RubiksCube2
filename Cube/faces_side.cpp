#include "faces_side.h"
#include "bit.h"
#include "intrin.h"
#include "Math/math.h"

const std::vector<Twist> FacesSide::twists = {
	Twist::L1, Twist::L2, Twist::L3, Twist::l1, Twist::l2, Twist::l3,
	Twist::R1, Twist::R2, Twist::R3, Twist::r1, Twist::r2, Twist::r3,
	Twist::U1, Twist::U2, Twist::U3, Twist::u1, Twist::u2, Twist::u3,
	Twist::D1, Twist::D2, Twist::D3, Twist::d1, Twist::d2, Twist::d3,
	Twist::F1, Twist::F2, Twist::F3, Twist::f1, Twist::f2, Twist::f3,
	Twist::B1, Twist::B2, Twist::B3, Twist::b1, Twist::b2, Twist::b3
};

FacesSide::FacesSide(
	uint8_t f0, uint8_t f1, uint8_t f2, uint8_t f3,
	uint8_t f4, uint8_t f5, uint8_t f6, uint8_t f7,
	uint8_t f8, uint8_t f9, uint8_t f10, uint8_t f11,
	uint8_t f12, uint8_t f13, uint8_t f14, uint8_t f15,
	uint8_t f16, uint8_t f17, uint8_t f18, uint8_t f19,
	uint8_t f20, uint8_t f21, uint8_t f22, uint8_t f23) noexcept
{
	a = set_epi8(f0, f1, f2, f3, f4, f5, f6, f7);
	b = set_epi8(f8, f9, f10, f11, f12, f13, f14, f15);
	c = set_epi8(f16, f17, f18, f19, f20, f21, f22, f23);
}

FacesSide FacesSide::solved()
{
	return FacesSide(
		0, 0, 0, 0,
		1, 1, 1, 1,
		2, 2, 2, 2,
		3, 3, 3, 3,
		4, 4, 4, 4,
		5, 5, 5, 5);
}

FacesSide FacesSide::impossible()
{
	return FacesSide(
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0);
}

bool FacesSide::is_solved() const
{
	return *this == FacesSide::solved();
}

int FacesSide::cubie(int i) const
{
	if (i < 8)
		return extract_epi8(a, i);
	if (i < 16)
		return extract_epi8(b, i - 8);
	return extract_epi8(c, i - 16);
}

FacesSide FacesSide::twisted(Twist t) const
{
	const int i0 = 8, i1 = 9, i2 = 10, i3 = 11, i4 = 12, i5 = 13, i6 = 14, i7 = 15;
	uint64_t A, B, C;
	switch (t)
	{
	case Twist::L1:
		A = byte_shuffle(a, 2, 0, 3, 1, 4, 5, 6, 7);
		return { A, b, c };
	case Twist::L2:
		A = byte_shuffle(a, 3, 2, 1, 0, 4, 5, 6, 7);
		return { A, b, c };
	case Twist::L3:
		A = byte_shuffle(a, 1, 3, 0, 2, 4, 5, 6, 7);
		return { A, b, c };
	case Twist::l1:
		std::tie(B, C) = byte_shuffle(
			b, c,
			i7, 1, i5, 3, i0, 5, i2, 7,
			0, i1, 2, i3, i4, 6, i6, 4);
		return { a, B, C };
	case Twist::l2:
		std::tie(B, C) = byte_shuffle(
			b, c,
			4, 1, 6, 3, 0, 5, 2, 7,
			i7, i1, i5, i3, i4, i2, i6, i0);
		return { a, B, C };
	case Twist::l3:
		std::tie(B, C) = byte_shuffle(
			b, c,
			i0, 1, i2, 3, i7, 5, i5, 7,
			4, i1, 6, i3, i4, 2, i6, 0);
		return { a, B, C };
	case Twist::R1:
		A = byte_shuffle(a, 0, 1, 2, 3, 6, 4, 7, 5);
		return { A, b, c };
	case Twist::R2:
		A = byte_shuffle(a, 0, 1, 2, 3, 7, 6, 5, 4);
		return { A, b, c };
	case Twist::R3:
		A = byte_shuffle(a, 0, 1, 2, 3, 5, 7, 4, 6);
		return { A, b, c };
	case Twist::r1:
		std::tie(B, C) = byte_shuffle(
			b, c,
			0, i1, 2, i3, 4, i6, 6, i4,
			i0, 5, i2, 7, 3, i5, 1, i7);
		return { a, B, C };
	case Twist::r2:
		std::tie(B, C) = byte_shuffle(
			b, c,
			0, 5, 2, 7, 4, 1, 6, 3,
			i0, i6, i2, i4, i3, i5, i1, i7);
		return { a, B, C };
	case Twist::r3:
		std::tie(B, C) = byte_shuffle(
			b, c,
			0, i6, 2, i4, 4, i1, 6, i3,
			i0, 1, i2, 3, 7, i5, 5, i7);
		return { a, B, C };
	case Twist::U1:
		B = byte_shuffle(b, 2, 0, 3, 1, 4, 5, 6, 7);
		return { a, B, c };
	case Twist::U2:
		B = byte_shuffle(b, 3, 2, 1, 0, 4, 5, 6, 7);
		return { a, B, c };
	case Twist::U3:
		B = byte_shuffle(b, 1, 3, 0, 2, 4, 5, 6, 7);
		return { a, B, c };
	case Twist::u1:
		std::tie(A, C) = byte_shuffle(
			a, c,
			i0, i1, 2, 3, i4, i5, 6, 7,
			4, 5, i2, i3, 0, 1, i6, i7);
		return { A, b, C };
	case Twist::u2:
		std::tie(A, C) = byte_shuffle(
			a, c,
			4, 5, 2, 3, 0, 1, 6, 7,
			i4, i5, i2, i3, i0, i1, i6, i7);
		return { A, b, C };
	case Twist::u3:
		std::tie(A, C) = byte_shuffle(
			a, c,
			i4, i5, 2, 3, i0, i1, 6, 7,
			0, 1, i2, i3, 4, 5, i6, i7);
		return { A, b, C };
	case Twist::D1:
		B = byte_shuffle(b, 0, 1, 2, 3, 6, 4, 7, 5);
		return { a, B, c };
	case Twist::D2:
		B = byte_shuffle(b, 0, 1, 2, 3, 7, 6, 5, 4);
		return { a, B, c };
	case Twist::D3:
		B = byte_shuffle(b, 0, 1, 2, 3, 5, 7, 4, 6);
		return { a, B, c };
	case Twist::d1:
		std::tie(A, C) = byte_shuffle(
			a, c,
			0, 1, i6, i7, 4, 5, i2, i3,
			i0, i1, 2, 3, i4, i5, 6, 7);
		return { A, b, C };
	case Twist::d2:
		std::tie(A, C) = byte_shuffle(
			a, c,
			0, 1, 6, 7, 4, 5, 2, 3,
			i0, i1, i6, i7, i4, i5, i2, i3);
		return { A, b, C };
	case Twist::d3:
		std::tie(A, C) = byte_shuffle(
			a, c,
			0, 1, i2, i3, 4, 5, i6, i7,
			i0, i1, 6, 7, i4, i5, 2, 3);
		return { A, b, C };
	case Twist::F1:
		C = byte_shuffle(c, 2, 0, 3, 1, 4, 5, 6, 7);
		return { a, b, C };
	case Twist::F2:
		C = byte_shuffle(c, 3, 2, 1, 0, 4, 5, 6, 7);
		return { a, b, C };
	case Twist::F3:
		C = byte_shuffle(c, 1, 3, 0, 2, 4, 5, 6, 7);
		return { a, b, C };
	case Twist::f1:
		std::tie(A, B) = byte_shuffle(
			a, b,
			0, i4, 2, i5, i2, 5, i3, 7,
			i0, i1, 3, 1, 6, 4, i6, i7);
		return { A, B, c };
	case Twist::f2:
		std::tie(A, B) = byte_shuffle(
			a, b,
			0, 6, 2, 4, 3, 5, 1, 7,
			i0, i1, i5, i4, i3, i2, i6, i7);
		return { A, B, c };
	case Twist::f3:
		std::tie(A, B) = byte_shuffle(
			a, b,
			0, i3, 2, i2, i5, 5, i4, 7,
			i0, i1, 4, 6, 1, 3, i6, i7);
		return { A, B, c };
	case Twist::B1:
		C = byte_shuffle(c, 0, 1, 2, 3, 6, 4, 7, 5);
		return { a, b, C };
	case Twist::B2:
		C = byte_shuffle(c, 0, 1, 2, 3, 7, 6, 5, 4);
		return { a, b, C };
	case Twist::B3:
		C = byte_shuffle(c, 0, 1, 2, 3, 5, 7, 4, 6);
		return { a, b, C };
	case Twist::b1:
		std::tie(A, B) = byte_shuffle(
			a, b,
			i1, 1, i0, 3, 4, i7, 6, i6,
			5, 7, i2, i3, i4, i5, 0, 2);
		return { A, B, c };
	case Twist::b2:
		std::tie(A, B) = byte_shuffle(
			a, b,
			7, 1, 5, 3, 4, 2, 6, 0,
			i7, i6, i2, i3, i4, i5, i1, i0);
		return { A, B, c };
	case Twist::b3:
		std::tie(A, B) = byte_shuffle(
			a, b,
			i6, 1, i7, 3, 4, i0, 6, i1,
			2, 0, i2, i3, i4, i5, 7, 5);
		return { A, B, c };
	default: return *this;
	}
}

uint64_t FacesSide::prm_index() const
{
	// TODO: Implement this function!
	return 0;
}

uint64_t FacesSide::index() const
{
	return prm_index();
}

uint64_t FacesSide::hash() const
{
	return ::hash(a, b, c);
}

std::string to_string(const FacesSide& f)
{
	std::string str;
	for (int i = 0; i < 24; i++)
		str += std::to_string(f.cubie(i)) + ' ';
	str.pop_back();
	return str;
}