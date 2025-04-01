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
	return EdgesCenter(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

EdgesCenter EdgesCenter::impossible()
{
    return EdgesCenter(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
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

int EdgesCenter::cubie(int index) const
{
    switch (index)
    {
    case 0: return _mm_extract_epi8(state, 0) & 0x0F;
    case 1: return _mm_extract_epi8(state, 1) & 0x0F;
    case 2: return _mm_extract_epi8(state, 2) & 0x0F;
    case 3: return _mm_extract_epi8(state, 3) & 0x0F;
    case 4: return _mm_extract_epi8(state, 4) & 0x0F;
    case 5: return _mm_extract_epi8(state, 5) & 0x0F;
    case 6: return _mm_extract_epi8(state, 6) & 0x0F;
    case 7: return _mm_extract_epi8(state, 7) & 0x0F;
    case 8: return _mm_extract_epi8(state, 8) & 0x0F;
    case 9: return _mm_extract_epi8(state, 9) & 0x0F;
    case 10: return _mm_extract_epi8(state, 10) & 0x0F;
    case 11: return _mm_extract_epi8(state, 11) & 0x0F;
	default: throw std::out_of_range("index out of range");
    }
}

int EdgesCenter::orientation(int index) const
{
    switch (index)
    {
    case 0: return _mm_extract_epi8(state, 0) >> 7;
    case 1: return _mm_extract_epi8(state, 1) >> 7;
    case 2: return _mm_extract_epi8(state, 2) >> 7;
    case 3: return _mm_extract_epi8(state, 3) >> 7;
    case 4: return _mm_extract_epi8(state, 4) >> 7;
    case 5: return _mm_extract_epi8(state, 5) >> 7;
    case 6: return _mm_extract_epi8(state, 6) >> 7;
    case 7: return _mm_extract_epi8(state, 7) >> 7;
    case 8: return _mm_extract_epi8(state, 8) >> 7;
    case 9: return _mm_extract_epi8(state, 9) >> 7;
    case 10: return _mm_extract_epi8(state, 10) >> 7;
    case 11: return _mm_extract_epi8(state, 11) >> 7;
    default: throw std::out_of_range("index out of range");
    }
}

static const __m128i B_mask = _mm_set_epi8(0, 0, 0, 0, 0x80u, 0x80u, 0, 0, 0, 0x80u, 0, 0, 0, 0x80u, 0, 0);
static const __m128i F_mask = _mm_set_epi8(0, 0, 0, 0, 0, 0, 0x80u, 0x80u, 0, 0, 0, 0x80u, 0, 0, 0, 0x80u);

EdgesCenter EdgesCenter::twisted(Twist r) const
{
	switch (r)
	{
    case Twist::L1:
        return byte_shuffle(state, 0, 1, 2, 11, 4, 5, 6, 8, 3, 9, 10, 7, 12, 13, 14, 15);
    case Twist::L2:
        return byte_shuffle(state, 0, 1, 2, 7, 4, 5, 6, 3, 11, 9, 10, 8, 12, 13, 14, 15);
    case Twist::L3:
        return byte_shuffle(state, 0, 1, 2, 8, 4, 5, 6, 11, 7, 9, 10, 3, 12, 13, 14, 15);
    case Twist::R1:
        return byte_shuffle(state, 0, 9, 2, 3, 4, 10, 6, 7, 8, 5, 1, 11, 12, 13, 14, 15);
    case Twist::R2:
        return byte_shuffle(state, 0, 5, 2, 3, 4, 1, 6, 7, 8, 10, 9, 11, 12, 13, 14, 15);
    case Twist::R3:
        return byte_shuffle(state, 0, 10, 2, 3, 4, 9, 6, 7, 8, 1, 5, 11, 12, 13, 14, 15);
    case Twist::U1:
        return byte_shuffle(state, 1, 2, 3, 0, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
    case Twist::U2:
        return byte_shuffle(state, 2, 3, 0, 1, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
    case Twist::U3:
        return byte_shuffle(state, 3, 0, 1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
    case Twist::D1:
        return byte_shuffle(state, 0, 1, 2, 3, 7, 4, 5, 6, 8, 9, 10, 11, 12, 13, 14, 15);
    case Twist::D2:
        return byte_shuffle(state, 0, 1, 2, 3, 6, 7, 4, 5, 8, 9, 10, 11, 12, 13, 14, 15);
    case Twist::D3:
        return byte_shuffle(state, 0, 1, 2, 3, 5, 6, 7, 4, 8, 9, 10, 11, 12, 13, 14, 15);
    case Twist::F1:
        return _mm_xor_si128(byte_shuffle(state, 8, 1, 2, 3, 9, 5, 6, 7, 4, 0, 10, 11, 12, 13, 14, 15), F_mask);
    case Twist::F2:
        return byte_shuffle(state, 4, 1, 2, 3, 0, 5, 6, 7, 9, 8, 10, 11, 12, 13, 14, 15);
    case Twist::F3:
        return _mm_xor_si128(byte_shuffle(state, 9, 1, 2, 3, 8, 5, 6, 7, 0, 4, 10, 11, 12, 13, 14, 15), F_mask);
    case Twist::B1:
        return _mm_xor_si128(byte_shuffle(state, 0, 1, 10, 3, 4, 5, 11, 7, 8, 9, 6, 2, 12, 13, 14, 15), B_mask);
    case Twist::B2:
        return byte_shuffle(state, 0, 1, 6, 3, 4, 5, 2, 7, 8, 9, 11, 10, 12, 13, 14, 15);
    case Twist::B3:
        return _mm_xor_si128(byte_shuffle(state, 0, 1, 11, 3, 4, 5, 10, 7, 8, 9, 2, 6, 12, 13, 14, 15), B_mask);
    default: return *this;
	}
}

uint64_t EdgesCenter::prm_index() const
{
	return permutation_index(cubie(0), cubie(1), cubie(2), cubie(3), cubie(4), cubie(5), cubie(6), cubie(7), cubie(8), cubie(9), cubie(10), cubie(11));
}

uint64_t EdgesCenter::ori_index() const
{
	return _mm_movemask_epi8(state) & 0x7FF;
}

uint64_t EdgesCenter::index() const
{
	return prm_index() * ori_size + ori_index();
}

uint64_t EdgesCenter::ud_slice_location_index() const
{
    __m128i edges = _mm_and_si128(state, _mm_set1_epi8(0x0F));
    __m128i ud_edges = _mm_cmpgt_epi8(edges, _mm_set1_epi8(7));
    uint64_t mask = _mm_movemask_epi8(ud_edges);
    std::array<int, 4> combination;
    for (int i = 0; i < combination.size(); i++)
    {
        combination[i] = std::countr_zero(mask);
        clear_lsb(mask);
    }
    return combination_index(12, combination);
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
	for (int i = 0; i < 12; i++)
		str += std::to_string(e.cubie(i)) + ' ';
	for (int i = 0; i < 12; i++)
		str += std::to_string(e.orientation(i)) + ' ';
    str.pop_back();
	return str;
}
