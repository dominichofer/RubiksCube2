#pragma once
#include "corners.h"
#include "edges_center.h"
#include "twist.h"
#include <cstdint>
#include <vector>

class Cube3x3 : public Twistable<Cube3x3>
{
	Corners c;
	EdgesCenter e;

	Cube3x3(Corners c, EdgesCenter e) noexcept : c(c), e(e) {}
public:
	static const std::vector<Twist> twists;

	Cube3x3() noexcept = default;
	static Cube3x3 solved();
	static Cube3x3 impossible();
	static Cube3x3 superflip();

	auto operator<=>(const Cube3x3&) const = default;

	bool is_solved() const { return c.is_solved() && e.is_solved(); }
	const Corners& corners() const { return c; }
	const EdgesCenter& edges() const { return e; }

	using Twistable::twisted;
	Cube3x3 twisted(Twist) const;

	uint64_t hash() const;
};
