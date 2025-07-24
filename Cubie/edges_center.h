#pragma once
#include "twist.h"
#include "Std/std.h"
#include "Math/math.h"
#include <array>
#include <cstdint>
#include <tuple>
#include <vector>

class EdgesCenter : public Twistable<EdgesCenter>
{
	//     +----1----+
	//    /|        /|
	//   4 11      5 10
	//  +----0----+  |
	//  |  |      |  |
	//  |  +----2-|--+
	//  8 /       9 /
	//  |7        |6
	//  +----3----+
	std::array<uint8_t, 12> s = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

	EdgesCenter(std::array<uint8_t, 12> s) noexcept : s(std::move(s)) {}

	uint8_t cubie(int) const;
	uint8_t orientation(int) const;
	std::array<uint8_t, 12> cubies() const;
	std::array<uint8_t, 12> orientations() const;
public:
	static constexpr uint64_t slice_prm_size = factorial(4);
	static constexpr uint64_t non_slice_prm_size = factorial(8);
	static constexpr uint64_t slice_loc_size = binomial(12, 4);
	static constexpr uint64_t ori_size = powi(2, 11);

	EdgesCenter() noexcept = default;
	EdgesCenter(std::array<uint8_t, 12> edges, std::array<uint8_t, 12> orientations) noexcept;

	auto operator<=>(const EdgesCenter&) const = default;

	using Twistable::twisted;
	EdgesCenter twisted(Twist) const;

	bool is_solved() const;

	static EdgesCenter from_index(uint8_t slice_prm, uint16_t non_slice_prm, uint16_t slice_loc, uint16_t ori);
	uint8_t slice_prm_index() const;
	uint16_t non_slice_prm_index() const;
	uint16_t slice_loc_index() const;
	uint16_t ori_index() const;

	friend std::string to_string(const EdgesCenter&);
};
