#include "edges_side.h"
#include "byte.h"
#include "Math/math.h"
#include <array>
#include <sstream>
#include <utility>

const std::vector<EdgesSide::Twist> EdgesSide::twists = {
	Twist::L1, Twist::L2, Twist::L3, Twist::l1, Twist::l2, Twist::l3,
	Twist::R1, Twist::R2, Twist::R3, Twist::r1, Twist::r2, Twist::r3,
	Twist::U1, Twist::U2, Twist::U3, Twist::u1, Twist::u2, Twist::u3,
	Twist::D1, Twist::D2, Twist::D3, Twist::d1, Twist::d2, Twist::d3,
	Twist::F1, Twist::F2, Twist::F3, Twist::f1, Twist::f2, Twist::f3,
	Twist::B1, Twist::B2, Twist::B3, Twist::b1, Twist::b2, Twist::b3
};

std::string to_string(EdgesSide::Twist t)
{
    return std::array{
		"L1", "L2", "L3", "l1", "l2", "l3",
		"R1", "R2", "R3", "r1", "r2", "r3",
		"U1", "U2", "U3", "u1", "u2", "u3",
		"D1", "D2", "D3", "d1", "d2", "d3",
		"F1", "F2", "F3", "f1", "f2", "f3",
		"B1", "B2", "B3", "b1", "b2", "b3"
	} [std::to_underlying(t)];
}

EdgesSide::EdgesSide(uint64_t a, uint64_t b, uint64_t c) noexcept : a(a), b(b), c(c) {}

EdgesSide::EdgesSide() noexcept : EdgesSide(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23) {}

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

bool EdgesSide::operator==(const EdgesSide& o) const
{
	return a == o.a && b == o.b && c == o.c;
}

bool EdgesSide::operator!=(const EdgesSide& o) const
{
	return !(*this == o);
}

bool EdgesSide::operator<(const EdgesSide& o) const
{
	if (a != o.a) return a < o.a;
	if (b != o.b) return b < o.b;
	return c < o.c;
}

int EdgesSide::cubie(int i) const
{
	if (i < 8)
		return extract_epi8(a, i);
	if (i < 16)
		return extract_epi8(b, i - 8);
	return extract_epi8(c, i - 16);
}

bool EdgesSide::is_solved() const
{
	return *this == EdgesSide();
}

const int i0 = 8, i1 = 9, i2 = 10, i3 = 11, i4 = 12, i5 = 13, i6 = 14, i7 = 15;

EdgesSide EdgesSide::L1() const
{
	auto [B, C] = byte_shuffle(
		b, c,
		i1, i0, 2, 3, 4, 5, i3, i2,
		6, 7, 0, 1, i4, i5, i6, i7);
	return { a, B, C };
}

EdgesSide EdgesSide::L2() const
{
	auto [B, C] = byte_shuffle(
		b, c,
		7, 6, 2, 3, 4, 5, 1, 0,
		i3, i2, i1, i0, i4, i5, i6, i7);
	return { a, B, C };
}

EdgesSide EdgesSide::L3() const
{
	auto [B, C] = byte_shuffle(
		b, c,
		i2, i3, 2, 3, 4, 5, i0, i1,
		1, 0, 7, 6, i4, i5, i6, i7);
	return { a, B, C };
}

EdgesSide EdgesSide::l1() const
{
	auto A = byte_shuffle(a, 2, 1, 4, 3, 6, 5, 0, 7);
	return { A, b, c };
}

EdgesSide EdgesSide::l2() const
{
	auto A = byte_shuffle(a, 4, 1, 6, 3, 0, 5, 2, 7);
	return { A, b, c };
}

EdgesSide EdgesSide::l3() const
{
	auto A = byte_shuffle(a, 6, 1, 0, 3, 2, 5, 4, 7);
	return { A, b, c };
}

EdgesSide EdgesSide::R1() const
{
	auto [B, C] = byte_shuffle(
		b, c,
		0, 1, i4, i5, i6, i7, 6, 7,
		i0, i1, i2, i3, 5, 4, 3, 2);
	return { a, B, C };
}

EdgesSide EdgesSide::R2() const
{
	auto [B, C] = byte_shuffle(
		b, c,
		0, 1, 5, 4, 3, 2, 6, 7,
		i0, i1, i2, i3, i7, i6, i5, i4);
	return { a, B, C };
}

