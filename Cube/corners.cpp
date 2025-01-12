#include "corners.h"
#include "byte.h"
#include "Math/math.h"
#include <array>
#include <intrin.h>
#include <sstream>

const std::array<Corners::Twist, 18> Corners::twists = {
	Twist::L1, Twist::L2, Twist::L3,
	Twist::R1, Twist::R2, Twist::R3,
	Twist::U1, Twist::U2, Twist::U3,
	Twist::D1, Twist::D2, Twist::D3,
	Twist::F1, Twist::F2, Twist::F3,
	Twist::B1, Twist::B2, Twist::B3
};

std::string to_string(Corners::Twist t)
{
    return std::array{
        "L1", "L2", "L3",
        "R1", "R2", "R3",
        "U1", "U2", "U3",
        "D1", "D2", "D3",
        "F1", "F2", "F3",
        "B1", "B2", "B3"
    } [std::to_underlying(t)] ;
}

Corners::Corners(uint64_t state) noexcept : state(state) {}

Corners::Corners() noexcept : Corners(0, 1, 2, 3, 4, 5, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0) {}

Corners::Corners(
    uint8_t c0, uint8_t c1, uint8_t c2, uint8_t c3,
    uint8_t c4, uint8_t c5, uint8_t c6, uint8_t c7,
    uint8_t o0, uint8_t o1, uint8_t o2, uint8_t o3,
    uint8_t o4, uint8_t o5, uint8_t o6, uint8_t o7) noexcept
{
    state = 0;
    state += static_cast<uint64_t>(o0 << 4 | c0);
    state += static_cast<uint64_t>(o1 << 4 | c1) << 8;
    state += static_cast<uint64_t>(o2 << 4 | c2) << 16;
    state += static_cast<uint64_t>(o3 << 4 | c3) << 24;
    state += static_cast<uint64_t>(o4 << 4 | c4) << 32;
    state += static_cast<uint64_t>(o5 << 4 | c5) << 40;
    state += static_cast<uint64_t>(o6 << 4 | c6) << 48;
    state += static_cast<uint64_t>(o7 << 4 | c7) << 56;
}

bool Corners::operator==(const Corners& o) const { return state == o.state; }
bool Corners::operator!=(const Corners& o) const { return !(*this == o); }
bool Corners::operator<(const Corners& o) const { return state < o.state; }

int Corners::cubie(int index) const { return (state >> (index * 8)) & 0x0F; }
int Corners::orientation(int index) const { return (state >> (index * 8 + 4)) & 0x0F; }

bool Corners::is_solved() const { return *this == Corners(); }

const uint64_t ori_mask = 0x30'30'30'30'30'30'30'30ULL;
const uint64_t upper_ori_bit = 0x20'20'20'20'20'20'20'20ULL;
const uint64_t lower_ori_bit = 0x10'10'10'10'10'10'10'10ULL;
const uint64_t L_mask = 0x00'FF'00'FF'00'FF'00'FFULL;
const uint64_t R_mask = 0xFF'00'FF'00'FF'00'FF'00ULL;
const uint64_t U_mask = 0x00'00'00'00'FF'FF'FF'FFULL;
const uint64_t D_mask = 0xFF'FF'FF'FF'00'00'00'00ULL;
const uint64_t F_mask = 0x00'00'FF'FF'00'00'FF'FFULL;
const uint64_t B_mask = 0xFF'FF'00'00'FF'FF'00'00ULL;

uint64_t ori_swap_0_1(uint64_t state, uint64_t mask)
{
    // Maps
    // b0000'XXXX -> b0001'XXXX
    // b0001'XXXX -> b0000'XXXX
    // b0010'XXXX -> b0010'XXXX
    
    // 1 NOT, 1 AND, 1 XOR, 1 SHIFT
    mask &= upper_ori_bit;
    return ((~state & mask) >> 1) ^ state;
}

uint64_t ori_swap_0_2(uint64_t state, uint64_t mask)
{
    // Maps
    // b0000'XXXX -> b0010'XXXX
    // b0001'XXXX -> b0001'XXXX
    // b0010'XXXX -> b0000'XXXX

    // 1 NOT, 1 AND, 1 OR, 1 SUB
    mask &= ori_mask;
    uint64_t x = (upper_ori_bit & mask) - (state & mask);
    return (state & ~mask) | x;
}

uint64_t ori_swap_1_2(uint64_t state, uint64_t mask)
{
    // Maps
    // b0000'XXXX -> b0000'XXXX
    // b0001'XXXX -> b0010'XXXX
    // b0010'XXXX -> b0001'XXXX

    // 3 AND, 2 SHIFT, 2 OR
    uint64_t l = (upper_ori_bit & mask & state) >> 1;
    uint64_t r = (lower_ori_bit & mask & state) << 1;
    return (state & ~(mask & ori_mask)) | l | r;
}

Corners Corners::L1() const
{
    auto s = byte_shuffle(state, 2, 1, 6, 3, 0, 5, 4, 7);
    return ori_swap_0_2(s, L_mask);
}

Corners Corners::L2() const
{
    return byte_shuffle(state, 6, 1, 4, 3, 2, 5, 0, 7);
}

Corners Corners::L3() const
{
    auto s = byte_shuffle(state, 4, 1, 0, 3, 6, 5, 2, 7);
    return ori_swap_0_2(s, L_mask);
}

