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
        0, 0,
        o11 << 4 | e11,
        o10 << 4 | e10,
        o9 << 4 | e9,
        o8 << 4 | e8,
        o7 << 4 | e7,
        o6 << 4 | e6,
        0, 0,
        o5 << 4 | e5,
        o4 << 4 | e4,
        o3 << 4 | e3,
        o2 << 4 | e2,
        o1 << 4 | e1,
        o0 << 4 | e0);
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
    uint64_t lo = _mm_extract_epi64(state, 0);
    uint64_t hi = _mm_extract_epi64(state, 1);
    if (index > 5)
        return hi >> ((index - 6) * 8) & 0x0F;
    else
        return lo >> (index * 8) & 0x0F;
}

int EdgesCenter::orientation(int index) const
{
    uint64_t lo = _mm_extract_epi64(state, 0);
    uint64_t hi = _mm_extract_epi64(state, 1);
    if (index > 5)
        return hi >> ((index - 6) * 8 + 4) & 0x01;
    else
        return lo >> (index * 8 + 4) & 0x01;
}

bool EdgesCenter::is_solved() const
{
    return *this == EdgesCenter();
}

__m128i byte_shuffle(__m128i state, int index_0, int index_1, int index_2, int index_3, int index_4, int index_5, int index_6, int index_7, int index_8, int index_9, int index_10, int index_11)
{
    return _mm_shuffle_epi8(
        state,
        _mm_set_epi8(15, 15, index_11, index_10, index_9, index_8, index_7, index_6, 15, 15, index_5, index_4, index_3, index_2, index_1, index_0));
}

const __m128i F_mask = _mm_set_epi8(0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10);
const __m128i B_mask = _mm_set_epi8(0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00);

EdgesCenter EdgesCenter::L1() const
{
    return byte_shuffle(state, 0, 1, 2, 13, 4, 5, 8, 10, 3, 11, 12, 9);
}

EdgesCenter EdgesCenter::L2() const
{
    return byte_shuffle(state, 0, 1, 2, 9, 4, 5, 8, 3, 13, 11, 12, 10);
}

EdgesCenter EdgesCenter::L3() const
{
    return byte_shuffle(state, 0, 1, 2, 10, 4, 5, 8, 13, 9, 11, 12, 3);
}

EdgesCenter EdgesCenter::R1() const
{
    return byte_shuffle(state, 0, 11, 2, 3, 4, 12, 8, 9, 10, 5, 1, 13);
}

EdgesCenter EdgesCenter::R2() const
{
    return byte_shuffle(state, 0, 5, 2, 3, 4, 1, 8, 9, 10, 12, 11, 13);
}

EdgesCenter EdgesCenter::R3() const
{
    return byte_shuffle(state, 0, 12, 2, 3, 4, 11, 8, 9, 10, 1, 5, 13);
}

EdgesCenter EdgesCenter::U1() const
{
    return byte_shuffle(state, 1, 2, 3, 0, 4, 5, 8, 9, 10, 11, 12, 13);
}

EdgesCenter EdgesCenter::U2() const
{
    return byte_shuffle(state, 2, 3, 0, 1, 4, 5, 8, 9, 10, 11, 12, 13);
}

EdgesCenter EdgesCenter::U3() const
{
    return byte_shuffle(state, 3, 0, 1, 2, 4, 5, 8, 9, 10, 11, 12, 13);
}

EdgesCenter EdgesCenter::D1() const
{
    return byte_shuffle(state, 0, 1, 2, 3, 9, 4, 5, 8, 10, 11, 12, 13);
}

EdgesCenter EdgesCenter::D2() const
{
    return byte_shuffle(state, 0, 1, 2, 3, 8, 9, 4, 5, 10, 11, 12, 13);
}

EdgesCenter EdgesCenter::D3() const
{
    return byte_shuffle(state, 0, 1, 2, 3, 5, 8, 9, 4, 10, 11, 12, 13);
}

EdgesCenter EdgesCenter::F1() const
{
    auto s = byte_shuffle(state, 10, 1, 2, 3, 11, 5, 8, 9, 4, 0, 12, 13);
    return _mm_xor_si128(s, F_mask);
}

EdgesCenter EdgesCenter::F2() const
{
    return byte_shuffle(state, 4, 1, 2, 3, 0, 5, 8, 9, 11, 10, 12, 13);
}

EdgesCenter EdgesCenter::F3() const
{
    auto s = byte_shuffle(state, 11, 1, 2, 3, 10, 5, 8, 9, 0, 4, 12, 13);
    return _mm_xor_si128(s, F_mask);
}

EdgesCenter EdgesCenter::B1() const
{
    auto s = byte_shuffle(state, 0, 1, 12, 3, 4, 5, 13, 9, 10, 11, 8, 2);
    return _mm_xor_si128(s, B_mask);
}

EdgesCenter EdgesCenter::B2() const
{
    return byte_shuffle(state, 0, 1, 8, 3, 4, 5, 2, 9, 10, 11, 13, 12);
}

EdgesCenter EdgesCenter::B3() const
{
    auto s = byte_shuffle(state, 0, 1, 13, 3, 4, 5, 12, 9, 10, 11, 2, 8);
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
    uint64_t lo = _mm_extract_epi64(state, 0);
    uint64_t hi = _mm_extract_epi64(state, 1);
	int e0 = lo & 0x0F;
	int e1 = lo >> 8 & 0x0F;
	int e2 = lo >> 16 & 0x0F;
	int e3 = lo >> 24 & 0x0F;
	int e4 = lo >> 32 & 0x0F;
	int e5 = lo >> 40 & 0x0F;
	int e6 = hi & 0x0F;
	int e7 = hi >> 8 & 0x0F;
	int e8 = hi >> 16 & 0x0F;
	int e9 = hi >> 24 & 0x0F;
	int e10 = hi >> 32 & 0x0F;
	int e11 = hi >> 40 & 0x0F;
	return permutation_index(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11);
}

uint64_t EdgesCenter::ori_index() const
{
    uint64_t lo = _mm_extract_epi64(state, 0);
    uint64_t hi = _mm_extract_epi64(state, 1);
    uint64_t index_0 = _pext_u64(lo, 0x00'00'10'10'10'10'10'10ULL);
    uint64_t index_1 = _pext_u64(hi, 0x00'00'00'10'10'10'10'10ULL);
    return index_0 | (index_1 << 6);
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
