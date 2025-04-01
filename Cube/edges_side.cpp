#include "edges_side.h"
#include "bit.h"
#include "Math/math.h"
#include <stdexcept>

const std::vector<Twist> EdgesSide::twists = {
	Twist::L1, Twist::L2, Twist::L3, Twist::l1, Twist::l2, Twist::l3,
	Twist::R1, Twist::R2, Twist::R3, Twist::r1, Twist::r2, Twist::r3,
	Twist::U1, Twist::U2, Twist::U3, Twist::u1, Twist::u2, Twist::u3,
	Twist::D1, Twist::D2, Twist::D3, Twist::d1, Twist::d2, Twist::d3,
	Twist::F1, Twist::F2, Twist::F3, Twist::f1, Twist::f2, Twist::f3,
	Twist::B1, Twist::B2, Twist::B3, Twist::b1, Twist::b2, Twist::b3
};

EdgesSide::EdgesSide(
	uint8_t a0, uint8_t a1, uint8_t a2, uint8_t a3,
	uint8_t a4, uint8_t a5, uint8_t a6, uint8_t a7,
	uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3,
	uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7,
	uint8_t c0, uint8_t c1, uint8_t c2, uint8_t c3,
	uint8_t c4, uint8_t c5, uint8_t c6, uint8_t c7) noexcept
{
	a = set_epi8(a0, a1, a2, a3, a4, a5, a6, a7);
	b = set_epi8(b0, b1, b2, b3, b4, b5, b6, b7);
	c = set_epi8(c0, c1, c2, c3, c4, c5, c6, c7);
}
EdgesSide EdgesSide::solved() { return EdgesSide(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23); }
EdgesSide EdgesSide::impossible() { return EdgesSide(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); }

bool EdgesSide::is_solved() const
{
	return *this == EdgesSide::solved();
}

int EdgesSide::cubie(int i) const
{
	if (i < 8)
		return extract_epi8(a, i);
	if (i < 16)
		return extract_epi8(b, i - 8);
	return extract_epi8(c, i - 16);
}

