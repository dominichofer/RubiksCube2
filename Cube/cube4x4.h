#pragma once
#include "corners.h"
#include "edges_side.h"
#include "faces_side.h"
#include "twist.h"
#include <cstdint>
#include <vector>

class Cube4x4 : public Twistable<Cube4x4>
{
	Corners c;
	EdgesSide e;
	FacesSide f;

	Cube4x4(Corners c, EdgesSide e, FacesSide f) noexcept : c(c), e(e), f(f) {}
public:
	static const std::vector<Twist> twists;

	Cube4x4() noexcept = default;
	static Cube4x4 solved();
	static Cube4x4 impossible();

	auto operator<=>(const Cube4x4&) const = default;

	bool is_solved() const { return c.is_solved() && e.is_solved() && f.is_solved(); }
	const Corners& corners() const { return c; }
	const EdgesSide& edges() const { return e; }
	const FacesSide& faces() const { return f; }


	Cube4x4 twisted(Twist) const;

	uint64_t hash() const;
};
