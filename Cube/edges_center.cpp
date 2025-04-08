#include "edges_center.h"
#include "bit.h"
#include "Math/math.h"
#include <array>
#include <stdexcept>

const std::vector<Twist> EdgesCenter::twists = {
    Twist::L1, Twist::L2, Twist::L3,
    Twist::R1, Twist::R2, Twist::R3,
    Twist::U1, Twist::U2, Twist::U3,
    Twist::D1, Twist::D2, Twist::D3,
    Twist::F1, Twist::F2, Twist::F3,
    Twist::B1, Twist::B2, Twist::B3
};

EdgesCenter::EdgesCenter(uint8_t e0, uint8_t e1, uint8_t e2, uint8_t e3, uint8_t e4, uint8_t e5, uint8_t e6, uint8_t e7, uint8_t e8, uint8_t e9, uint8_t e10, uint8_t e11, uint64_t ori_index)
{
	if (ori_index >= ori_size)
		throw std::invalid_argument("ori_index is too big");

	std::array<uint8_t, 12> o;
	std::ranges::iota(o, 0);
	nth_permutation(o, ori_index);

	state = _mm_set_epi8(
        0, 0, 0, 0,
		o[11] << 7 | e11,
		o[10] << 7 | e10,
		o[9] << 7 | e9,
        o[8] << 7 | e8,
        o[7] << 7 | e7,
        o[6] << 7 | e6,
        o[5] << 7 | e5,
        o[4] << 7 | e4,
        o[3] << 7 | e3,
        o[2] << 7 | e2,
        o[1] << 7 | e1,
        o[0] << 7 | e0);
}

EdgesCenter::EdgesCenter(
    uint8_t e0, uint8_t e1, uint8_t e2, uint8_t e3,
    uint8_t e4, uint8_t e5, uint8_t e6, uint8_t e7,
    uint8_t e8, uint8_t e9, uint8_t e10, uint8_t e11,
	uint8_t o0, uint8_t o1, uint8_t o2, uint8_t o3,
	uint8_t o4, uint8_t o5, uint8_t o6, uint8_t o7,
	uint8_t o8, uint8_t o9, uint8_t o10, uint8_t o11) noexcept
{
    state = _mm_set_epi8(
        0, 0, 0, 0,
        o11 << 7 | e11,
        o10 << 7 | e10,
        o9 << 7 | e9,
        o8 << 7 | e8,
        o7 << 7 | e7,
        o6 << 7 | e6,
        o5 << 7 | e5,
        o4 << 7 | e4,
        o3 << 7 | e3,
        o2 << 7 | e2,
        o1 << 7 | e1,
        o0 << 7 | e0);
}

