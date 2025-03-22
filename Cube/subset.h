#pragma once
#include "cube3x3.h"
#include "twist.h"
#include "Math/math.h"
#include <vector>

// H0 = { L2,R2,F2,B2,U,D }
namespace H0
{
    static const uint64_t subset_size = factorial(8) * factorial(8) * factorial(4) / 2;
    static const uint64_t cosets = std::pow(3, 7) * std::pow(2, 11) * binomial(12, 4);
    static inline std::vector<Twist> twists = {
		Twist::L2,
		Twist::R2,
		Twist::U1, Twist::U2, Twist::U3,
		Twist::D1, Twist::D2, Twist::D3,
		Twist::F2,
		Twist::B2,
	};

    uint64_t subset_index(const Cube3x3&);
    uint64_t coset_index(const Cube3x3&);

	Cube3x3 from_coset_index(uint64_t);
}
