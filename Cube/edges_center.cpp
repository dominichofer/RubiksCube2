#include "edges_center.h"
#include "bit.h"
#include "Math/math.h"

const std::vector<Twist> EdgesCenter::twists = {
Twist::L1, Twist::L2, Twist::L3,
Twist::R1, Twist::R2, Twist::R3,
Twist::U1, Twist::U2, Twist::U3,
Twist::D1, Twist::D2, Twist::D3,
Twist::F1, Twist::F2, Twist::F3,
Twist::B1, Twist::B2, Twist::B3
};

EdgesCenter::EdgesCenter(
uint8_t e0, uint8_t e1, uint8_t e2, uint8_t e3, uint8_t e4, uint8_t e5, uint8_t e6, uint8_t e7, uint8_t e8, uint8_t e9, uint8_t e10, uint8_t e11,
uint8_t o0, uint8_t o1, uint8_t o2, uint8_t o3, uint8_t o4, uint8_t o5, uint8_t o6, uint8_t o7, uint8_t o8, uint8_t o9, uint8_t o10, uint8_t o11) noexcept
: EdgesCenter(
{ e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11 },
{ o0, o1, o2, o3, o4, o5, o6, o7, o8, o9, o10, o11 })
{
}

EdgesCenter::EdgesCenter(std::array<uint8_t, 12> edges, std::array<uint8_t, 12> orientations) noexcept
{
state = _mm_set_epi8(
0, 0, 0, 0,
orientations[11] << 7 | edges[11],
orientations[10] << 7 | edges[10],
orientations[9] << 7 | edges[9],
orientations[8] << 7 | edges[8],
orientations[7] << 7 | edges[7],
orientations[6] << 7 | edges[6],
orientations[5] << 7 | edges[5],
orientations[4] << 7 | edges[4],
orientations[3] << 7 | edges[3],
orientations[2] << 7 | edges[2],
orientations[1] << 7 | edges[1],
orientations[0] << 7 | edges[0]);
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
	alignas(16) uint8_t bytes[16];
	_mm_store_si128(reinterpret_cast<__m128i*>(bytes), state);
	return bytes[index];
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

std::array<uint8_t, 12> EdgesCenter::from_prm_index(uint64_t index)
{
std::array<uint8_t, 12> e;
	nth_permutation(index, e);
	return e;
}

std::array<uint8_t, 12> EdgesCenter::from_ori_index(uint64_t index)
{
	std::array<uint8_t, 12> o;
	for (int i = 0; i < 11; i++)
		o[i] = (index >> i) & 0x01;
	o[11] = std::popcount(index) % 2; // parity of the number of 1s in the orientation index
	return o;
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

bool same_permutation(const EdgesCenter& a, const EdgesCenter& b)
{
	return _mm_test_all_zeros(_mm_xor_si128(a.state, b.state), _mm_set1_epi8(0x7F));
}

bool same_orientation(const EdgesCenter& a, const EdgesCenter& b)
{
	return _mm_test_all_zeros(_mm_xor_si128(a.state, b.state), _mm_set1_epi8(0x80));
}

bool same_lr_slice_location(const EdgesCenter& a, const EdgesCenter& b)
{
auto A = _mm_cmplt_epi8(a.state, _mm_set1_epi8(4));
	auto B = _mm_cmplt_epi8(b.state, _mm_set1_epi8(4));
	auto x = _mm_xor_si128(A, B);
	return _mm_test_all_zeros(x, x);
}

bool same_ud_slice_location(const EdgesCenter& a, const EdgesCenter& b)
{
	auto A = _mm_slli_epi64(a.state, 4);
	auto B = _mm_slli_epi64(b.state, 4);
	auto x = _mm_xor_si128(A, B);
	return _mm_test_all_zeros(x, x);
}

bool same_fb_slice_location(const EdgesCenter& a, const EdgesCenter& b)
{
	auto A = _mm_slli_epi64(a.state, 5);
	auto B = _mm_slli_epi64(b.state, 5);
	auto x = _mm_xor_si128(A, B);
	return _mm_test_all_zeros(x, x);
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
