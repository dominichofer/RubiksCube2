#pragma once
#include "twist.h"
#include "Std/std.h"
#include "Math/math.h"
#include <array>
#include <cstdint>
#include <string>

class Corners : public Twistable<Corners>
{
	//     2---------3
	//    /|        /|
	//   / |       / |
	//  0---------1  |
	//  |  |      |  |
	//  |  6------|--7
	//  | /       | /
	//  |/        |/
	//  4---------5
	std::array<uint8_t, 8> s = { 0, 1, 2, 3, 4, 5, 6, 7 };

	Corners(std::array<uint8_t, 8> s) noexcept : s(std::move(s)) {}

	uint8_t cubie(int) const;
	uint8_t orientation(int) const;
	std::array<uint8_t, 8> cubies() const;
	std::array<uint8_t, 8> orientations() const;
public:
	static constexpr uint16_t prm_size = factorial(8);
	static constexpr uint16_t ori_size = powi(3, 7);
	static constexpr uint32_t size = prm_size * ori_size;

	Corners() noexcept = default;
	Corners(std::array<uint8_t, 8> cubies, std::array<uint8_t, 8> orientations) noexcept;

	auto operator<=>(const Corners&) const = default;

	using Twistable::twisted;
	Corners twisted(Twist) const;

	bool is_solved() const;

	static Corners from_index(uint16_t prm, uint16_t ori);
	static Corners from_index(uint32_t);
	uint16_t prm_index() const;
	uint16_t ori_index() const;
	uint32_t index() const;

	friend std::string to_string(const Corners&);
};