EdgesCenter EdgesCenter::solved()
{
    return EdgesCenter{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
}

EdgesCenter EdgesCenter::impossible()
{
    return EdgesCenter{ _mm_setzero_si128() };
}

bool EdgesCenter::operator==(const EdgesCenter& o) const
{
    __m128i x = _mm_xor_si128(state, o.state);
    return _mm_testz_si128(x, x);
}

bool EdgesCenter::operator!=(const EdgesCenter& o) const
{
    return !(*this == o);
}

bool EdgesCenter::operator<(const EdgesCenter& o) const
{
    // Compare 8-bit lanes for ( a < b ), store the bits in the low 16 bits of the scalar value
	int less = _mm_movemask_epi8(_mm_cmplt_epi8(state, o.state));

    // Compare 8-bit lanes for ( a > b ), store the bits in the low 16 bits of the scalar value
	int greater = _mm_movemask_epi8(_mm_cmpgt_epi8(state, o.state));

    return less > greater;
}

bool EdgesCenter::is_solved() const
{
	return *this == EdgesCenter::solved();
}

int EdgesCenter::byte(int index) const
{
    switch (index)
    {
    case 0: return _mm_extract_epi8(state, 0);
    case 1: return _mm_extract_epi8(state, 1);
    case 2: return _mm_extract_epi8(state, 2);
    case 3: return _mm_extract_epi8(state, 3);
    case 4: return _mm_extract_epi8(state, 4);
    case 5: return _mm_extract_epi8(state, 5);
    case 6: return _mm_extract_epi8(state, 6);
    case 7: return _mm_extract_epi8(state, 7);
    case 8: return _mm_extract_epi8(state, 8);
    case 9: return _mm_extract_epi8(state, 9);
    case 10: return _mm_extract_epi8(state, 10);
    case 11: return _mm_extract_epi8(state, 11);
    default:
        throw std::out_of_range("Index out of range");
    }
}

uint8_t EdgesCenter::cubie(int index) const
{
	return byte(index) & 0x0F;
}

uint8_t EdgesCenter::orientation(int index) const
{
	return byte(index) >> 7;
}

std::array<uint8_t, 12> EdgesCenter::cubies() const
{
    return {
        cubie(0), cubie(1), cubie(2), cubie(3),
        cubie(4), cubie(5), cubie(6), cubie(7),
        cubie(8), cubie(9), cubie(10), cubie(11)
    };
}

std::array<uint8_t, 12> EdgesCenter::orientations() const
{
	return {
		orientation(0), orientation(1), orientation(2), orientation(3),
		orientation(4), orientation(5), orientation(6), orientation(7),
		orientation(8), orientation(9), orientation(10), orientation(11)
	};
}


__m128i byte_shuffle(__m128i state, int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9, int i10, int i11)
{
	return byte_shuffle(state, i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, 12, 13, 14, 15);
}

EdgesCenter EdgesCenter::twisted(Twist r) const
{
    const __m128i R_mask = _mm_set_epi8(0, 0, 0, 0, 0, 0x80u, 0x80u, 0, 0, 0x80u, 0x80u, 0, 0, 0, 0, 0);
    const __m128i L_mask = _mm_set_epi8(0, 0, 0, 0, 0x80u, 0, 0, 0x80u, 0x80u, 0, 0, 0x80u, 0, 0, 0, 0);
	switch (r)
	{
    case Twist::L1:
		return _mm_xor_si128(byte_shuffle(state, 0, 1, 2, 3, 11, 5, 6, 8, 4, 9, 10, 7), L_mask);
    case Twist::L2:
        return byte_shuffle(state, 0, 1, 2, 3, 7, 5, 6, 4, 11, 9, 10, 8);
    case Twist::L3:
		return _mm_xor_si128(byte_shuffle(state, 0, 1, 2, 3, 8, 5, 6, 11, 7, 9, 10, 4), L_mask);
    case Twist::R1:
        return _mm_xor_si128(byte_shuffle(state, 0, 1, 2, 3, 4, 9, 10, 7, 8, 6, 5, 11), R_mask);
    case Twist::R2:
        return byte_shuffle(state, 0, 1, 2, 3, 4, 6, 5, 7, 8, 10, 9, 11);
    case Twist::R3:
        return _mm_xor_si128(byte_shuffle(state, 0, 1, 2, 3, 4, 10, 9, 7, 8, 5, 6, 11), R_mask);
    case Twist::U1:
        return byte_shuffle(state, 5, 4, 2, 3, 0, 1, 6, 7, 8, 9, 10, 11);
    case Twist::U2:
        return byte_shuffle(state, 1, 0, 2, 3, 5, 4, 6, 7, 8, 9, 10, 11);
    case Twist::U3:
        return byte_shuffle(state, 4, 5, 2, 3, 1, 0, 6, 7, 8, 9, 10, 11);
    case Twist::D1:
        return byte_shuffle(state, 0, 1, 6, 7, 4, 5, 3, 2, 8, 9, 10, 11);
    case Twist::D2:
        return byte_shuffle(state, 0, 1, 3, 2, 4, 5, 7, 6, 8, 9, 10, 11);
    case Twist::D3:
        return byte_shuffle(state, 0, 1, 7, 6, 4, 5, 2, 3, 8, 9, 10, 11);
    case Twist::F1:
        return byte_shuffle(state, 8, 1, 2, 9, 4, 5, 6, 7, 3, 0, 10, 11);
    case Twist::F2:
        return byte_shuffle(state, 3, 1, 2, 0, 4, 5, 6, 7, 9, 8, 10, 11);
    case Twist::F3:
        return byte_shuffle(state, 9, 1, 2, 8, 4, 5, 6, 7, 0, 3, 10, 11);
    case Twist::B1:
        return byte_shuffle(state, 0, 10, 11, 3, 4, 5, 6, 7, 8, 9, 2, 1);
    case Twist::B2:
        return byte_shuffle(state, 0, 2, 1, 3, 4, 5, 6, 7, 8, 9, 11, 10);
    case Twist::B3:
        return byte_shuffle(state, 0, 11, 10, 3, 4, 5, 6, 7, 8, 9, 1, 2);
    default: return *this;
	}
}

uint64_t EdgesCenter::prm_index() const
{
    return permutation_index(cubies());
}

uint64_t EdgesCenter::ori_index() const
{
	return _mm_movemask_epi8(state) & 0x7FF;
}

uint64_t EdgesCenter::index() const
{
	return prm_index() * ori_size + ori_index();
}

std::array<uint8_t, 4> EdgesCenter::lr_slice_location() const
{
	uint64_t mask = _mm_movemask_epi8(_mm_cmplt_epi8(state, _mm_set1_epi8(4)));
    std::array<uint8_t, 4> loc;
	for (auto& l : loc)
	{
		l = std::countr_zero(mask);
		clear_lsb(mask);
	}
    return loc;
}

std::array<uint8_t, 4> EdgesCenter::ud_slice_location() const
{
    uint64_t mask = _mm_movemask_epi8(_mm_slli_epi64(state, 4));
    std::array<uint8_t, 4> loc;
    for (auto& l : loc)
    {
        l = std::countr_zero(mask);
        clear_lsb(mask);
    }
	return loc;
}

std::array<uint8_t, 4> EdgesCenter::fb_slice_location() const
{
    uint64_t mask = _mm_movemask_epi8(_mm_slli_epi64(state, 5));
    std::array<uint8_t, 4> loc;
	for (auto& l : loc)
    {
        l = std::countr_zero(mask);
        clear_lsb(mask);
    }
    return loc;
}

uint64_t EdgesCenter::hash() const
{
    uint64_t lo = _mm_extract_epi64(state, 0);
    uint64_t hi = _mm_extract_epi64(state, 1);
	return ::hash(lo, hi);
}

std::string to_string(const EdgesCenter& e)
{
	std::string str;
	for (auto c : e.cubies())
		str += std::to_string(c) + ' ';
    str += "| ";
	for (auto o : e.orientations())
		str += std::to_string(o) + ' ';
    str.pop_back();
	return str;
}
