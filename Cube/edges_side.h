#pragma once
#include <cstdint>
#include "intrin.h"
#include <string>
#include <vector>

class EdgesSide
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

	EdgesSide(uint64_t a, uint64_t b, uint64_t c) noexcept;
public:
	enum class Twist : uint8_t
	{
		L1, L2, L3, l1, l2, l3,
		R1, R2, R3, r1, r2, r3,
		U1, U2, U3, u1, u2, u3,
		D1, D2, D3, d1, d2, d3,
		F1, F2, F3, f1, f2, f3,
		B1, B2, B3, b1, b2, b3,
		None
	};
	static const std::vector<Twist> twists;

	EdgesSide() noexcept;
	EdgesSide(
		uint8_t a0, uint8_t a1, uint8_t a2, uint8_t a3,
		uint8_t a4, uint8_t a5, uint8_t a6, uint8_t a7,
		uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3,
		uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7,
		uint8_t c0, uint8_t c1, uint8_t c2, uint8_t c3,
		uint8_t c4, uint8_t c5, uint8_t c6, uint8_t c7) noexcept;

	bool operator==(const EdgesSide&) const;
	bool operator!=(const EdgesSide&) const;
	bool operator<(const EdgesSide&) const;

	int cubie(int) const;

	bool is_solved() const;

	EdgesSide L1() const;
	EdgesSide L2() const;
	EdgesSide L3() const;

	EdgesSide l1() const;
	EdgesSide l2() const;
	EdgesSide l3() const;

	EdgesSide R1() const;
	EdgesSide R2() const;
	EdgesSide R3() const;

	EdgesSide r1() const;
	EdgesSide r2() const;
	EdgesSide r3() const;

	EdgesSide U1() const;
	EdgesSide U2() const;
	EdgesSide U3() const;

	EdgesSide u1() const;
	EdgesSide u2() const;
	EdgesSide u3() const;

	EdgesSide D1() const;
	EdgesSide D2() const;
	EdgesSide D3() const;

	EdgesSide d1() const;
	EdgesSide d2() const;
	EdgesSide d3() const;

	EdgesSide F1() const;
	EdgesSide F2() const;
	EdgesSide F3() const;

	EdgesSide f1() const;
	EdgesSide f2() const;
	EdgesSide f3() const;

	EdgesSide B1() const;
	EdgesSide B2() const;
	EdgesSide B3() const;

	EdgesSide b1() const;
	EdgesSide b2() const;
	EdgesSide b3() const;

	EdgesSide twisted(Twist) const;
	EdgesSide twisted(const std::vector<Twist>&) const;

	uint64_t prm_index() const;
	uint64_t index() const;

	//static const uint64_t prm_size = 620'448'401'733'239'439'360'000ULL; // 24!

	uint64_t hash() const;
};

std::string to_string(EdgesSide::Twist);
std::string to_string(EdgesSide);

namespace std
{
	template <>
	struct hash<EdgesSide>
	{
		std::size_t operator()(const EdgesSide& e) const
		{
			return e.hash();
		}
	};
}