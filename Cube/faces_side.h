#pragma once
#include <cstdint>
#include <string>
#include <vector>

class FacesSide
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

	FacesSide(uint64_t a, uint64_t b, uint64_t c) noexcept;
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

	FacesSide() noexcept;
	FacesSide(
		uint8_t f0, uint8_t f1, uint8_t f2, uint8_t f3,
		uint8_t f4, uint8_t f5, uint8_t f6, uint8_t f7,
		uint8_t f8, uint8_t f9, uint8_t f10, uint8_t f11,
		uint8_t f12, uint8_t f13, uint8_t f14, uint8_t f15,
		uint8_t f16, uint8_t f17, uint8_t f18, uint8_t f19,
		uint8_t f20, uint8_t f21, uint8_t f22, uint8_t f23) noexcept;

	bool operator==(const FacesSide&) const;
	bool operator!=(const FacesSide&) const;
	bool operator<(const FacesSide&) const;

	int cubie(int) const;

	bool is_solved() const;

	FacesSide L1() const;
	FacesSide L2() const;
	FacesSide L3() const;

	FacesSide l1() const;
	FacesSide l2() const;
	FacesSide l3() const;

	FacesSide R1() const;
	FacesSide R2() const;
	FacesSide R3() const;

	FacesSide r1() const;
	FacesSide r2() const;
	FacesSide r3() const;

	FacesSide U1() const;
	FacesSide U2() const;
	FacesSide U3() const;

	FacesSide u1() const;
	FacesSide u2() const;
	FacesSide u3() const;

	FacesSide D1() const;
	FacesSide D2() const;
	FacesSide D3() const;

	FacesSide d1() const;
	FacesSide d2() const;
	FacesSide d3() const;

	FacesSide F1() const;
	FacesSide F2() const;
	FacesSide F3() const;

	FacesSide f1() const;
	FacesSide f2() const;
	FacesSide f3() const;

	FacesSide B1() const;
	FacesSide B2() const;
	FacesSide B3() const;

	FacesSide b1() const;
	FacesSide b2() const;
	FacesSide b3() const;

	FacesSide twisted(Twist) const;
	FacesSide twisted(const std::vector<Twist>&) const;

	uint64_t prm_index() const;
	uint64_t index() const;

	static const uint64_t prm_size = 3'246'670'537'110'000; // 24!/24^6

	uint64_t hash() const;
};

std::string to_string(FacesSide::Twist);
std::string to_string(FacesSide);

namespace std
{
	template <>
	struct hash<FacesSide>
	{
		std::size_t operator()(const FacesSide& e) const
		{
			return e.hash();
		}
	};
}