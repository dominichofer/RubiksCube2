#include "corners.h"
#include "bit.h"
#include "Math/math.h"

const std::vector<Twist> Corners::twists = {
	Twist::L1, Twist::L2, Twist::L3,
	Twist::R1, Twist::R2, Twist::R3,
	Twist::U1, Twist::U2, Twist::U3,
	Twist::D1, Twist::D2, Twist::D3,
	Twist::F1, Twist::F2, Twist::F3,
	Twist::B1, Twist::B2, Twist::B3
};

Corners::Corners(uint64_t prm_index, uint64_t ori_index)
{
	if (prm_index >= prm_size)
		throw std::invalid_argument("prm_index is too big");
	if (ori_index >= ori_size)
		throw std::invalid_argument("ori_index is too big");
    std::array<uint8_t, 8> c;
    std::ranges::iota(c, 0);
	nth_permutation(c, prm_index);
    std::array<uint8_t, 8> o;
    std::ranges::iota(o, 0);
}

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
Corners Corners::solved() { return Corners(0, 1, 2, 3, 4, 5, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0); }
Corners Corners::impossible() { return Corners(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); }

bool Corners::is_solved() const { return *this == Corners::solved(); }
int Corners::cubie(int index) const { return (state >> (index * 8)) & 0x0F; }
int Corners::orientation(int index) const { return (state >> (index * 8 + 4)) & 0x0F; }

static const uint64_t ori_mask = 0x30'30'30'30'30'30'30'30ULL;
static const uint64_t upper_ori_bit = 0x20'20'20'20'20'20'20'20ULL;
static const uint64_t lower_ori_bit = 0x10'10'10'10'10'10'10'10ULL;
static const uint64_t L_mask = 0x00'FF'00'FF'00'FF'00'FFULL;
static const uint64_t R_mask = 0xFF'00'FF'00'FF'00'FF'00ULL;
static const uint64_t U_mask = 0x00'00'00'00'FF'FF'FF'FFULL;
static const uint64_t D_mask = 0xFF'FF'FF'FF'00'00'00'00ULL;
static const uint64_t F_mask = 0x00'00'FF'FF'00'00'FF'FFULL;
static const uint64_t B_mask = 0xFF'FF'00'00'FF'FF'00'00ULL;

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

Corners Corners::twisted(Twist r) const
{
    switch (r)
    {
    case Twist::L1:
        return ori_swap_0_2(byte_shuffle(state, 2, 1, 6, 3, 0, 5, 4, 7), L_mask);
    case Twist::L2:
        return byte_shuffle(state, 6, 1, 4, 3, 2, 5, 0, 7);
    case Twist::L3:
        return ori_swap_0_2(byte_shuffle(state, 4, 1, 0, 3, 6, 5, 2, 7), L_mask);
    case Twist::R1:
        return ori_swap_0_2(byte_shuffle(state, 0, 5, 2, 1, 4, 7, 6, 3), R_mask);
    case Twist::R2:
        return byte_shuffle(state, 0, 7, 2, 5, 4, 3, 6, 1);
    case Twist::R3:
        return ori_swap_0_2(byte_shuffle(state, 0, 3, 2, 7, 4, 1, 6, 5), R_mask);
    case Twist::U1:
        return ori_swap_1_2(byte_shuffle(state, 1, 3, 0, 2, 4, 5, 6, 7), U_mask);
    case Twist::U2:
        return byte_shuffle(state, 3, 2, 1, 0, 4, 5, 6, 7);
    case Twist::U3:
        return ori_swap_1_2(byte_shuffle(state, 2, 0, 3, 1, 4, 5, 6, 7), U_mask);
    case Twist::D1:
        return ori_swap_1_2(byte_shuffle(state, 0, 1, 2, 3, 6, 4, 7, 5), D_mask);
    case Twist::D2:
        return byte_shuffle(state, 0, 1, 2, 3, 7, 6, 5, 4);
    case Twist::D3:
        return ori_swap_1_2(byte_shuffle(state, 0, 1, 2, 3, 5, 7, 4, 6), D_mask);
    case Twist::F1:
        return ori_swap_0_1(byte_shuffle(state, 4, 0, 2, 3, 5, 1, 6, 7), F_mask);
    case Twist::F2:
        return byte_shuffle(state, 5, 4, 2, 3, 1, 0, 6, 7);
    case Twist::F3:
        return ori_swap_0_1(byte_shuffle(state, 1, 5, 2, 3, 0, 4, 6, 7), F_mask);
    case Twist::B1:
        return ori_swap_0_1(byte_shuffle(state, 0, 1, 3, 7, 4, 5, 2, 6), B_mask);
    case Twist::B2:
        return byte_shuffle(state, 0, 1, 7, 6, 4, 5, 3, 2);
    case Twist::B3:
        return ori_swap_0_1(byte_shuffle(state, 0, 1, 6, 2, 4, 5, 7, 3), B_mask);
    default: return *this;
    }
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
    return index_1 + index_2; // TODO: Move ">> 52" to here!
}

uint64_t Corners::index() const
{
    return prm_index() * ori_size + ori_index();
}

uint64_t Corners::hash() const
{
	return std::hash<uint64_t>{}(state);
}

std::string to_string(const Corners& c)  
{
   std::string str;
   for (int i = 0; i < 8; i++)
       str += std::to_string(c.cubie(i)) + ' ';
   for (int i = 0; i < 8; i++)
       str += std::to_string(c.orientation(i)) + ' ';
   str.pop_back();
   return str;
}
