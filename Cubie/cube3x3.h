#pragma once
#include "corners.h"
#include "edges_center.h"
#include "twist.h"
#include <cstdint>

class Cube3x3 : public Twistable<Cube3x3>
{
	Cube3x3(
		uint16_t c_ori,
		uint16_t c_prm,
		uint16_t e_ori,
		uint8_t e_slice_prm,
		uint16_t e_non_slice_prm,
		uint16_t e_slice_loc) noexcept;
public:
	uint16_t c_ori; // 3^7 = 2'187
	uint16_t c_prm; // 8! = 40'320
	uint16_t e_ori; // 2^11 = 2'048
	uint8_t e_slice_prm; // 4! = 24
	uint16_t e_non_slice_prm; // 8! = 40'320
	uint16_t e_slice_loc; // 12 choose 4 = 495

	static constexpr uint64_t set_size = Corners::prm_size / 2 * EdgesCenter::slice_prm_size * EdgesCenter::non_slice_prm_size;
	static constexpr uint32_t cosets = Corners::ori_size * EdgesCenter::ori_size * EdgesCenter::slice_loc_size;

	Cube3x3() noexcept;
	static Cube3x3 impossible() noexcept;
	static Cube3x3 from_subset(uint64_t) noexcept;
	static Cube3x3 from_coset(uint64_t number, uint64_t index) noexcept;

	auto operator<=>(const Cube3x3&) const = default;

	using Twistable::twisted;
	Cube3x3 twisted(Twist) const;

	uint64_t coset_index() const;
	uint64_t coset_number() const;
	uint32_t corners_index() const
	{
		return static_cast<uint32_t>(c_prm * Corners::ori_size + c_ori);
	}

	bool in_subset() const;
	bool is_solved() const;

	uint64_t hash() const;
};
