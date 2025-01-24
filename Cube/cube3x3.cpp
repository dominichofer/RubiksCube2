#include "cube3x3.h"
#include <sstream>
#include <utility>

const std::array<Cube3x3::Twist, 18> Cube3x3::twists = {
	Twist::L1, Twist::L2, Twist::L3,
	Twist::R1, Twist::R2, Twist::R3,
	Twist::U1, Twist::U2, Twist::U3,
	Twist::D1, Twist::D2, Twist::D3,
	Twist::F1, Twist::F2, Twist::F3,
	Twist::B1, Twist::B2, Twist::B3
};

Cube3x3 Cube3x3::superflip()
{
	// From https://en.wikipedia.org/wiki/Superflip
	return Cube3x3().U1().R2().F1().B1().R1().B2().R1().U2().L1().B2().R1().U3().D3().R2().F1().R3().L1().B2().U2().F2();
}

Cube3x3 Cube3x3::impossible()
{
	return Cube3x3(Corners(0, 1, 2, 3, 4, 5, 6, 7, 0, 0, 0, 0, 0, 0, 0, 1), EdgesCenter());
}

bool Cube3x3::operator==(const Cube3x3& o) const
{
	return c == o.c && e == o.e;
}

bool Cube3x3::operator!=(const Cube3x3& o) const
{
	return !(*this == o);
}

bool Cube3x3::operator<(const Cube3x3& o) const
{
	if (c != o.c)
		return c < o.c;
	return e < o.e;
}

bool Cube3x3::in_H() const
{
	return c.ori_index() == 0 && e.ori_index() == 0 && e.cubie(8) >= 8 && e.cubie(9) >= 8 && e.cubie(10) >= 8 && e.cubie(11) >= 8;
}

Cube3x3 Cube3x3::twisted(Twist t) const
{
	switch (t)
	{
	case Twist::L1: return L1();
	case Twist::L2: return L2();
	case Twist::L3: return L3();
	case Twist::R1: return R1();
	case Twist::R2: return R2();
	case Twist::R3: return R3();
	case Twist::U1: return U1();
	case Twist::U2: return U2();
	case Twist::U3: return U3();
	case Twist::D1: return D1();
	case Twist::D2: return D2();
	case Twist::D3: return D3();
	case Twist::F1: return F1();
	case Twist::F2: return F2();
	case Twist::F3: return F3();
	case Twist::B1: return B1();
	case Twist::B2: return B2();
	case Twist::B3: return B3();
	case Twist::None: return *this;
	}
}

Cube3x3 Cube3x3::twisted(const std::vector<Twist>& twists) const
{
	auto cube = *this;
	for (auto t : twists)
		cube = cube.twisted(t);
	return cube;
}

uint64_t Cube3x3::hash() const
{
	return c.hash() ^ e.hash();
}

std::string to_string(Cube3x3::Twist t)
{
	return std::array{
		"L1", "L2", "L3",
		"R1", "R2", "R3",
		"U1", "U2", "U3",
		"D1", "D2", "D3",
		"F1", "F2", "F3",
		"B1", "B2", "B3"
	} [std::to_underlying(t)];
}

std::string to_string(Cube3x3 cube)
{
	auto c = [cube](uint8_t i)
		{ return std::to_string(cube.corners().cubie(i)); };
	auto co = [cube](uint8_t i)
		{ return std::to_string(cube.corners().orientation(i)); };
	auto e = [cube](uint8_t i)
		{
			std::string s = std::to_string(cube.edges().cubie(i));
			return std::string(2 - s.length(), ' ') + s;
		};
	auto eo = [cube](uint8_t i)
		{ return std::to_string(cube.edges().orientation(i)); };

	//     2----2----3         0----0----0
	//    /|        /|        /|        /|
	//   3 11      1 10      0 0       0 0
	//  0----0----1  |      0----0----0  |
	//  |  |      |  |      |  |      |  |
	//  |  6----6-|--7      |  0----0-|--0
	//  8 /       9 /       0 /       0 /
	//  |7        |5        |0        |0
	//  4----4----5         0----0----0
	std::ostringstream oss;
	oss << "       Piece            Orientation\n"
		<< "    " << c(2) << "---" << e(2) << "----" << c(3) << "         " << co(2) << "----" << eo(2) << "----" << co(3) << "\n"
		<< "   /|        /|        /|        /|\n"
		<< " " << e(3) << " " << e(11) << "     " << e(1) << " " << e(10) << "      " << eo(3) << " " << eo(11) << "       " << eo(1) << " " << eo(10) << "\n"
		<< " " << c(0) << "---" << e(0) << "----" << c(1) << "  |      " << co(0) << "----" << eo(0) << "----" << co(1) << "  |\n"
		<< " |  |      |  |      |  |      |  |\n"
		<< " |  " << c(6) << "---" << e(6) << "-|--" << c(7) << "      |  " << co(6) << "----" << eo(6) << "-|--" << co(7) << "\n"
		<< e(8) << "  /     " << e(9) << " /       " << eo(8) << " /       " << eo(9) << " /\n"
		<< " |" << e(7) << "       |" << e(5) << "       |" << eo(7) << "        |" << eo(5) << "\n"
		<< " " << c(4) << "---" << e(4) << "----" << c(5) << "         " << co(4) << "----" << eo(4) << "----" << co(5) << "\n";
	return oss.str();
}
