#pragma once
#include "twist.h"
#include <cstdint>
#include <vector>

class FacesSide : public Twistable<FacesSide>
{
	//       +-----+
	//       |     |
	//       |     |
	// +-----+-----+-----+-----+
	// | 0  1|     | 4  5|     |
	// | 2  3|     | 6  7|     |
	// +-----+-----+-----+-----+
	//       |     |
	//       |     |
	//       +-----+
	uint64_t a;

	//       +-----+
	//       | 0  1|
	//       | 2  3|
	// +-----+-----+-----+-----+
	// |     |     |     |     |
	// |     |     |     |     |
	// +-----+-----+-----+-----+
	//       | 4  5|
	//       | 6  7|
	//       +-----+
	uint64_t b;

	//       +-----+
	//       |     |
	//       |     |
	// +-----+-----+-----+-----+
	// |     | 0  1|     | 4  5|
	// |     | 2  3|     | 6  7|
	// +-----+-----+-----+-----+
	//       |     |
	//       |     |
	//       +-----+
	uint64_t c;

	FacesSide(uint64_t a, uint64_t b, uint64_t c) noexcept : a(a), b(b), c(c) {}
public:
	static const uint64_t prm_size = 3'246'670'537'110'000; // 24! / 24^6
	static const Twists twists;

	FacesSide() noexcept = default;
	FacesSide(
		uint8_t f0, uint8_t f1, uint8_t f2, uint8_t f3,
		uint8_t f4, uint8_t f5, uint8_t f6, uint8_t f7,
		uint8_t f8, uint8_t f9, uint8_t f10, uint8_t f11,
		uint8_t f12, uint8_t f13, uint8_t f14, uint8_t f15,
		uint8_t f16, uint8_t f17, uint8_t f18, uint8_t f19,
		uint8_t f20, uint8_t f21, uint8_t f22, uint8_t f23) noexcept;
	static FacesSide solved();
	static FacesSide impossible();

	auto operator<=>(const FacesSide&) const = default;

	bool is_solved() const;
	uint8_t cubie(int) const;
	std::array<uint8_t, 24> cubies() const;

	using Twistable::twisted;
	FacesSide twisted(Twist) const;

	uint64_t prm_index() const;
	uint64_t index() const;
	uint64_t hash() const;
};

std::string to_string(const FacesSide&);

namespace std
{
	template <>
	struct hash<FacesSide>
	{
		size_t operator()(const FacesSide& c) const
		{
			return c.hash();
		}
	};
}
