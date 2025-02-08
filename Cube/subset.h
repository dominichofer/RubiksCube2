#pragma once
#include "cube3x3.h"
#include "Math/math.h"
#include <vector>

// H0 = { L2,R2,F2,B2,U,D }
namespace H0
{
    const std::vector<Cube3x3::Twist> twists;

    uint64_t subset_index(const Cube3x3&);
    uint64_t coset_inedx(const Cube3x3&);

    static const uint64_t subset_size = factorial(8) * factorial(8) * factorial(4) / 2;
    static const uint64_t cosets = std::pow(3, 7) * std::pow(2, 11) * binomial(12, 4);
}
