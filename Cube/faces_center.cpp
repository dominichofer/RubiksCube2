#include "faces_center.h"
#include "byte.h"
#include "Math/math.h"
#include <array>
#include "intrin.h"
#include <sstream>
#include <utility>

const std::array<FacesCenter::Twist, 36> FacesCenter::twists = {
	Twist::L1, Twist::L2, Twist::L3, Twist::l1, Twist::l2, Twist::l3,
	Twist::R1, Twist::R2, Twist::R3, Twist::r1, Twist::r2, Twist::r3,
	Twist::U1, Twist::U2, Twist::U3, Twist::u1, Twist::u2, Twist::u3,
	Twist::D1, Twist::D2, Twist::D3, Twist::d1, Twist::d2, Twist::d3,
	Twist::F1, Twist::F2, Twist::F3, Twist::f1, Twist::f2, Twist::f3,
	Twist::B1, Twist::B2, Twist::B3, Twist::b1, Twist::b2, Twist::b3
};

std::string to_string(FacesCenter::Twist t)
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

FacesCenter::FacesCenter(uint64_t a, uint64_t b, uint64_t c) noexcept : a(a), b(b), c(c) {}

FacesCenter::FacesCenter() noexcept : FacesCenter(
	0, 0, 0, 0,
	1, 1, 1, 1,
	2, 2, 2, 2,
	3, 3, 3, 3,
	4, 4, 4, 4,
	5, 5, 5, 5)
{}

