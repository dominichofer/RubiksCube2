#pragma once
#include "corners.h"
#include "edges_center.h"
#include <string>
#include <vector>

class Cube3x3
{
	Corners c;
	EdgesCenter e;

	Cube3x3(Corners c, EdgesCenter e) noexcept : c(c), e(e) {}
public:
	enum class Twist : uint8_t
	{
		L1, L2, L3,
		R1, R2, R3,
		U1, U2, U3,
		D1, D2, D3,
		F1, F2, F3,
		B1, B2, B3,
		None
	};
	static const std::vector<Twist> twists;

	Cube3x3() noexcept = default;
	static Cube3x3 superflip();
	static Cube3x3 impossible();

	bool operator==(const Cube3x3&) const;
	bool operator!=(const Cube3x3&) const;
	bool operator<(const Cube3x3&) const;

	const Corners& corners() const { return c; }
	const EdgesCenter& edges() const { return e; }

	bool is_solved() const { return c.is_solved() && e.is_solved(); }
	bool in_H() const;

	std::size_t coset_index() const;
	std::size_t set_index() const;

	Cube3x3 L1() const { return Cube3x3(c.L1(), e.L1()); }
	Cube3x3 L2() const { return Cube3x3(c.L2(), e.L2()); }
	Cube3x3 L3() const { return Cube3x3(c.L3(), e.L3()); }

	Cube3x3 R1() const { return Cube3x3(c.R1(), e.R1()); }
	Cube3x3 R2() const { return Cube3x3(c.R2(), e.R2()); }
	Cube3x3 R3() const { return Cube3x3(c.R3(), e.R3()); }

	Cube3x3 U1() const { return Cube3x3(c.U1(), e.U1()); }
	Cube3x3 U2() const { return Cube3x3(c.U2(), e.U2()); }
	Cube3x3 U3() const { return Cube3x3(c.U3(), e.U3()); }

	Cube3x3 D1() const { return Cube3x3(c.D1(), e.D1()); }
	Cube3x3 D2() const { return Cube3x3(c.D2(), e.D2()); }
	Cube3x3 D3() const { return Cube3x3(c.D3(), e.D3()); }

	Cube3x3 F1() const { return Cube3x3(c.F1(), e.F1()); }
	Cube3x3 F2() const { return Cube3x3(c.F2(), e.F2()); }
	Cube3x3 F3() const { return Cube3x3(c.F3(), e.F3()); }

	Cube3x3 B1() const { return Cube3x3(c.B1(), e.B1()); }
	Cube3x3 B2() const { return Cube3x3(c.B2(), e.B2()); }
	Cube3x3 B3() const { return Cube3x3(c.B3(), e.B3()); }

	Cube3x3 twisted(Twist) const;
	Cube3x3 twisted(const std::vector<Twist>&) const;

	uint64_t hash() const;
};

std::string to_string(Cube3x3::Twist);
std::string to_string(Cube3x3);

namespace std
{
	template <>
	struct hash<Cube3x3>
	{
		std::size_t operator()(const Cube3x3& c) const
		{
			return c.hash();
		}
	};
}
