#pragma once
#include <cstdint>
#include <string>
#include <vector>

class Corners
{
    //   2 - 3
    //  /   /|
    // 0 - 1 |
    // | 6 | 7
    // 4 - 5/
    uint64_t state;

    Corners(uint64_t state) noexcept;
public:
    enum class Twist : uint8_t
    {
        L1, L2, L3,
        R1, R2, R3,
        U1, U2, U3,
        D1, D2, D3,
        F1, F2, F3,
        B1, B2, B3,
        None
    };
    static const std::array<Twist, 18> twists;

    Corners() noexcept;
    Corners(
        uint8_t c0, uint8_t c1, uint8_t c2, uint8_t c3,
        uint8_t c4, uint8_t c5, uint8_t c6, uint8_t c7,
        uint8_t o0, uint8_t o1, uint8_t o2, uint8_t o3,
        uint8_t o4, uint8_t o5, uint8_t o6, uint8_t o7) noexcept;

    bool operator==(const Corners&) const;
    bool operator!=(const Corners&) const;
    bool operator<(const Corners&) const;

    int cubie(int) const;
    int orientation(int) const;

    bool is_solved() const;

    Corners L1() const;
    Corners L2() const;
    Corners L3() const;

    Corners R1() const;
    Corners R2() const;
    Corners R3() const;

    Corners U1() const;
    Corners U2() const;
    Corners U3() const;

    Corners D1() const;
    Corners D2() const;
    Corners D3() const;

    Corners F1() const;
    Corners F2() const;
    Corners F3() const;

    Corners B1() const;
    Corners B2() const;
    Corners B3() const;

    Corners twisted(Twist) const;
    Corners twisted(const std::vector<Twist>&) const;

    uint64_t prm_index() const;
    uint64_t ori_index() const;
    uint64_t index() const;

	static const uint64_t prm_size = 40'320; // 8!
	static const uint64_t ori_size = 2'187; // 3^7
	static const uint64_t index_size = prm_size * ori_size;

    uint64_t hash() const;
};

std::string to_string(Corners::Twist);
std::string to_string(Corners);

namespace std
{
    template <>
    struct hash<Corners>
    {
        std::size_t operator()(const Corners& c) const
        {
            return c.hash();
        }
	};
}
