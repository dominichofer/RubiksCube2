#include "twist.h"
#include <stdexcept>

std::string to_string(Twist twist)
{
	switch (twist)
	{
	case Twist::L1: return "L1";
	case Twist::L2: return "L2";
	case Twist::L3: return "L3";
	case Twist::l1: return "l1";
	case Twist::l2: return "l2";
	case Twist::l3: return "l3";
	case Twist::R1: return "R1";
	case Twist::R2: return "R2";
	case Twist::R3: return "R3";
	case Twist::r1: return "r1";
	case Twist::r2: return "r2";
	case Twist::r3: return "r3";
	case Twist::U1: return "U1";
	case Twist::U2: return "U2";
	case Twist::U3: return "U3";
	case Twist::u1: return "u1";
	case Twist::u2: return "u2";
	case Twist::u3: return "u3";
	case Twist::D1: return "D1";
	case Twist::D2: return "D2";
	case Twist::D3: return "D3";
	case Twist::d1: return "d1";
	case Twist::d2: return "d2";
	case Twist::d3: return "d3";
	case Twist::F1: return "F1";
	case Twist::F2: return "F2";
	case Twist::F3: return "F3";
	case Twist::f1: return "f1";
	case Twist::f2: return "f2";
	case Twist::f3: return "f3";
	case Twist::B1: return "B1";
	case Twist::B2: return "B2";
	case Twist::B3: return "B3";
	case Twist::b1: return "b1";
	case Twist::b2: return "b2";
	case Twist::b3: return "b3";
	case Twist::None: return "None";
	default: throw std::invalid_argument("Invalid twist");
	}
}

Twist twist_from_string(std::string_view s)
{
	static const std::vector<Twist> all_twists = {
		Twist::L1, Twist::L2, Twist::L3, Twist::l1, Twist::l2, Twist::l3,
		Twist::R1, Twist::R2, Twist::R3, Twist::r1, Twist::r2, Twist::r3,
		Twist::U1, Twist::U2, Twist::U3, Twist::u1, Twist::u2, Twist::u3,
		Twist::D1, Twist::D2, Twist::D3, Twist::d1, Twist::d2, Twist::d3,
		Twist::F1, Twist::F2, Twist::F3, Twist::f1, Twist::f2, Twist::f3,
		Twist::B1, Twist::B2, Twist::B3, Twist::b1, Twist::b2, Twist::b3,
	};
	for (Twist t : all_twists)
		if (to_string(t) == s)
			return t;
	throw std::invalid_argument("Invalid twist string");
}

Twist inversed(Twist twist)
{
	switch (twist)
	{
	case Twist::L1: return Twist::L3;
	case Twist::L2: return Twist::L2;
	case Twist::L3: return Twist::L1;
	case Twist::l1: return Twist::l3;
	case Twist::l2: return Twist::l2;
	case Twist::l3: return Twist::l1;
	case Twist::R1: return Twist::R3;
	case Twist::R2: return Twist::R2;
	case Twist::R3: return Twist::R1;
	case Twist::r1: return Twist::r3;
	case Twist::r2: return Twist::r2;
	case Twist::r3: return Twist::r1;
	case Twist::U1: return Twist::U3;
	case Twist::U2: return Twist::U2;
	case Twist::U3: return Twist::U1;
	case Twist::u1: return Twist::u3;
	case Twist::u2: return Twist::u2;
	case Twist::u3: return Twist::u1;
	case Twist::D1: return Twist::D3;
	case Twist::D2: return Twist::D2;
	case Twist::D3: return Twist::D1;
	case Twist::d1: return Twist::d3;
	case Twist::d2: return Twist::d2;
	case Twist::d3: return Twist::d1;
	case Twist::F1: return Twist::F3;
	case Twist::F2: return Twist::F2;
	case Twist::F3: return Twist::F1;
	case Twist::f1: return Twist::f3;
	case Twist::f2: return Twist::f2;
	case Twist::f3: return Twist::f1;
	case Twist::B1: return Twist::B3;
	case Twist::B2: return Twist::B2;
	case Twist::B3: return Twist::B1;
	case Twist::b1: return Twist::b3;
	case Twist::b2: return Twist::b2;
	case Twist::b3: return Twist::b1;
	case Twist::None: return Twist::None;
	default: throw std::invalid_argument("Invalid twist");
	}
}

std::vector<Twist> inversed(const std::vector<Twist>& twists)
{
	std::vector<Twist> r;
	r.reserve(twists.size());
	for (auto it = twists.rbegin(); it != twists.rend(); ++it)
		r.push_back(inversed(*it));
	return r;
}

bool same_plane(Twist a, Twist b)
{
	return std::to_underlying(a) / 3 == std::to_underlying(b) / 3;
}
