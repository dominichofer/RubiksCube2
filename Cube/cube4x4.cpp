#include "cube4x4.h"
#include <sstream>
#include <utility>

const std::array<Cube4x4::Twist, 36> Cube4x4::twists = {
	Twist::L1, Twist::L2, Twist::L3, Twist::l1, Twist::l2, Twist::l3,
	Twist::R1, Twist::R2, Twist::R3, Twist::r1, Twist::r2, Twist::r3,
	Twist::U1, Twist::U2, Twist::U3, Twist::u1, Twist::u2, Twist::u3,
	Twist::D1, Twist::D2, Twist::D3, Twist::d1, Twist::d2, Twist::d3,
	Twist::F1, Twist::F2, Twist::F3, Twist::f1, Twist::f2, Twist::f3,
	Twist::B1, Twist::B2, Twist::B3, Twist::b1, Twist::b2, Twist::b3
};

bool Cube4x4::operator==(const Cube4x4& o) const
{
	return c == o.c && e == o.e && f == o.f;
}

bool Cube4x4::operator!=(const Cube4x4& o) const
{
	return !(*this == o);
}

bool Cube4x4::operator<(const Cube4x4& o) const
{
	if (c != o.c) return c < o.c;
	if (e != o.e) return e < o.e;
	return f < o.f;
}

Cube4x4 Cube4x4::twisted(Twist t) const
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
	}
}

Cube4x4 Cube4x4::twisted(const std::vector<Twist>& twists) const
{
	auto cube = *this;
	for (auto t : twists)
		cube = cube.twisted(t);
	return cube;
}

uint64_t Cube4x4::hash() const
{
	return c.hash() ^ e.hash() ^ f.hash();
}

std::string to_string(Cube4x4::Twist t)
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

std::string to_string(Cube4x4 c)
{
	std::stringstream ss;
	ss << to_string(c.corners()) << to_string(c.edges()) << to_string(c.faces());
	return ss.str();
}