EdgesSide EdgesSide::R3() const
{
	auto [B, C] = byte_shuffle(
		b, c,
		0, 1, i7, i6, i5, i4, 6, 7,
		i0, i1, i2, i3, 2, 3, 4, 5);
	return { a, B, C };
}

EdgesSide EdgesSide::r1() const
{
	auto A = byte_shuffle(a, 0, 7, 2, 1, 4, 3, 6, 5);
	return { A, b, c };
}

EdgesSide EdgesSide::r2() const
{
	auto A = byte_shuffle(a, 0, 5, 2, 7, 4, 1, 6, 3);
	return { A, b, c };
}

EdgesSide EdgesSide::r3() const
{
	auto A = byte_shuffle(a, 0, 3, 2, 5, 4, 7, 6, 1);
	return { A, b, c };
}

EdgesSide EdgesSide::U1() const
{
	auto [A, C] = byte_shuffle(
		a, c,
		i6, i7, i0, i1, 4, 5, 6, 7,
		1, 0, i2, i3, i4, i5, 3, 2);
	return { A, b, C };
}

EdgesSide EdgesSide::U2() const
{
	auto [A, C] = byte_shuffle(
		a, c,
		3, 2, 1, 0, 4, 5, 6, 7,
		i7, i6, i2, i3, i4, i5, i1, i0);
	return { A, b, C };
}

EdgesSide EdgesSide::U3() const
{
	auto [A, C] = byte_shuffle(
		a, c,
		i1, i0, i7, i6, 4, 5, 6, 7,
		2, 3, i2, i3, i4, i5, 0, 1);
	return { A, b, C };
}

EdgesSide EdgesSide::u1() const
{
	auto B = byte_shuffle(b, 2, 1, 4, 3, 6, 5, 0, 7);
	return { a, B, c };
}

EdgesSide EdgesSide::u2() const
{
	auto B = byte_shuffle(b, 4, 1, 6, 3, 0, 5, 2, 7);
	return { a, B, c };
}

EdgesSide EdgesSide::u3() const
{
	auto B = byte_shuffle(b, 6, 1, 0, 3, 2, 5, 4, 7);
	return { a, B, c };
}

EdgesSide EdgesSide::D1() const
{
	auto [A, C] = byte_shuffle(
		a, c,
		0, 1, 2, 3, i5, i4, i3, i2,
		i0, i1, 4, 5, 6, 7, i6, i7);
	return { A, b, C };
}

EdgesSide EdgesSide::D2() const
{
	auto [A, C] = byte_shuffle(
		a, c,
		0, 1, 2, 3, 7, 6, 5, 4,
		i0, i1, i5, i4, i3, i2, i6, i7);
	return { A, b, C };
}

EdgesSide EdgesSide::D3() const
{
	auto [A, C] = byte_shuffle(
		a, c,
		0, 1, 2, 3, i2, i3, i4, i5,
		i0, i1, 7, 6, 5, 4, i6, i7);
	return { A, b, C };
}

EdgesSide EdgesSide::d1() const
{
	auto B = byte_shuffle(b, 0, 7, 2, 1, 4, 3, 6, 5);
	return { a, B, c };
}

EdgesSide EdgesSide::d2() const
{
	auto B = byte_shuffle(b, 0, 5, 2, 7, 4, 1, 6, 3);
	return { a, B, c };
}

EdgesSide EdgesSide::d3() const
{
	auto B = byte_shuffle(b, 0, 3, 2, 5, 4, 7, 6, 1);
	return { a, B, c };
}

EdgesSide EdgesSide::F1() const
{
	auto [A, B] = byte_shuffle(
		a, b,
		i1, i0, 2, 3, 4, 5, i3, i2,
		6, 7, 0, 1, i4, i5, i6, i7);
	return { A, B, c };
}

EdgesSide EdgesSide::F2() const
{
	auto [A, B] = byte_shuffle(
		a, b,
		7, 6, 2, 3, 4, 5, 1, 0,
		i3, i2, i1, i0, i4, i5, i6, i7);
	return { A, B, c };
}

