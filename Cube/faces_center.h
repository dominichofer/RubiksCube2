#pragma once
#include "twist.h"
#include <cstdint>
#include <vector>

class FacesCenter
{
	//+--------+
	//||
	//||
	//||
	// +--------+--------+--------+--------+
	// |1 ||5 ||
	// | 2 0|| 6 4||
	// |3 ||7 ||
	// +--------+--------+--------+--------+
	//||
	//||
	//||
	//+--------+
	uint64_t a;

	//+--------+
	//|1 |
	//| 2 0|
	//|3 |
	// +--------+--------+--------+--------+
	// |||||
	// |||||
	// |||||
	// +--------+--------+--------+--------+
	//|5 |
	//| 6 4|
	//|7 |
	//+--------+
	uint64_t b;

	//+--------+
	//||
	//||
	//||
	// +--------+--------+--------+--------+
	// ||1 ||5 |
	// || 2 0|| 6 4|
	// ||3 ||7 |
	// +--------+--------+--------+--------+
	//||
	//||
	//||
	//+--------+
	uint64_t c;

	FacesCenter(uint64_t a, uint64_t b, uint64_t c) noexcept : a(a), b(b), c(c) {}
public:
	static const uint64_t prm_size = 3'246'670'537'110'000; // 24! / 24^6
	static const std::vector<Twist> twists;

	FacesCenter() noexcept = default;
	FacesCenter(
		uint8_t f0, uint8_t f1, uint8_t f2, uint8_t f3,
		uint8_t f4, uint8_t f5, uint8_t f6, uint8_t f7,
		uint8_t f8, uint8_t f9, uint8_t f10, uint8_t f11,
		uint8_t f12, uint8_t f13, uint8_t f14, uint8_t f15,
		uint8_t f16, uint8_t f17, uint8_t f18, uint8_t f19,
		uint8_t f20, uint8_t f21, uint8_t f22, uint8_t f23) noexcept;
	static FacesCenter solved();
	static FacesCenter impossible();

	auto operator<=>(const FacesCenter&) const = default;

	bool is_solved() const;
	uint8_t cubie(int) const;
	std::array<uint8_t, 24> cubies() const;

	FacesCenter twisted(Twist) const;

	uint64_t prm_index() const;
	uint64_t index() const;
	uint64_t hash() const;
};

std::string to_string(const FacesCenter&);

namespace std
{
	template <>
	struct hash<FacesCenter>
	{
		size_t operator()(const FacesCenter& c) const
		{
			return c.hash();
		}
	};
}
