#pragma once
#include "corners.h"
#include "edges_center.h"
#include "edges_side.h"
#include "faces_center.h"
#include "faces_side.h"
#include <array>
#include <string>
#include <vector>

class Cube5x5
{
	Corners c;
	EdgesCenter ec;
	EdgesSide es;
	FacesCenter fc;
	FacesSide fs;

	Cube5x5(Corners c, EdgesCenter ec, EdgesSide es, FacesCenter fc, FacesSide fs) noexcept : c(c), ec(ec), es(es), fc(fc), fs(fs) {}
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

	Cube5x5() noexcept = default;

	bool operator==(const Cube5x5&) const;
	bool operator!=(const Cube5x5&) const;
	bool operator<(const Cube5x5&) const;

	Corners corners() const { return c; }
	EdgesCenter edges_center() const { return ec; }
	EdgesSide edges_side() const { return es; }
	FacesCenter faces_center() const { return fc; }
	FacesSide faces_side() const { return fs; }

	bool is_solved() const { return c.is_solved() && ec.is_solved() && es.is_solved() && fc.is_solved() && fs.is_solved(); }

	Cube5x5 L1() const { return Cube5x5(c.L1(), ec.L1(), es.L1(), fc.L1(), fs.L1()); }
	Cube5x5 L2() const { return Cube5x5(c.L2(), ec.L2(), es.L2(), fc.L2(), fs.L2()); }
	Cube5x5 L3() const { return Cube5x5(c.L3(), ec.L3(), es.L3(), fc.L3(), fs.L3()); }

	Cube5x5 l1() const { return Cube5x5(c, ec, es.l1(), fc.l1(), fs.l1()); }
	Cube5x5 l2() const { return Cube5x5(c, ec, es.l2(), fc.l2(), fs.l2()); }
	Cube5x5 l3() const { return Cube5x5(c, ec, es.l3(), fc.l3(), fs.l3()); }

	Cube5x5 R1() const { return Cube5x5(c.R1(), ec.R1(), es.R1(), fc.R1(), fs.R1()); }
	Cube5x5 R2() const { return Cube5x5(c.R2(), ec.R2(), es.R2(), fc.R2(), fs.R2()); }
	Cube5x5 R3() const { return Cube5x5(c.R3(), ec.R3(), es.R3(), fc.R3(), fs.R3()); }

	Cube5x5 r1() const { return Cube5x5(c, ec, es.r1(), fc.r1(), fs.r1()); }
	Cube5x5 r2() const { return Cube5x5(c, ec, es.r2(), fc.r2(), fs.r2()); }
	Cube5x5 r3() const { return Cube5x5(c, ec, es.r3(), fc.r3(), fs.r3()); }

	Cube5x5 U1() const { return Cube5x5(c.U1(), ec.U1(), es.U1(), fc.U1(), fs.U1()); }
	Cube5x5 U2() const { return Cube5x5(c.U2(), ec.U2(), es.U2(), fc.U2(), fs.U2()); }
	Cube5x5 U3() const { return Cube5x5(c.U3(), ec.U3(), es.U3(), fc.U3(), fs.U3()); }

	Cube5x5 u1() const { return Cube5x5(c, ec, es.u1(), fc.u1(), fs.u1()); }
	Cube5x5 u2() const { return Cube5x5(c, ec, es.u2(), fc.u2(), fs.u2()); }
	Cube5x5 u3() const { return Cube5x5(c, ec, es.u3(), fc.u3(), fs.u3()); }

	Cube5x5 D1() const { return Cube5x5(c.D1(), ec.D1(), es.D1(), fc.D1(), fs.D1()); }
	Cube5x5 D2() const { return Cube5x5(c.D2(), ec.D2(), es.D2(), fc.D2(), fs.D2()); }
	Cube5x5 D3() const { return Cube5x5(c.D3(), ec.D3(), es.D3(), fc.D3(), fs.D3()); }

	Cube5x5 d1() const { return Cube5x5(c, ec, es.d1(), fc.d1(), fs.d1()); }
	Cube5x5 d2() const { return Cube5x5(c, ec, es.d2(), fc.d2(), fs.d2()); }
	Cube5x5 d3() const { return Cube5x5(c, ec, es.d3(), fc.d3(), fs.d3()); }

	Cube5x5 F1() const { return Cube5x5(c.F1(), ec.F1(), es.F1(), fc.F1(), fs.F1()); }
	Cube5x5 F2() const { return Cube5x5(c.F2(), ec.F2(), es.F2(), fc.F2(), fs.F2()); }
	Cube5x5 F3() const { return Cube5x5(c.F3(), ec.F3(), es.F3(), fc.F3(), fs.F3()); }

	Cube5x5 f1() const { return Cube5x5(c, ec, es.f1(), fc.f1(), fs.f1()); }
	Cube5x5 f2() const { return Cube5x5(c, ec, es.f2(), fc.f2(), fs.f2()); }
	Cube5x5 f3() const { return Cube5x5(c, ec, es.f3(), fc.f3(), fs.f3()); }

	Cube5x5 B1() const { return Cube5x5(c.B1(), ec.B1(), es.B1(), fc.B1(), fs.B1()); }
	Cube5x5 B2() const { return Cube5x5(c.B2(), ec.B2(), es.B2(), fc.B2(), fs.B2()); }
	Cube5x5 B3() const { return Cube5x5(c.B3(), ec.B3(), es.B3(), fc.B3(), fs.B3()); }
		
	Cube5x5 b1() const { return Cube5x5(c, ec, es.b1(), fc.b1(), fs.b1()); }
	Cube5x5 b2() const { return Cube5x5(c, ec, es.b2(), fc.b2(), fs.b2()); }
	Cube5x5 b3() const { return Cube5x5(c, ec, es.b3(), fc.b3(), fs.b3()); }

	Cube5x5 twisted(Twist) const;
	Cube5x5 twisted(const std::vector<Twist>&) const;

	uint64_t hash() const;
};

std::string to_string(Cube5x5::Twist);
std::string to_string(Cube5x5);

namespace std
{
	template <>
	struct hash<Cube5x5>
	{
		size_t operator()(const Cube5x5& c) const
		{
			return c.hash();
		}
	};
}
