#pragma once
#include "cube3x3.h"
#include "twist.h"
#include "Math/math.h"
#include <vector>

// H0 = { L2,R2,F2,B2,U,D }
namespace H0
{
	static const uint64_t set_size = factorial(8) * factorial(8) * factorial(4) / 2;
	static const uint64_t cosets = powi(3, 7) * powi(2, 11) * binomial(12, 4);
	static inline std::vector<Twist> twists = {
			Twist::L2, Twist::R2, Twist::F2, Twist::B2,
			Twist::U1, Twist::U2, Twist::U3,
			Twist::D1, Twist::D2, Twist::D3,
	};
	static inline std::vector<Twist> non_twists = {
			Twist::L1, Twist::L3,
			Twist::R1, Twist::R3,
			Twist::F1, Twist::F3,
			Twist::B1, Twist::B3,
	};

	// Identifies the cube in the subset.
	uint64_t subset_index(const Cube3x3&);

	// Determines to which coset the cube belongs.
	uint64_t coset_number(const Cube3x3&);

	// Identifies the cube in the coset.
	uint64_t coset_index(const Cube3x3&);

	Cube3x3 from_subset(uint64_t index);
	Cube3x3 from_coset(int64_t number, int64_t index);

	bool in_subset(const Cube3x3&);
	bool same_coset(const Cube3x3&, const Cube3x3&);
}