EdgesSide EdgesSide::F3() const
{
	auto [A, B] = byte_shuffle(
		a, b,
		i2, i3, 2, 3, 4, 5, i0, i1,
		1, 0, 7, 6, i4, i5, i6, i7);
	return { A, B, c };
}

EdgesSide EdgesSide::f1() const
{
	auto C = byte_shuffle(c, 2, 1, 4, 3, 6, 5, 0, 7);
	return { a, b, C };
}

EdgesSide EdgesSide::f2() const
{
	auto C = byte_shuffle(c, 4, 1, 6, 3, 0, 5, 2, 7);
	return { a, b, C };
}

EdgesSide EdgesSide::f3() const
{
	auto C = byte_shuffle(c, 6, 1, 0, 3, 2, 5, 4, 7);
	return { a, b, C };
}

EdgesSide EdgesSide::B1() const
{
	auto [A, B] = byte_shuffle(
		a, b,
		0, 1, i4, i5, i6, i7, 6, 7,
		i0, i1, i2, i3, 5, 4, 3, 2);
	return { A, B, c };
}

EdgesSide EdgesSide::B2() const
{
	auto [A, B] = byte_shuffle(
		a, b,
		0, 1, 5, 4, 3, 2, 6, 7,
		i0, i1, i2, i3, i7, i6, i5, i4);
	return { A, B, c };
}

EdgesSide EdgesSide::B3() const
{
	auto [A, B] = byte_shuffle(
		a, b,
		0, 1, i7, i6, i5, i4, 6, 7,
		i0, i1, i2, i3, 2, 3, 4, 5);
	return { A, B, c };
}

EdgesSide EdgesSide::b1() const
{
	auto C = byte_shuffle(c, 0, 7, 2, 1, 4, 3, 6, 5);
	return { a, b, C };
}

EdgesSide EdgesSide::b2() const
{
	auto C = byte_shuffle(c, 0, 5, 2, 7, 4, 1, 6, 3);
	return { a, b, C };
}

EdgesSide EdgesSide::b3() const
{
	auto C = byte_shuffle(c, 0, 3, 2, 5, 4, 7, 6, 1);
	return { a, b, C };
}

EdgesSide EdgesSide::twisted(Twist t) const
{
	switch (t)
	{
	case Twist::L1: return L1();
	case Twist::L2: return L2();
	case Twist::L3: return L3();
	case Twist::l1: return l1();
	case Twist::l2: return l2();
	case Twist::l3: return l3();
	case Twist::R1: return R1();
	case Twist::R2: return R2();
	case Twist::R3: return R3();
	case Twist::r1: return r1();
	case Twist::r2: return r2();
	case Twist::r3: return r3();
	case Twist::U1: return U1();
	case Twist::U2: return U2();
	case Twist::U3: return U3();
	case Twist::u1: return u1();
	case Twist::u2: return u2();
	case Twist::u3: return u3();
	case Twist::D1: return D1();
	case Twist::D2: return D2();
	case Twist::D3: return D3();
	case Twist::d1: return d1();
	case Twist::d2: return d2();
	case Twist::d3: return d3();
	case Twist::F1: return F1();
	case Twist::F2: return F2();
	case Twist::F3: return F3();
	case Twist::f1: return f1();
	case Twist::f2: return f2();
	case Twist::f3: return f3();
	case Twist::B1: return B1();
	case Twist::B2: return B2();
	case Twist::B3: return B3();
	case Twist::b1: return b1();
	case Twist::b2: return b2();
	case Twist::b3: return b3();
	case Twist::None: return *this;
	default: throw std::invalid_argument("Invalid twist");
	}
}

EdgesSide EdgesSide::twisted(const std::vector<Twist>& twists) const
{
	auto e = *this;
	for (auto t : twists)
		e = e.twisted(t);
	return e;
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
	std::hash<uint64_t> h;
	uint64_t ret = h(a) + 0x9E3779B9;
	ret ^= h(b) + 0x9E3779B9 + (ret << 6) + (ret >> 2);
	ret ^= h(c) + 0x9E3779B9 + (ret << 6) + (ret >> 2);
	return ret;
}

std::string to_string(EdgesSide e)
{
	std::ostringstream oss;
	oss << "EdgesSide(";
	for (int i = 0; i < 24; ++i)
		oss << e.cubie(i) << (i == 23 ? ")" : ",");
	return oss.str();
}
