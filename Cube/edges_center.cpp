#include "edges_center.h"
#include "Math/math.h"
#include <array>
#include <sstream>

const std::array<EdgesCenter::Twist, 18> EdgesCenter::twists = {
    Twist::L1, Twist::L2, Twist::L3,
    Twist::R1, Twist::R2, Twist::R3,
    Twist::U1, Twist::U2, Twist::U3,
    Twist::D1, Twist::D2, Twist::D3,
    Twist::F1, Twist::F2, Twist::F3,
    Twist::B1, Twist::B2, Twist::B3
};

std::string to_string(EdgesCenter::Twist t)
{
    return std::array{
        "L1", "L2", "L3",
        "R1", "R2", "R3",
        "U1", "U2", "U3",
        "D1", "D2", "D3",
        "F1", "F2", "F3",
        "B1", "B2", "B3"
    } [std::to_underlying(t)];
}

EdgesCenter::EdgesCenter(__m128i state) noexcept : state(state) {}

EdgesCenter::EdgesCenter() noexcept : EdgesCenter(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) {}

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
    }
}

bool EdgesCenter::is_solved() const
{
    return *this == EdgesCenter();
}

__m128i byte_shuffle(__m128i state, int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9, int i10, int i11) noexcept
{
	return _mm_shuffle_epi8(
		state,
		_mm_set_epi8(15, 14, 13, 12, i11, i10, i9, i8, i7, i6, i5, i4, i3, i2, i1, i0));
}

EdgesCenter EdgesCenter::L1() const
{
    return byte_shuffle(state, 0, 1, 2, 11, 4, 5, 6, 8, 3, 9, 10, 7);
}

EdgesCenter EdgesCenter::L2() const
{
    return byte_shuffle(state, 0, 1, 2, 7, 4, 5, 6, 3, 11, 9, 10, 8);
}

EdgesCenter EdgesCenter::L3() const
{
    return byte_shuffle(state, 0, 1, 2, 8, 4, 5, 6, 11, 7, 9, 10, 3);
}

EdgesCenter EdgesCenter::R1() const
{
    return byte_shuffle(state, 0, 9, 2, 3, 4, 10, 6, 7, 8, 5, 1, 11);
}

EdgesCenter EdgesCenter::R2() const
{
    return byte_shuffle(state, 0, 5, 2, 3, 4, 1, 6, 7, 8, 10, 9, 11);
}

EdgesCenter EdgesCenter::R3() const
{
    return byte_shuffle(state, 0, 10, 2, 3, 4, 9, 6, 7, 8, 1, 5, 11);
}

EdgesCenter EdgesCenter::U1() const
{
    return byte_shuffle(state, 1, 2, 3, 0, 4, 5, 6, 7, 8, 9, 10, 11);
}

EdgesCenter EdgesCenter::U2() const
{
    return byte_shuffle(state, 2, 3, 0, 1, 4, 5, 6, 7, 8, 9, 10, 11);
}

EdgesCenter EdgesCenter::U3() const
{
    return byte_shuffle(state, 3, 0, 1, 2, 4, 5, 6, 7, 8, 9, 10, 11);
}

EdgesCenter EdgesCenter::D1() const
{
    return byte_shuffle(state, 0, 1, 2, 3, 7, 4, 5, 6, 8, 9, 10, 11);
}

EdgesCenter EdgesCenter::D2() const
{
    return byte_shuffle(state, 0, 1, 2, 3, 6, 7, 4, 5, 8, 9, 10, 11);
}

EdgesCenter EdgesCenter::D3() const
{
    return byte_shuffle(state, 0, 1, 2, 3, 5, 6, 7, 4, 8, 9, 10, 11);
}

EdgesCenter EdgesCenter::F1() const
{
    const __m128i F_mask = _mm_set_epi8(0, 0, 0, 0, 0, 0, 0x80, 0x80, 0, 0, 0, 0x80, 0, 0, 0, 0x80);
    auto s = byte_shuffle(state, 8, 1, 2, 3, 9, 5, 6, 7, 4, 0, 10, 11);
    return _mm_xor_si128(s, F_mask);
}