EdgesSide EdgesSide::twisted(Twist t) const
{
	const int i0 = 8, i1 = 9, i2 = 10, i3 = 11, i4 = 12, i5 = 13, i6 = 14, i7 = 15;
	uint64_t A, B, C;
	switch (t)
	{
	case Twist::L1:
		std::tie(B, C) = byte_shuffle(
			b, c,
			i1, i0, 2, 3, 4, 5, i3, i2,
			6, 7, 0, 1, i4, i5, i6, i7);
		return { a, B, C };
	case Twist::L2:
		std::tie(B, C) = byte_shuffle(
			b, c,
			7, 6, 2, 3, 4, 5, 1, 0,
			i3, i2, i1, i0, i4, i5, i6, i7);
		return { a, B, C };
	case Twist::L3:
		std::tie(B, C) = byte_shuffle(
			b, c,
			i2, i3, 2, 3, 4, 5, i0, i1,
			1, 0, 7, 6, i4, i5, i6, i7);
		return { a, B, C };
	case Twist::l1:
		A = byte_shuffle(a, 2, 1, 4, 3, 6, 5, 0, 7);
		return { A, b, c };
	case Twist::l2:
		A = byte_shuffle(a, 4, 1, 6, 3, 0, 5, 2, 7);
		return { A, b, c };
	case Twist::l3:
		A = byte_shuffle(a, 6, 1, 0, 3, 2, 5, 4, 7);
		return { A, b, c };
	case Twist::R1:
		std::tie(B, C) = byte_shuffle(
			b, c,
			0, 1, i4, i5, i6, i7, 6, 7,
			i0, i1, i2, i3, 5, 4, 3, 2);
		return { a, B, C };
	case Twist::R2:
		std::tie(B, C) = byte_shuffle(
			b, c,
			0, 1, 5, 4, 3, 2, 6, 7,
			i0, i1, i2, i3, i7, i6, i5, i4);
		return { a, B, C };
	case Twist::R3:
		std::tie(B, C) = byte_shuffle(
			b, c,
			0, 1, i7, i6, i5, i4, 6, 7,
			i0, i1, i2, i3, 2, 3, 4, 5);
		return { a, B, C };
	case Twist::r1:
		A = byte_shuffle(a, 0, 7, 2, 1, 4, 3, 6, 5);
		return { A, b, c };
	case Twist::r2:
		A = byte_shuffle(a, 0, 5, 2, 7, 4, 1, 6, 3);
		return { A, b, c };
	case Twist::r3:
		A = byte_shuffle(a, 0, 3, 2, 5, 4, 7, 6, 1);
		return { A, b, c };
	case Twist::U1:
		std::tie(A, C) = byte_shuffle(
			a, c,
			i6, i7, i0, i1, 4, 5, 6, 7,
			1, 0, i2, i3, i4, i5, 3, 2);
		return { A, b, C };
	case Twist::U2:
		std::tie(A, C) = byte_shuffle(
			a, c,
			3, 2, 1, 0, 4, 5, 6, 7,
			i7, i6, i2, i3, i4, i5, i1, i0);
		return { A, b, C };
	case Twist::U3:
		std::tie(A, C) = byte_shuffle(
			a, c,
			i1, i0, i7, i6, 4, 5, 6, 7,
			2, 3, i2, i3, i4, i5, 0, 1);
		return { A, b, C };
	case Twist::u1:
		B = byte_shuffle(b, 2, 1, 4, 3, 6, 5, 0, 7);
		return { a, B, c };
	case Twist::u2:
		B = byte_shuffle(b, 4, 1, 6, 3, 0, 5, 2, 7);
		return { a, B, c };
	case Twist::u3:
		B = byte_shuffle(b, 6, 1, 0, 3, 2, 5, 4, 7);
		return { a, B, c };
	case Twist::D1:
		std::tie(A, C) = byte_shuffle(
			a, c,
			0, 1, 2, 3, i5, i4, i3, i2,
			i0, i1, 4, 5, 6, 7, i6, i7);
		return { A, b, C };
	case Twist::D2:
		std::tie(A, C) = byte_shuffle(
			a, c,
			0, 1, 2, 3, 7, 6, 5, 4,
			i0, i1, i5, i4, i3, i2, i6, i7);
		return { A, b, C };
	case Twist::D3:
		std::tie(A, C) = byte_shuffle(
			a, c,
			0, 1, 2, 3, i2, i3, i4, i5,
			i0, i1, 7, 6, 5, 4, i6, i7);
		return { A, b, C };
	case Twist::d1:
		B = byte_shuffle(b, 0, 7, 2, 1, 4, 3, 6, 5);
		return { a, B, c };
	case Twist::d2:
		B = byte_shuffle(b, 0, 5, 2, 7, 4, 1, 6, 3);
		return { a, B, c };
	case Twist::d3:
		B = byte_shuffle(b, 0, 3, 2, 5, 4, 7, 6, 1);
		return { a, B, c };
	case Twist::F1:
		std::tie(A, B) = byte_shuffle(
			a, b,
			i1, i0, 2, 3, 4, 5, i3, i2,
			6, 7, 0, 1, i4, i5, i6, i7);
		return { A, B, c };
	case Twist::F2:
		std::tie(A, B) = byte_shuffle(
			a, b,
			7, 6, 2, 3, 4, 5, 1, 0,
			i3, i2, i1, i0, i4, i5, i6, i7);
		return { A, B, c };
	case Twist::F3:
		std::tie(A, B) = byte_shuffle(
			a, b,
			i2, i3, 2, 3, 4, 5, i0, i1,
			1, 0, 7, 6, i4, i5, i6, i7);
		return { A, B, c };
	case Twist::f1:
		C = byte_shuffle(c, 2, 1, 4, 3, 6, 5, 0, 7);
		return { a, b, C };
	case Twist::f2:
		C = byte_shuffle(c, 4, 1, 6, 3, 0, 5, 2, 7);
		return { a, b, C };
	case Twist::f3:
		C = byte_shuffle(c, 6, 1, 0, 3, 2, 5, 4, 7);
		return { a, b, C };
	case Twist::B1:
		std::tie(A, B) = byte_shuffle(
			a, b,
			0, 1, i4, i5, i6, i7, 6, 7,
			i0, i1, i2, i3, 5, 4, 3, 2);
		return { A, B, c };
	case Twist::B2:
		std::tie(A, B) = byte_shuffle(
			a, b,
			0, 1, 5, 4, 3, 2, 6, 7,
			i0, i1, i2, i3, i7, i6, i5, i4);
		return { A, B, c };
	case Twist::B3:
		std::tie(A, B) = byte_shuffle(
			a, b,
			0, 1, i7, i6, i5, i4, 6, 7,
			i0, i1, i2, i3, 2, 3, 4, 5);
		return { A, B, c };
	case Twist::b1:
		C = byte_shuffle(c, 0, 7, 2, 1, 4, 3, 6, 5);
		return { a, b, C };
	case Twist::b2:
		C = byte_shuffle(c, 0, 5, 2, 7, 4, 1, 6, 3);
		return { a, b, C };
	case Twist::b3:
		C = byte_shuffle(c, 0, 3, 2, 5, 4, 7, 6, 1);
		return { a, b, C };
	default: return *this;
	}
}

uint64_t EdgesSide::prm_index() const
{
	return 0;
	// TODO!
	//return permutation_index(
	//	cubie(0), cubie(1), cubie(2), cubie(3),
	//	cubie(4), cubie(5), cubie(6), cubie(7),
	//	cubie(8), cubie(9), cubie(10), cubie(11),
	//	cubie(12), cubie(13), cubie(14), cubie(15),
	//	cubie(16), cubie(17), cubie(18), cubie(19),
	//	cubie(20), cubie(21), cubie(22), cubie(23));
}

uint64_t EdgesSide::index() const
{
	return prm_index();
}

uint64_t EdgesSide::hash() const
{
	return ::hash(a, b, c);
}

std::string to_string(const EdgesSide& e)
{
	std::string str;
	for (int i = 0; i < 24; i++)
		str += std::to_string(e.cubie(i)) + ' ';
	str.pop_back();
	return str;
}
