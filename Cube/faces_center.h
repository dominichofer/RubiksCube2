#pragma once
#include <cstdint>
#include <string>
#include <vector>

class FacesCenter
{
	//          +--------+
	//          |        |
	//          |        |
	//          |        |
	// +--------+--------+--------+--------+
	// |    1   |        |    5   |        |
	// | 2     0|        | 6     4|        |
	// |    3   |        |    7   |        |
	// +--------+--------+--------+--------+
	//          |        |
	//          |        |
	//          |        |
	//          +--------+
	uint64_t a;

	//          +--------+
	//          |    1   |
	//          | 2     0|
	//          |    3   |
	// +--------+--------+--------+--------+
	// |        |        |        |        |
	// |        |        |        |        |
	// |        |        |        |        |
	// +--------+--------+--------+--------+
	//          |    5   |
	//          | 6     4|
	//          |    7   |
	//          +--------+
	uint64_t b;

	//          +--------+
	//          |        |
	//          |        |
	//          |        |
	// +--------+--------+--------+--------+
	// |        |    1   |        |    5   |
	// |        | 2     0|        | 6     4|
	// |        |    3   |        |    7   |
	// +--------+--------+--------+--------+
	//          |        |
	//          |        |
	//          |        |
	//          +--------+
	uint64_t c;

	FacesCenter(uint64_t a, uint64_t b, uint64_t c) noexcept;
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
	static const std::array<Twist, 36> twists;

	FacesCenter() noexcept;
	FacesCenter(
		uint8_t f0, uint8_t f1, uint8_t f2, uint8_t f3,
		uint8_t f4, uint8_t f5, uint8_t f6, uint8_t f7,
		uint8_t f8, uint8_t f9, uint8_t f10, uint8_t f11,
		uint8_t f12, uint8_t f13, uint8_t f14, uint8_t f15,
		uint8_t f16, uint8_t f17, uint8_t f18, uint8_t f19,
		uint8_t f20, uint8_t f21, uint8_t f22, uint8_t f23) noexcept;

	bool operator==(const FacesCenter&) const;
	bool operator!=(const FacesCenter&) const;
	bool operator<(const FacesCenter&) const;

	int cubie(int) const;

	bool is_solved() const;

	FacesCenter L1() const;
	FacesCenter L2() const;
	FacesCenter L3() const;

	FacesCenter l1() const;
	FacesCenter l2() const;
	FacesCenter l3() const;

	FacesCenter R1() const;
	FacesCenter R2() const;
	FacesCenter R3() const;

	FacesCenter r1() const;
	FacesCenter r2() const;
	FacesCenter r3() const;

	FacesCenter U1() const;
	FacesCenter U2() const;
	FacesCenter U3() const;

	FacesCenter u1() const;
	FacesCenter u2() const;
	FacesCenter u3() const;

	FacesCenter D1() const;
	FacesCenter D2() const;
	FacesCenter D3() const;

	FacesCenter d1() const;
	FacesCenter d2() const;
	FacesCenter d3() const;

	FacesCenter F1() const;
	FacesCenter F2() const;
	FacesCenter F3() const;

	FacesCenter f1() const;
	FacesCenter f2() const;
	FacesCenter f3() const;

	FacesCenter B1() const;
	FacesCenter B2() const;
	FacesCenter B3() const;

	FacesCenter b1() const;
	FacesCenter b2() const;
	FacesCenter b3() const;

	FacesCenter twisted(Twist) const;
	FacesCenter twisted(const std::vector<Twist>&) const;

	uint64_t prm_index() const;
	uint64_t index() const;

	static const uint64_t prm_size = 3'246'670'537'110'000; // 24!/24^6

	uint64_t hash() const;
};

std::string to_string(FacesCenter::Twist);
std::string to_string(FacesCenter);

namespace std
{
	template <>
	struct hash<FacesCenter>
	{
		std::size_t operator()(const FacesCenter& e) const
		{
			return e.hash();
		}
	};
}