FacesCenter::FacesCenter(
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

bool FacesCenter::operator==(const FacesCenter& o) const
{
	return a == o.a && b == o.b && c == o.c;
}

bool FacesCenter::operator!=(const FacesCenter& o) const
{
	return !(*this == o);
}

bool FacesCenter::operator<(const FacesCenter& o) const
{
	if (a != o.a) return a < o.a;
	if (b != o.b) return b < o.b;
	return c < o.c;
}

int FacesCenter::cubie(int i) const
{
	if (i < 8)
		return extract_epi8(a, i);
	if (i < 16)
		return extract_epi8(b, i - 8);
	return extract_epi8(c, i - 16);
}

bool FacesCenter::is_solved() const
{
	return *this == FacesCenter();
}

const int i0 = 8, i1 = 9, i2 = 10, i3 = 11, i4 = 12, i5 = 13, i6 = 14, i7 = 15;

FacesCenter FacesCenter::L1() const
{
	auto A = byte_shuffle(a, 1, 2, 3, 0, 4, 5, 6, 7);
	return { A, b, c };
}

FacesCenter FacesCenter::L2() const
{
	auto A = byte_shuffle(a, 2, 3, 0, 1, 4, 5, 6, 7);
	return { A, b, c };
}

FacesCenter FacesCenter::L3() const
{
	auto A = byte_shuffle(a, 3, 0, 1, 2, 4, 5, 6, 7);
	return { A, b, c };
}

FacesCenter FacesCenter::l1() const
{
	auto [B, C] = byte_shuffle(
		b, c,
		0, 1, i4, 3, 4, 5, i2, 7,
		i0, i1, 2, i3, 6, i5, i6, i7);
	return { a, B, C };
}

FacesCenter FacesCenter::l2() const
{
	auto [B, C] = byte_shuffle(
		b, c,
		0, 1, 6, 3, 4, 5, 2, 7,
		i0, i1, i4, i3, i2, i5, i6, i7);
	return { a, B, C };
}

FacesCenter FacesCenter::l3() const
{
	auto [B, C] = byte_shuffle(
		b, c,
		0, 1, i2, 3, 4, 5, i4, 7,
		i0, i1, 6, i3, 2, i5, i6, i7);
	return { a, B, C };
}

FacesCenter FacesCenter::R1() const
{
	auto A = byte_shuffle(a, 0, 1, 2, 3, 5, 6, 7, 4);
	return { A, b, c };
}

FacesCenter FacesCenter::R2() const
{
	auto A = byte_shuffle(a, 0, 1, 2, 3, 6, 7, 4, 5);
	return { A, b, c };
}

FacesCenter FacesCenter::R3() const
{
	auto A = byte_shuffle(a, 0, 1, 2, 3, 7, 4, 5, 6);
	return { A, b, c };
}

FacesCenter FacesCenter::r1() const
{
	auto [B, C] = byte_shuffle(
		b, c,
		i0, 1, 2, 3, i6, 5, 6, 7,
		4, i1, i2, i3, i4, i5, 0, i7);
	return { a, B, C };
}

FacesCenter FacesCenter::r2() const
{
	auto [B, C] = byte_shuffle(
		b, c,
		4, 1, 2, 3, 0, 5, 6, 7,
		i6, i1, i2, i3, i4, i5, i0, i7);
	return { a, B, C };
}

FacesCenter FacesCenter::r3() const
{
	auto [B, C] = byte_shuffle(
		b, c,
		i6, 1, 2, 3, i0, 5, 6, 7,
		0, i1, i2, i3, i4, i5, 4, i7);
	return { a, B, C };
}

FacesCenter FacesCenter::U1() const
{
	auto B = byte_shuffle(b, 1, 2, 3, 0, 4, 5, 6, 7);
	return { a, B, c };
}

FacesCenter FacesCenter::U2() const
{
	auto B = byte_shuffle(b, 2, 3, 0, 1, 4, 5, 6, 7);
	return { a, B, c };
}

FacesCenter FacesCenter::U3() const
{
	auto B = byte_shuffle(b, 3, 0, 1, 2, 4, 5, 6, 7);
	return { a, B, c };
}

FacesCenter FacesCenter::u1() const
{
	auto [A, C] = byte_shuffle(
		a, c,
		0, i1, 2, 3, 4, i5, 6, 7,
		i0, 5, i2, i3, i4, 1, i6, i7);
	return { A, b, C };
}

FacesCenter FacesCenter::u2() const
{
	auto [A, C] = byte_shuffle(
		a, c,
		0, 5, 2, 3, 4, 1, 6, 7,
		i0, i5, i2, i3, i4, i1, i6, i7);
	return { A, b, C };
}

FacesCenter FacesCenter::u3() const
{
	auto [A, C] = byte_shuffle(
		a, c,
		0, i5, 2, 3, 4, i1, 6, 7,
		i0, 1, i2, i3, i4, 5, i6, i7);
	return { A, b, C };
}

FacesCenter FacesCenter::D1() const
{
	auto B = byte_shuffle(b, 0, 1, 2, 3, 5, 6, 7, 4);
	return { a, B, c };
}

FacesCenter FacesCenter::D2() const
{
	auto B = byte_shuffle(b, 0, 1, 2, 3, 6, 7, 4, 5);
	return { a, B, c };
}

FacesCenter FacesCenter::D3() const
{
	auto B = byte_shuffle(b, 0, 1, 2, 3, 7, 4, 5, 6);
	return { a, B, c };
}

FacesCenter FacesCenter::d1() const
{
	auto [A, C] = byte_shuffle(
		a, c,
		0, 1, 2, i7, 4, 5, 6, i3,
		i0, i1, i2, 3, i4, i5, i6, 7);
	return { A, b, C };
}

FacesCenter FacesCenter::d2() const
{
	auto [A, C] = byte_shuffle(
		a, c,
		0, 1, 2, 7, 4, 5, 6, 3,
		i0, i1, i2, i7, i4, i5, i6, i3);
	return { A, b, C };
}

FacesCenter FacesCenter::d3() const
{
	auto [A, C] = byte_shuffle(
		a, c,
		0, 1, 2, i3, 4, 5, 6, i7,
		i0, i1, i2, 7, i4, i5, i6, 3);
	return { A, b, C };
}

FacesCenter FacesCenter::F1() const
{
	auto C = byte_shuffle(c, 1, 2, 3, 0, 4, 5, 6, 7);
	return { a, b, C };
}

FacesCenter FacesCenter::F2() const
{
	auto C = byte_shuffle(c, 2, 3, 0, 1, 4, 5, 6, 7);
	return { a, b, C };
}

FacesCenter FacesCenter::F3() const
{
	auto C = byte_shuffle(c, 3, 0, 1, 2, 4, 5, 6, 7);
	return { a, b, C };
}

FacesCenter FacesCenter::f1() const
{
	auto [A, B] = byte_shuffle(
		a, b,
		i5, 1, 2, 3, 4, 5, i3, 7,
		i0, i1, i2, 0, i4, 6, i6, i7);
	return { A, B, c };
}

FacesCenter FacesCenter::f2() const
{
	auto [A, B] = byte_shuffle(
		a, b,
		6, 1, 2, 3, 4, 5, 0, 7,
		i0, i1, i2, i5, i4, i3, i6, i7);
	return { A, B, c };
}

FacesCenter FacesCenter::f3() const
{
	auto [A, B] = byte_shuffle(
		a, b,
		i3, 1, 2, 3, 4, 5, i5, 7,
		i0, i1, i2, 6, i4, 0, i6, i7);
	return { A, B, c };
}

FacesCenter FacesCenter::B1() const
{
	auto C = byte_shuffle(c, 0, 1, 2, 3, 5, 6, 7, 4);
	return { a, b, C };
}

FacesCenter FacesCenter::B2() const
{
	auto C = byte_shuffle(c, 0, 1, 2, 3, 6, 7, 4, 5);
	return { a, b, C };
}

FacesCenter FacesCenter::B3() const
{
	auto C = byte_shuffle(c, 0, 1, 2, 3, 7, 4, 5, 6);
	return { a, b, C };
}

FacesCenter FacesCenter::b1() const
{
	auto [A, B] = byte_shuffle(
		a, b,
		0, 1, i1, 3, i7, 5, 6, 7,
		i0, 4, i2, i3, i4, i5, i6, 2);
	return { A, B, c };
}

FacesCenter FacesCenter::b2() const
{
	auto [A, B] = byte_shuffle(
		a, b,
		0, 1, 4, 3, 2, 5, 6, 7,
		i0, i7, i2, i3, i4, i5, i6, i1);
	return { A, B, c };
}

FacesCenter FacesCenter::b3() const
{
	auto [A, B] = byte_shuffle(
		a, b,
		0, 1, i7, 3, i1, 5, 6, 7,
		i0, 2, i2, i3, i4, i5, i6, 4);
	return { A, B, c };
}

FacesCenter FacesCenter::twisted(Twist t) const
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

FacesCenter FacesCenter::twisted(const std::vector<Twist>& ts) const
{
	auto e = *this;
	for (auto t : ts)
		e = e.twisted(t);
	return e;
}

uint64_t FacesCenter::prm_index() const
{
	// TODO: Implement this function!
	return 0;
}

uint64_t FacesCenter::index() const
{
	return prm_index();
}

uint64_t FacesCenter::hash() const
{
	std::hash<uint64_t> h;
	uint64_t ret = h(a) + 0x9E3779B9;
	ret ^= h(b) + 0x9E3779B9 + (ret << 6) + (ret >> 2);
	ret ^= h(c) + 0x9E3779B9 + (ret << 6) + (ret >> 2);
	return ret;
}

std::string to_string(FacesCenter f)
{
	std::stringstream ss;
	ss << "FacesCenter(";
	for (int i = 0; i < 24; ++i)
		ss << (i ? ", " : "") << int(f.cubie(i));
	ss << ")";
	return ss.str();
}
