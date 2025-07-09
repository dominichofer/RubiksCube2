#pragma once
#include "corners.h"
#include "edges_center.h"

class Cube3x3 : public Twistable<Cube3x3>
{
	uint16_t c_prm;
	uint16_t c_ori;
	uint32_t e_prm;
	uint16_t e_slice_loc;
	uint16_t e_ori;

	Cube3x3(
		uint16_t c_prm,
		uint16_t c_ori,
		uint32_t e_prm,
		uint16_t e_slice_loc,
		uint16_t e_ori) noexcept;
public:
	Cube3x3(const Corners& c, const EdgesCenter& e) noexcept;
	Cube3x3() noexcept;

	auto operator<=>(const Cube3x3&) const = default;

	using Twistable::twisted;
	Cube3x3 twisted(Twist) const;

	static Cube3x3 from_index(uint64_t coset_number, uint64_t coset_index);
	uint64_t coset_number() const;
	uint64_t coset_index() const;

	friend std::string to_string(const Cube3x3&);
};