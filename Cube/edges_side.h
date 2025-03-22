#pragma once
#include "intrin.h"
#include "twist.h"
#include <cstdint>
#include <vector>

class EdgesSide : public Twistable<EdgesSide>
{
	//     +--2----3-+
	//    /|        /|
	//   / |       / |
	//  +--0----1-+  |
	//  |  |      |  |
	//  |  +--4---|5-+
	//  | /       | /
	//  |/        |/
	//  +--6----7-+
	uint64_t a;

	//     +---------+
	//    /6        /4
	//   / |       / |
	//  +---------+  |
	//  0  7      2  5
	//  |  +------|--+
	//  | /       | /
	//  1/        3/
	//  +---------+
	uint64_t b;

	//     +---------+
	//    1|        7|
	//   0 |       6 |
	//  +---------+  |
	//  |  |      |  |
	//  |  +------|--+
	//  | 3       | 5
	//  |2        |4
	//  +---------+
	uint64_t c;

	EdgesSide(uint64_t a, uint64_t b, uint64_t c) noexcept : a(a), b(b), c(c) {}
public:
	//static const uint64_t prm_size = 620'448'401'733'239'439'360'000ULL; // 24!
	static const std::vector<Twist> twists;

	EdgesSide() noexcept = default;
	EdgesSide(
		uint8_t a0, uint8_t a1, uint8_t a2, uint8_t a3,
		uint8_t a4, uint8_t a5, uint8_t a6, uint8_t a7,
		uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3,
		uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7,
		uint8_t c0, uint8_t c1, uint8_t c2, uint8_t c3,
		uint8_t c4, uint8_t c5, uint8_t c6, uint8_t c7) noexcept;
	static EdgesSide solved();
	static EdgesSide impossible();

	auto operator<=>(const EdgesSide&) const = default;
	bool is_solved() const;

	int cubie(int) const;

	EdgesSide twisted(Twist) const;

	uint64_t prm_index() const;
	uint64_t index() const;
	uint64_t hash() const;
};
