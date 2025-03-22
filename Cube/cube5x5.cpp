#include "cube5x5.h"

const std::vector<Twist> Cube5x5::twists = {
	Twist::L1, Twist::L2, Twist::L3, Twist::l1, Twist::l2, Twist::l3,
	Twist::R1, Twist::R2, Twist::R3, Twist::r1, Twist::r2, Twist::r3,
	Twist::U1, Twist::U2, Twist::U3, Twist::u1, Twist::u2, Twist::u3,
	Twist::D1, Twist::D2, Twist::D3, Twist::d1, Twist::d2, Twist::d3,
	Twist::F1, Twist::F2, Twist::F3, Twist::f1, Twist::f2, Twist::f3,
	Twist::B1, Twist::B2, Twist::B3, Twist::b1, Twist::b2, Twist::b3
};

Cube5x5 Cube5x5::solved()
{
	return Cube5x5{
		Corners::solved(),
		EdgesCenter::solved(),
		EdgesSide::solved(),
		FacesCenter::solved(),
		FacesSide::solved()
	};
}

Cube5x5 Cube5x5::impossible()
{
	return Cube5x5{
		Corners::impossible(),
		EdgesCenter::impossible(),
		EdgesSide::impossible(),
		FacesCenter::impossible(),
		FacesSide::impossible()
	};
}

Cube5x5 Cube5x5::twisted(Twist t) const
{
	return Cube5x5{
		c.twisted(t),
		ec.twisted(t),
		es.twisted(t),
		fc.twisted(t),
		fs.twisted(t)
	};
}

uint64_t Cube5x5::hash() const
{
	std::hash<uint64_t> h;
	uint64_t ret = c.hash() + 0x9E3779B9;
	ret ^= ec.hash() + 0x9E3779B9 + (ret << 6) + (ret >> 2);
	ret ^= es.hash() + 0x9E3779B9 + (ret << 6) + (ret >> 2);
	ret ^= fc.hash() + 0x9E3779B9 + (ret << 6) + (ret >> 2);
	ret ^= fs.hash() + 0x9E3779B9 + (ret << 6) + (ret >> 2);
	return ret;
}
