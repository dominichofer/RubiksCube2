#pragma once
#include "intrin.h"
#include <cstdint>
#include <bit>

// Clear Least Significant Bit.
inline void ClearLSB(uint64_t& b) noexcept
{
	b &= b - 1;
}
