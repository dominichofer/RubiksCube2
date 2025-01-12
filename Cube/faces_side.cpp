#include "faces_side.h"
#include "byte.h"
#include "Math/math.h"
#include <array>
#include <intrin.h>
#include <sstream>

const std::array<FacesSide::Twist, 36> FacesSide::twists = {
	Twist::L1, Twist::L2, Twist::L3, Twist::l1, Twist::l2, Twist::l3,
	Twist::R1, Twist::R2, Twist::R3, Twist::r1, Twist::r2, Twist::r3,
	Twist::U1, Twist::U2, Twist::U3, Twist::u1, Twist::u2, Twist::u3,
	Twist::D1, Twist::D2, Twist::D3, Twist::d1, Twist::d2, Twist::d3,
	Twist::F1, Twist::F2, Twist::F3, Twist::f1, Twist::f2, Twist::f3,
	Twist::B1, Twist::B2, Twist::B3, Twist::b1, Twist::b2, Twist::b3
};

std::string to_string(FacesSide::Twist t)
{
	return std::array{
		"L1", "L2", "L3", "l1", "l2", "l3",
		"R1", "R2", "R3", "r1", "r2", "r3",
		"U1", "U2", "U3", "u1", "u2", "u3",
		"D1", "D2", "D3", "d1", "d2", "d3",
		"F1", "F2", "F3", "f1", "f2", "f3",
		"B1", "B2", "B3", "b1", "b2", "b3"
	} [std::to_underlying(t)] ;
}

FacesSide::FacesSide(uint64_t a, uint64_t b, uint64_t c) noexcept : a(a), b(b), c(c) {}

FacesSide::FacesSide() noexcept : FacesSide(
	0, 0, 0, 0,
	1, 1, 1, 1,
	2, 2, 2, 2,
	3, 3, 3, 3,
	4, 4, 4, 4,
	5, 5, 5, 5)
{}

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

bool FacesSide::operator==(const FacesSide& o) const
{
	return a == o.a && b == o.b && c == o.c;
}

bool FacesSide::operator!=(const FacesSide& o) const
{
	return !(*this == o);
}

bool FacesSide::operator<(const FacesSide& o) const
{
	if (a != o.a) return a < o.a;
	if (b != o.b) return b < o.b;
	return c < o.c;
}

int FacesSide::cubie(int i) const
{
	if (i < 8)
		return extract_epi8(a, i);
	if (i < 16)
		return extract_epi8(b, i - 8);
	return extract_epi8(c, i - 16);
}

bool FacesSide::is_solved() const
{
	return *this == FacesSide();
}

const int i0 = 8, i1 = 9, i2 = 10, i3 = 11, i4 = 12, i5 = 13, i6 = 14, i7 = 15;

FacesSide FacesSide::L1() const
{
	auto A = byte_shuffle(a, 2, 0, 3, 1, 4, 5, 6, 7);
	return { A, b, c };
}

FacesSide FacesSide::L2() const
{
	auto A = byte_shuffle(a, 3, 2, 1, 0, 4, 5, 6, 7);
	return { A, b, c };
}

FacesSide FacesSide::L3() const
{
	auto A = byte_shuffle(a, 1, 3, 0, 2, 4, 5, 6, 7);
	return { A, b, c };
}

FacesSide FacesSide::l1() const
{
	auto [B, C] = byte_shuffle(
		b, c,
		i7, 1, i5, 3, i0, 5, i2, 7,
		0, i1, 2, i3, i4, 6, i6, 4);
	return { a, B, C };
}

FacesSide FacesSide::l2() const
{
	auto [B, C] = byte_shuffle(
		b, c,
		4, 1, 6, 3, 0, 5, 2, 7,
		i7, i1, i5, i3, i4, i2, i6, i0);
	return { a, B, C };
}

FacesSide FacesSide::R1() const
{
	auto A = byte_shuffle(a, 0, 1, 2, 3, 6, 4, 7, 5);
	return { A, b, c };
}

FacesSide FacesSide::R2() const
{
	auto A = byte_shuffle(a, 0, 1, 2, 3, 7, 6, 5, 4);
	return { A, b, c };
}

FacesSide FacesSide::R3() const
{
	auto A = byte_shuffle(a, 0, 1, 2, 3, 5, 7, 4, 6);
	return { A, b, c };
}

FacesSide FacesSide::l3() const
{
	auto [B, C] = byte_shuffle(
		b, c,
		i0, 1, i2, 3, i7, 5, i5, 7,
		4, i1, 6, i3, i4, 2, i6, 0);
	return { a, B, C };
}

FacesSide FacesSide::r1() const
{
	auto [B, C] = byte_shuffle(
		b, c,
		0, i1, 2, i3, 4, i6, 6, i4,
		i0, 5, i2, 7, 3, i5, 1, i7);
	return { a, B, C };
}

FacesSide FacesSide::r2() const
{
	auto [B, C] = byte_shuffle(
		b, c,
		0, 5, 2, 7, 4, 1, 6, 3,
		i0, i6, i2, i4, i3, i5, i1, i7);
	return { a, B, C };
}

FacesSide FacesSide::r3() const
{
	auto [B, C] = byte_shuffle(
		b, c,
		0, i6, 2, i4, 4, i1, 6, i3,
		i0, 1, i2, 3, 7, i5, 5, i7);
	return { a, B, C };
}

FacesSide FacesSide::U1() const
{
	auto B = byte_shuffle(b, 2, 0, 3, 1, 4, 5, 6, 7);
	return { a, B, c };
}

FacesSide FacesSide::U2() const
{
	auto B = byte_shuffle(b, 3, 2, 1, 0, 4, 5, 6, 7);
	return { a, B, c };
}

