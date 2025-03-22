#pragma once
#include "intrin.h"
#include <cstdint>
#include <bit>
#include <tuple>

// Clear Least Significant Bit.
void clear_lsb(uint64_t&);

uint64_t set_epi8(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7);
uint8_t extract_epi8(uint64_t, int index);

uint64_t byte_shuffle(uint64_t, int b0, int b1, int b2, int b3, int b4, int b5, int b6, int b7);
std::pair<uint64_t, uint64_t> byte_shuffle(
	uint64_t, uint64_t,
	int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7,
	int b0, int b1, int b2, int b3, int b4, int b5, int b6, int b7);

__m128i byte_shuffle(__m128i state, int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9, int i10, int i11, int i12, int i13, int i14, int i15);