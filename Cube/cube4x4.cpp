#include "cube4x4.h"
#include "Math/math.h"

const Twists Cube4x4::twists = {
	Twist::L1, Twist::L2, Twist::L3, Twist::l1, Twist::l2, Twist::l3,
	Twist::R1, Twist::R2, Twist::R3, Twist::r1, Twist::r2, Twist::r3,
	Twist::U1, Twist::U2, Twist::U3, Twist::u1, Twist::u2, Twist::u3,
	Twist::D1, Twist::D2, Twist::D3, Twist::d1, Twist::d2, Twist::d3,
	Twist::F1, Twist::F2, Twist::F3, Twist::f1, Twist::f2, Twist::f3,
	Twist::B1, Twist::B2, Twist::B3, Twist::b1, Twist::b2, Twist::b3
};

Cube4x4 Cube4x4::solved()
{
	return Cube4x4{ Corners::solved(), EdgesSide::solved(), FacesSide::solved() };
}

Cube4x4 Cube4x4::impossible()
{
	return Cube4x4{ Corners::impossible(), EdgesSide::impossible(), FacesSide::impossible() };
}

Cube4x4 Cube4x4::twisted(Twist t) const
{
	return Cube4x4{ c.twisted(t), e.twisted(t), f.twisted(t) };
}

uint64_t Cube4x4::hash() const
{
	return ::hash(c, e, f);
}

std::string to_string(const Cube4x4& c)
{
	return "Corners: " + to_string(c.corners())
		+ " Edges: " + to_string(c.edges())
		+ " Faces: " + to_string(c.faces());
}
