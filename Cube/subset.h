#pragma once
#include "cube3x3.h"
#include "twist.h"
#include "Math/math.h"
#include <vector>

// H0 = { L2,R2,U,D,F2,B2 }
namespace H0
{
	static const uint64_t set_size = Corners::prm_size * EdgesCenter::ud_prm_size / 2;
	static const uint64_t cosets = Corners::ori_size * EdgesCenter::ori_size * EdgesCenter::ud_slice_loc_size;
	static inline Twists twists = {
			Twist::L2,
			Twist::R2,
			Twist::U1, Twist::U2, Twist::U3,
			Twist::D1, Twist::D2, Twist::D3,
			Twist::F2,
			Twist::B2,
	};
	static inline Twists non_twists = {
			Twist::L1, Twist::L3,
			Twist::R1, Twist::R3,
			Twist::F1, Twist::F3,
			Twist::B1, Twist::B3,
	};

	struct CosetNumber
	{
		uint64_t e_slice_loc, e_ori, c_ori;
	};

	struct CosetIndex
	{
		uint64_t e_prm, c_prm;
	};

	uint64_t coset_number(uint64_t corner_ori, uint64_t edge_ori, uint64_t slice_loc);
	uint64_t coset_number(const Cube3x3&);
	uint64_t coset_index(uint64_t corner_prm, uint64_t edge_prm);
	uint64_t coset_index(const Cube3x3&);

	CosetNumber from_coset_number(uint64_t);
	CosetIndex from_coset_index(uint64_t);
	Cube3x3 from_coset(uint64_t number, uint64_t index);

	bool in_subset(const Cube3x3&);
	bool same_coset(const Cube3x3&, const Cube3x3&);
}
