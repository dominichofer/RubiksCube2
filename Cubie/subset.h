#pragma once
#include "corners.h"
#include "cube3x3.h"
#include "edges_center.h"
#include <cstdint>

// H0 = { L2,R2,U,D,F2,B2 }
namespace H0
{
	static inline const Twists twists = {
			Twist::L2,
			Twist::R2,
			Twist::U1, Twist::U2, Twist::U3,
			Twist::D1, Twist::D2, Twist::D3,
			Twist::F2,
			Twist::B2,
	};
	static inline const Twists non_twists = {
			Twist::L1, Twist::L3,
			Twist::R1, Twist::R3,
			Twist::F1, Twist::F3,
			Twist::B1, Twist::B3,
	};
}

class SubsetCube : public Twistable<SubsetCube>
{
	uint16_t c_prm; // 8! = 40'320
	uint8_t e_slice_prm; // 4! = 24
	uint16_t e_non_slice_prm; // 8! = 40'320

	SubsetCube(
		uint16_t c_prm,
		uint8_t e_slice_prm,
		uint16_t e_non_slice_prm) noexcept;
public:
	static constexpr uint64_t size = Corners::prm_size / 2 * EdgesCenter::slice_prm_size * EdgesCenter::non_slice_prm_size;

	SubsetCube(const Cube3x3& = Cube3x3{}) noexcept;

	auto operator<=>(const SubsetCube&) const = default;

	using Twistable::twisted;
	SubsetCube twisted(Twist) const;

	bool is_solved() const;

	static SubsetCube from_subset_index(uint64_t);
	uint64_t subset_index() const;
};

class CosetNumberCube : public Twistable<CosetNumberCube>
{
	uint16_t c_ori; // 3^7 = 2'187
	uint16_t e_ori; // 2^11 = 2'048
	uint16_t e_slice_loc; // 12 choose 4 = 495

	CosetNumberCube(
		uint16_t c_ori,
		uint16_t e_ori,
		uint16_t e_slice_loc) noexcept;
public:
	static constexpr uint32_t size = Corners::ori_size * EdgesCenter::ori_size * EdgesCenter::slice_loc_size;

	CosetNumberCube(const Cube3x3& = Cube3x3{}) noexcept;
	static CosetNumberCube impossible() noexcept;

	auto operator<=>(const CosetNumberCube&) const = default;

	using Twistable::twisted;
	CosetNumberCube twisted(Twist) const;

	bool in_subset() const;

	static CosetNumberCube from_coset_number(uint32_t);
	uint32_t coset_number() const;

	uint64_t hash() const;
};

//class CosetIndexCube : public Twistable<CosetIndexCube>
//{
//	uint16_t c_prm; // 8! = 40'320
//	uint8_t e_slice_prm; // 4! = 24
//	uint16_t e_non_slice_prm; // 8! = 40'320
//	uint16_t e_slice_loc; // 12 choose 4 = 495
//
//	CosetIndexCube(
//		uint16_t c_prm,
//		uint8_t e_slice_prm,
//		uint16_t e_non_slice_prm,
//		uint16_t e_slice_loc) noexcept;
//public:
//	static constexpr uint64_t size = Corners::prm_size / 2 * EdgesCenter::slice_prm_size * EdgesCenter::non_slice_prm_size;
//
//	CosetIndexCube(const Corners& c, const EdgesCenter& e) noexcept;
//	CosetIndexCube() noexcept;
//
//	auto operator<=>(const CosetIndexCube&) const = default;
//
//	using Twistable::twisted;
//	CosetIndexCube twisted(Twist) const;
//
//	bool is_solved() const;
//
//	static CosetIndexCube from_subset_index(uint64_t);
//	uint64_t subset_index() const;
//};

//class CosetIndexCube
//{
//	uint16_t c_prm; // 8! = 40'320
//	uint8_t e_slice_prm; // 4! = 24
//	uint16_t e_non_slice_prm; // 8! = 40'320
//
//	CosetIndexCube(
//		uint16_t c_prm,
//		uint8_t e_slice_prm,
//		uint16_t e_non_slice_prm) noexcept;
//public:
//	static constexpr uint32_t size =
//
//	CosetIndexCube(const Corners& c, const EdgesCenter& e) noexcept;
//	CosetIndexCube() noexcept;
//
//	auto operator<=>(const CosetIndexCube&) const = default;
//
//	CosetIndexCube twisted(Twist) const;
//};