Corners Corners::R1() const
{
    auto s = byte_shuffle(state, 0, 5, 2, 1, 4, 7, 6, 3);
    return ori_swap_0_2(s, R_mask);
}

Corners Corners::R2() const
{
    return byte_shuffle(state, 0, 7, 2, 5, 4, 3, 6, 1);
}

Corners Corners::R3() const
{
    auto s = byte_shuffle(state, 0, 3, 2, 7, 4, 1, 6, 5);
    return ori_swap_0_2(s, R_mask);
}

Corners Corners::U1() const
{
    auto s = byte_shuffle(state, 1, 3, 0, 2, 4, 5, 6, 7);
    return ori_swap_1_2(s, U_mask);
}

Corners Corners::U2() const
{
    return byte_shuffle(state, 3, 2, 1, 0, 4, 5, 6, 7);
}

Corners Corners::U3() const
{
    auto s = byte_shuffle(state, 2, 0, 3, 1, 4, 5, 6, 7);
    return ori_swap_1_2(s, U_mask);
}

Corners Corners::D1() const
{
    auto s = byte_shuffle(state, 0, 1, 2, 3, 6, 4, 7, 5);
    return ori_swap_1_2(s, D_mask);
}

Corners Corners::D2() const
{
    return byte_shuffle(state, 0, 1, 2, 3, 7, 6, 5, 4);
}

Corners Corners::D3() const
{
    auto s = byte_shuffle(state, 0, 1, 2, 3, 5, 7, 4, 6);
    return ori_swap_1_2(s, D_mask);
}

Corners Corners::F1() const
{
    auto s = byte_shuffle(state, 4, 0, 2, 3, 5, 1, 6, 7);
    return ori_swap_0_1(s, F_mask);
}

Corners Corners::F2() const
{
    return byte_shuffle(state, 5, 4, 2, 3, 1, 0, 6, 7);
}

Corners Corners::F3() const
{
    auto s = byte_shuffle(state, 1, 5, 2, 3, 0, 4, 6, 7);
    return ori_swap_0_1(s, F_mask);
}

Corners Corners::B1() const
{
    auto s = byte_shuffle(state, 0, 1, 3, 7, 4, 5, 2, 6);
    return ori_swap_0_1(s, B_mask);
}

Corners Corners::B2() const
{
    return byte_shuffle(state, 0, 1, 7, 6, 4, 5, 3, 2);
}

Corners Corners::B3() const
{
    auto s = byte_shuffle(state, 0, 1, 6, 2, 4, 5, 7, 3);
    return ori_swap_0_1(s, B_mask);
}

Corners Corners::twisted(Twist r) const
{
    switch (r)
    {
    case Twist::L1: return L1();
    case Twist::L2: return L2();
    case Twist::L3: return L3();
    case Twist::R1: return R1();
    case Twist::R2: return R2();
    case Twist::R3: return R3();
    case Twist::U1: return U1();
    case Twist::U2: return U2();
    case Twist::U3: return U3();
    case Twist::D1: return D1();
    case Twist::D2: return D2();
    case Twist::D3: return D3();
    case Twist::F1: return F1();
    case Twist::F2: return F2();
    case Twist::F3: return F3();
    case Twist::B1: return B1();
    case Twist::B2: return B2();
    case Twist::B3: return B3();
	case Twist::None: return *this;
    }
}

Corners Corners::twisted(const std::vector<Twist>& twists) const
{
    Corners c = *this;
    for (auto t : twists)
        c = c.twisted(t);
    return c;
}

uint64_t Corners::prm_index() const
{
	return permutation_index(cubie(0), cubie(1), cubie(2), cubie(3), cubie(4), cubie(5), cubie(6), cubie(7));
}

uint64_t Corners::ori_index() const
{
    uint64_t ori_1 = state & 0x00'30'00'30'00'30'00'30ULL;
    uint64_t ori_2 = state & 0x00'00'30'00'30'00'30'00ULL;
    uint64_t index_1 = (ori_1 * 0x02'D9'00'51'00'09'00'01ULL) >> 52;
    uint64_t index_2 = (ori_2 * 0x00'00'F3'00'1B'00'03'00ULL) >> 52;
    return index_1 + index_2;
}

uint64_t Corners::index() const
{
    return prm_index() * 2'187 + ori_index();
}

uint64_t Corners::hash() const
{
    std::hash<uint64_t> h;
	return h(state);
}

std::string to_string(Corners corners)
{
    auto c = [corners](uint8_t i)
        { return std::to_string(corners.cubie(i)); };
    auto o = [corners](uint8_t i)
        { return std::to_string(corners.orientation(i)); };

    //   2 - 3    2 - 3
    //  /   /|   /   /|
    // 0 - 1 |  0 - 1 |
    // | 6 | 7  | 6 | 7
    // 4 - 5/   4 - 5/
    std::ostringstream oss;
    oss << " Cubie  Orientation\n"
        << "  " << c(2) << " - " << c(3) << "    " << o(2) << " - " << o(3) << "\n"
        << " /   /|   /   /|\n"
        << c(0) << " - " << c(1) << " |  " << o(0) << " - " << o(1) << " |\n"
        << "| " << c(6) << " | " << c(7) << "  | " << o(6) << " | " << o(7) << "\n"
        << c(4) << " - " << c(5) << "/   " << o(4) << " - " << o(5) << "/\n";
    return oss.str();
}
