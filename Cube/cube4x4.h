#pragma once
#include "corners.h"
#include "edges_side.h"
#include "faces_side.h"
#include <array>
#include <string>
#include <vector>

class Cube4x4
{
	Corners c;
	EdgesSide e;
	FacesSide f;

	Cube4x4(Corners c, EdgesSide e, FacesSide f) noexcept : c(c), e(e), f(f) {}
public:
	enum class Twist : uint8_t
	{
		L1, L2, L3, l1, l2, l3,
		R1, R2, R3, r1, r2, r3,
		U1, U2, U3, u1, u2, u3,
		D1, D2, D3, d1, d2, d3,
		F1, F2, F3, f1, f2, f3,
		B1, B2, B3, b1, b2, b3,
		None
	};
	static const std::array<Twist, 36> twists;

	Cube4x4() noexcept = default;

	bool operator==(const Cube4x4&) const;
	bool operator!=(const Cube4x4&) const;
	bool operator<(const Cube4x4&) const;

	Corners corners() const { return c; }
	EdgesSide edges() const { return e; }
	FacesSide faces() const { return f; }

	bool is_solved() const { return c.is_solved() && e.is_solved() && f.is_solved(); }

	Cube4x4 L1() const { return Cube4x4(c.L1(), e.L1(), f.L1()); }
	Cube4x4 L2() const { return Cube4x4(c.L2(), e.L2(), f.L2()); }
	Cube4x4 L3() const { return Cube4x4(c.L3(), e.L3(), f.L3()); }
	
	Cube4x4 l1() const { return Cube4x4(c, e.l1(), f.l1()); }
	Cube4x4 l2() const { return Cube4x4(c, e.l2(), f.l2()); }
	Cube4x4 l3() const { return Cube4x4(c, e.l3(), f.l3()); }

	Cube4x4 R1() const { return Cube4x4(c.R1(), e.R1(), f.R1()); }
	Cube4x4 R2() const { return Cube4x4(c.R2(), e.R2(), f.R2()); }
	Cube4x4 R3() const { return Cube4x4(c.R3(), e.R3(), f.R3()); }

	Cube4x4 r1() const { return Cube4x4(c, e.r1(), f.r1()); }
	Cube4x4 r2() const { return Cube4x4(c, e.r2(), f.r2()); }
	Cube4x4 r3() const { return Cube4x4(c, e.r3(), f.r3()); }

	Cube4x4 U1() const { return Cube4x4(c.U1(), e.U1(), f.U1()); }
	Cube4x4 U2() const { return Cube4x4(c.U2(), e.U2(), f.U2()); }
	Cube4x4 U3() const { return Cube4x4(c.U3(), e.U3(), f.U3()); }

	Cube4x4 u1() const { return Cube4x4(c, e.u1(), f.u1()); }
	Cube4x4 u2() const { return Cube4x4(c, e.u2(), f.u2()); }
	Cube4x4 u3() const { return Cube4x4(c, e.u3(), f.u3()); }

	Cube4x4 D1() const { return Cube4x4(c.D1(), e.D1(), f.D1()); }
	Cube4x4 D2() const { return Cube4x4(c.D2(), e.D2(), f.D2()); }
	Cube4x4 D3() const { return Cube4x4(c.D3(), e.D3(), f.D3()); }

	Cube4x4 d1() const { return Cube4x4(c, e.d1(), f.d1()); }
	Cube4x4 d2() const { return Cube4x4(c, e.d2(), f.d2()); }
	Cube4x4 d3() const { return Cube4x4(c, e.d3(), f.d3()); }

	Cube4x4 F1() const { return Cube4x4(c.F1(), e.F1(), f.F1()); }
	Cube4x4 F2() const { return Cube4x4(c.F2(), e.F2(), f.F2()); }
	Cube4x4 F3() const { return Cube4x4(c.F3(), e.F3(), f.F3()); }

	Cube4x4 f1() const { return Cube4x4(c, e.f1(), f.f1()); }
	Cube4x4 f2() const { return Cube4x4(c, e.f2(), f.f2()); }
	Cube4x4 f3() const { return Cube4x4(c, e.f3(), f.f3()); }

	Cube4x4 B1() const { return Cube4x4(c.B1(), e.B1(), f.B1()); }
	Cube4x4 B2() const { return Cube4x4(c.B2(), e.B2(), f.B2()); }
	Cube4x4 B3() const { return Cube4x4(c.B3(), e.B3(), f.B3()); }

	Cube4x4 b1() const { return Cube4x4(c, e.b1(), f.b1()); }
	Cube4x4 b2() const { return Cube4x4(c, e.b2(), f.b2()); }
	Cube4x4 b3() const { return Cube4x4(c, e.b3(), f.b3()); }

	Cube4x4 twisted(Twist) const;
	Cube4x4 twisted(const std::vector<Twist>&) const;

	uint64_t hash() const;
};

std::string to_string(Cube4x4::Twist);
std::string to_string(Cube4x4);

namespace std
{
	template <>
	struct hash<Cube4x4>
	{
		std::size_t operator()(const Cube4x4& c) const
		{
			return c.hash();
		}
	};
}