EdgesCenter EdgesCenter::F2() const
{
    return byte_shuffle(state, 4, 1, 2, 3, 0, 5, 6, 7, 9, 8, 10, 11);
}

EdgesCenter EdgesCenter::F3() const
{
    const __m128i F_mask = _mm_set_epi8(0, 0, 0, 0, 0, 0, 0x80, 0x80, 0, 0, 0, 0x80, 0, 0, 0, 0x80);
    auto s = byte_shuffle(state, 9, 1, 2, 3, 8, 5, 6, 7, 0, 4, 10, 11);
    return _mm_xor_si128(s, F_mask);
}

EdgesCenter EdgesCenter::B1() const
{
    const __m128i B_mask = _mm_set_epi8(0, 0, 0, 0, 0x80, 0x80, 0, 0, 0, 0x80, 0, 0, 0, 0x80, 0, 0);
    auto s = byte_shuffle(state, 0, 1, 10, 3, 4, 5, 11, 7, 8, 9, 6, 2);
    return _mm_xor_si128(s, B_mask);
}

EdgesCenter EdgesCenter::B2() const
{
    return byte_shuffle(state, 0, 1, 6, 3, 4, 5, 2, 7, 8, 9, 11, 10);
}

EdgesCenter EdgesCenter::B3() const
{
    const __m128i B_mask = _mm_set_epi8(0, 0, 0, 0, 0x80, 0x80, 0, 0, 0, 0x80, 0, 0, 0, 0x80, 0, 0);
    auto s = byte_shuffle(state, 0, 1, 11, 3, 4, 5, 10, 7, 8, 9, 2, 6);
    return _mm_xor_si128(s, B_mask);
}

EdgesCenter EdgesCenter::twisted(Twist r) const
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

EdgesCenter EdgesCenter::twisted(const std::vector<Twist>& twists) const
{
    EdgesCenter e = *this;
    for (auto t : twists)
        e = e.twisted(t);
    return e;
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
	return prm_index() * 2'048 + ori_index();
}

uint64_t EdgesCenter::hash() const
{
	std::hash<uint64_t> h;
    uint64_t lo = _mm_extract_epi64(state, 0);
    uint64_t hi = _mm_extract_epi64(state, 1);
	uint64_t ret = h(lo) + 0x9E3779B9;
	ret ^= h(hi) + 0x9E3779B9 + (ret << 6) + (ret >> 2);
	return ret;
}

std::string to_string(EdgesCenter edges)
{
    auto e = [edges](uint8_t i)
        {
            std::string s = std::to_string(edges.cubie(i));
            return std::string(2 - s.length(), ' ') + s;
        };
    auto o = [edges](uint8_t i)
        { return std::to_string(edges.orientation(i)); };

    //     +----2----+         +----0----+
    //    /|        /|        /|        /|
    //   3 11      1 10      0 0       0 0
    //  +----0----+  |      +----0----+  |
    //  |  |      |  |      |  |      |  |
    //  |  +----6-|--+      |  +----0-|--+
    //  8 /       9 /       0 /       0 /
    //  |7        |5        |0        |0
    //  +----4----+         +----0----+
    std::ostringstream oss;
    oss << "       Edge             Orientation\n"
        << "    +---" << e(2) << "----+         +----" << o(2) << "----+\n"
        << "   /|        /|        /|        /|\n"
        << " " << e(3) << " " << e(11) << "     " << e(1) << " " << e(10) << "      " << o(3) << " " << o(11) << "       " << o(1) << " " << o(10) << "\n"
        << " +---" << e(0) << "----+  |      +----" << o(0) << "----+  |\n"
        << " |  |      |  |      |  |      |  |\n"
        << " |  +---" << e(6) << "-|--+      |  +----" << o(6) << "-|--+\n"
        << e(8) << "  /     " << e(9) << " /       " << o(8) << " /       " << o(9) << " /\n"
        << " |" << e(7) << "       |" << e(5) << "       |" << o(7) << "        |" << o(5) << "\n"
        << " +---" << e(4) << "----+         +----" << o(4) << "----+\n";
    return oss.str();
}
