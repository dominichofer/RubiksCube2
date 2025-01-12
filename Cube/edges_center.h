#pragma once
#include <cstdint>
#include <intrin.h>
#include <string>
#include <vector>

class EdgesCenter
{
    //     +----2----+
    //    /|        /|
    //   3 11      1 10
    //  +----0----+  |
    //  |  |      |  |
    //  |  +----6-|--+
    //  8 /       9 /
    //  |7        |5
    //  +----4----+
    __m128i state;

    EdgesCenter(__m128i state) noexcept;
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

    EdgesCenter() noexcept;
    EdgesCenter(
        uint8_t e0, uint8_t e1, uint8_t e2, uint8_t e3,
        uint8_t e4, uint8_t e5, uint8_t e6, uint8_t e7,
        uint8_t e8, uint8_t e9, uint8_t e10, uint8_t e11,
        uint8_t o0, uint8_t o1, uint8_t o2, uint8_t o3,
        uint8_t o4, uint8_t o5, uint8_t o6, uint8_t o7,
        uint8_t o8, uint8_t o9, uint8_t o10, uint8_t o11) noexcept;

    bool operator==(const EdgesCenter&) const;
    bool operator!=(const EdgesCenter&) const;
    bool operator<(const EdgesCenter&) const;

    int cubie(int) const;
    int orientation(int) const;

    bool is_solved() const;

    EdgesCenter L1() const;
    EdgesCenter L2() const;
    EdgesCenter L3() const;

    EdgesCenter R1() const;
    EdgesCenter R2() const;
    EdgesCenter R3() const;

    EdgesCenter U1() const;
    EdgesCenter U2() const;
    EdgesCenter U3() const;

    EdgesCenter D1() const;
    EdgesCenter D2() const;
    EdgesCenter D3() const;

    EdgesCenter F1() const;
    EdgesCenter F2() const;
    EdgesCenter F3() const;

    EdgesCenter B1() const;
    EdgesCenter B2() const;
    EdgesCenter B3() const;

    EdgesCenter twisted(Twist) const;
    EdgesCenter twisted(const std::vector<Twist>&) const;

    uint64_t prm_index() const;
    uint64_t ori_index() const;
    uint64_t index() const;

	static const uint64_t prm_size = 479'001'600; // 12!
	static const uint64_t ori_size = 2'048; // 2^11
	static const uint64_t index_size = prm_size * ori_size;

    uint64_t hash() const;
};

std::string to_string(EdgesCenter::Twist);
std::string to_string(EdgesCenter);

namespace std
{
    template <>
    struct hash<EdgesCenter>
    {
        std::size_t operator()(const EdgesCenter& e) const
        {
            return e.hash();
        }
    };
}
