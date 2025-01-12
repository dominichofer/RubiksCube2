#pragma once
#include <cstdint>
#include <tuple>

uint64_t set_epi8(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7);
uint8_t extract_epi8(uint64_t, int index);

uint64_t byte_shuffle(uint64_t, int b0, int b1, int b2, int b3, int b4, int b5, int b6, int b7);
std::pair<uint64_t, uint64_t> byte_shuffle(
	uint64_t, uint64_t,
	int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7,
	int b0, int b1, int b2, int b3, int b4, int b5, int b6, int b7);