FacesSide FacesSide::U3() const
{
	auto B = byte_shuffle(b, 1, 3, 0, 2, 4, 5, 6, 7);
	return { a, B, c };
}

FacesSide FacesSide::u1() const
{
	auto [A, C] = byte_shuffle(
		a, c,
		i0, i1, 2, 3, i4, i5, 6, 7,
		4, 5, i2, i3, 0, 1, i6, i7);
	return { A, b, C };
}

FacesSide FacesSide::u2() const
{
	auto [A, C] = byte_shuffle(
		a, c,
		4, 5, 2, 3, 0, 1, 6, 7,
		i4, i5, i2, i3, i0, i1, i6, i7);
	return { A, b, C };
}

FacesSide FacesSide::u3() const
{
	auto [A, C] = byte_shuffle(
		a, c,
		i4, i5, 2, 3, i0, i1, 6, 7,
		0, 1, i2, i3, 4, 5, i6, i7);
	return { A, b, C };
}

FacesSide FacesSide::D1() const
{
	auto B = byte_shuffle(b, 0, 1, 2, 3, 6, 4, 7, 5);
	return { a, B, c };
}

FacesSide FacesSide::D2() const
{
	auto B = byte_shuffle(b, 0, 1, 2, 3, 7, 6, 5, 4);
	return { a, B, c };
}

FacesSide FacesSide::D3() const
{
	auto B = byte_shuffle(b, 0, 1, 2, 3, 5, 7, 4, 6);
	return { a, B, c };
}

FacesSide FacesSide::d1() const
{
	auto [A, C] = byte_shuffle(
		a, c,
		0, 1, i6, i7, 4, 5, i2, i3,
		i0, i1, 2, 3, i4, i5, 6, 7);
	return { A, b, C };
}

FacesSide FacesSide::d2() const
{
	auto [A, C] = byte_shuffle(
		a, c,
		0, 1, 6, 7, 4, 5, 2, 3,
		i0, i1, i6, i7, i4, i5, i2, i3);
	return { A, b, C };
}

FacesSide FacesSide::d3() const
{
	auto [A, C] = byte_shuffle(
		a, c,
		0, 1, i2, i3, 4, 5, i6, i7,
		i0, i1, 6, 7, i4, i5, 2, 3);
	return { A, b, C };
}

FacesSide FacesSide::F1() const
{
	auto C = byte_shuffle(c, 2, 0, 3, 1, 4, 5, 6, 7);
	return { a, b, C };
}

FacesSide FacesSide::F2() const
{
	auto C = byte_shuffle(c, 3, 2, 1, 0, 4, 5, 6, 7);
	return { a, b, C };
}

FacesSide FacesSide::F3() const
{
	auto C = byte_shuffle(c, 1, 3, 0, 2, 4, 5, 6, 7);
	return { a, b, C };
}

FacesSide FacesSide::f1() const
{
	auto [A, B] = byte_shuffle(
		a, b,
		0, i4, 2, i5, i2, 5, i3, 7,
		i0, i1, 3, 1, 6, 4, i6, i7);
	return { A, B, c };
}

FacesSide FacesSide::f2() const
{
	auto [A, B] = byte_shuffle(
		a, b,
		0, 6, 2, 4, 3, 5, 1, 7,
		i0, i1, i5, i4, i3, i2, i6, i7);
	return { A, B, c };
}

FacesSide FacesSide::f3() const
{
	auto [A, B] = byte_shuffle(
		a, b,
		0, i3, 2, i2, i5, 5, i4, 7,
		i0, i1, 4, 6, 1, 3, i6, i7);
	return { A, B, c };
}

FacesSide FacesSide::B1() const
{
	auto C = byte_shuffle(c, 0, 1, 2, 3, 6, 4, 7, 5);
	return { a, b, C };
}

FacesSide FacesSide::B2() const
{
	auto C = byte_shuffle(c, 0, 1, 2, 3, 7, 6, 5, 4);
	return { a, b, C };
}

FacesSide FacesSide::B3() const
{
	auto C = byte_shuffle(c, 0, 1, 2, 3, 5, 7, 4, 6);
	return { a, b, C };
}

FacesSide FacesSide::b1() const
{
	auto [A, B] = byte_shuffle(
		a, b,
		i1, 1, i0, 3, 4, i7, 6, i6,
		5, 7, i2, i3, i4, i5, 0, 2);
	return { A, B, c };
}

FacesSide FacesSide::b2() const
{
	auto [A, B] = byte_shuffle(
		a, b,
		7, 1, 5, 3, 4, 2, 6, 0,
		i7, i6, i2, i3, i4, i5, i1, i0);
	return { A, B, c };
}

FacesSide FacesSide::b3() const
{
	auto [A, B] = byte_shuffle(
		a, b,
		i6, 1, i7, 3, 4, i0, 6, i1,
		2, 0, i2, i3, i4, i5, 7, 5);
	return { A, B, c };
}

FacesSide FacesSide::twisted(Twist t) const
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
	default: return *this;
	}
}

FacesSide FacesSide::twisted(const std::vector<Twist>& twists) const
{
	auto result = *this;
	for (auto t : twists)
		result = result.twisted(t);
	return result;
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
	std::hash<uint64_t> h;
	uint64_t ret = h(a) + 0x9E3779B9;
	ret ^= h(b) + 0x9E3779B9 + (ret << 6) + (ret >> 2);
	ret ^= h(c) + 0x9E3779B9 + (ret << 6) + (ret >> 2);
	return ret;
}

std::string to_string(FacesSide f)
{
	std::stringstream ss;
	ss << "FacesSide(";
	for (int i = 0; i < 24; ++i)
		ss << (i ? ", " : "") << int(f.cubie(i));
	ss << ")";
	return ss.str();
}
