#pragma once
#include "corners.h"
#include "edges_center.h"
#include "edges_side.h"
#include "faces_center.h"
#include "faces_side.h"
#include "twist.h"
#include <cstdint>
#include <vector>

class Cube5x5 : public Twistable<Cube5x5>
{
	Corners c;
	EdgesCenter ec;
	EdgesSide es;
	FacesCenter fc;
	FacesSide fs;

	Cube5x5(Corners c, EdgesCenter ec, EdgesSide es, FacesCenter fc, FacesSide fs) noexcept : c(c), ec(ec), es(es), fc(fc), fs(fs) {}
public:
	static const std::vector<Twist> twists;

	Cube5x5() noexcept = default;
	static Cube5x5 solved();
	static Cube5x5 impossible();

	auto operator<=>(const Cube5x5&) const = default;

	bool is_solved() const;
	const Corners& corners() const { return c; }
	const EdgesCenter& edges_center() const { return ec; }
	const EdgesSide& edges_side() const { return es; }
	const FacesCenter& faces_center() const { return fc; }
	const FacesSide& faces_side() const { return fs; }

	using Twistable::twisted;
	Cube5x5 twisted(Twist) const;

	uint64_t hash() const;
};
