#include "cube3x3.h"
#include "twist.h"
#include "Math/math.h"

const std::vector<Twist> Cube3x3::twists = {
	Twist::L1, Twist::L2, Twist::L3,
	Twist::R1, Twist::R2, Twist::R3,
	Twist::U1, Twist::U2, Twist::U3,
	Twist::D1, Twist::D2, Twist::D3,
	Twist::F1, Twist::F2, Twist::F3,
	Twist::B1, Twist::B2, Twist::B3
};

Cube3x3 Cube3x3::solved()
{
	return Cube3x3{ Corners::solved(), EdgesCenter::solved() };
}

Cube3x3 Cube3x3::impossible()
{
	return Cube3x3{ Corners::impossible(), EdgesCenter::impossible() };
}

Cube3x3 Cube3x3::superflip()
{
	// From https://en.wikipedia.org/wiki/Superflip
	return Cube3x3::solved().twisted(twists_from_string("U1 R2 F1 B1 R1 B2 R1 U2 L1 B2 R1 U3 D3 R2 F1 R3 L1 B2 U2 F2"));
}

Cube3x3 Cube3x3::twisted(Twist t) const
{
	return Cube3x3{ c.twisted(t), e.twisted(t) };
}

uint64_t Cube3x3::hash() const
{
	return ::hash(c, e);
}

bool same_permutation(const Cube3x3& a, const Cube3x3& b)
{
	return same_permutation(a.corners(), b.corners())
		&& same_permutation(a.edges(), b.edges());
}

bool same_orientation(const Cube3x3& a, const Cube3x3& b)
{
	return same_orientation(a.corners(), b.corners())
		&& same_orientation(a.edges(), b.edges());
}

std::string to_string(const Cube3x3& c)
{
	return "Corners: " + to_string(c.corners())
		 + " Edges: " + to_string(c.edges());
}
