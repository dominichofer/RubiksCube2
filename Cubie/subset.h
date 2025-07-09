#pragma once
#include "Math/math.h"
#include "corners.h"
#include "edges_center.h"
#include <cstdint>

// H0 = { L2,R2,U,D,F2,B2 }
namespace H0
{
	static constexpr uint64_t set_size = Corners::prm_size * EdgesCenter::prm_size / 2;
	static constexpr uint64_t cosets = Corners::ori_size * EdgesCenter::ori_size * EdgesCenter::slice_loc_size;
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
}