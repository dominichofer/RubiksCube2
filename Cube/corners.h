#pragma once
#include "twist.h"
#include <cstdint>
#include <vector>

class Corners : public Twistable<Corners>
{
    //   2 - 3
    //  /   /|
    // 0 - 1 |
    // | 6 | 7
    // 4 - 5/
    uint64_t state;

    Corners(uint64_t state) noexcept : state(state) {}
public:
    static const uint64_t prm_size = 40'320; // 8!
    static const uint64_t ori_size = 2'187; // 3^7
    static const uint64_t index_size = prm_size * ori_size;
    static const std::vector<Twist> twists;

	Corners() noexcept = default;
    Corners(
        uint8_t c0, uint8_t c1, uint8_t c2, uint8_t c3,
        uint8_t c4, uint8_t c5, uint8_t c6, uint8_t c7,
        uint8_t o0, uint8_t o1, uint8_t o2, uint8_t o3,
        uint8_t o4, uint8_t o5, uint8_t o6, uint8_t o7) noexcept;
    static Corners solved();
	static Corners impossible();

    auto operator<=>(const Corners&) const = default;

    bool is_solved() const;
    int cubie(int) const;
    int orientation(int) const;

    using Twistable<Corners>::twisted;
    Corners twisted(Twist) const;

    uint64_t prm_index() const;
    uint64_t ori_index() const;
    uint64_t index() const;
    uint64_t hash() const;
};
