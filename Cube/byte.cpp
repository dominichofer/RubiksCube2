#include "byte.h"
#include <intrin.h>

uint64_t set_epi8(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7)
{
    __m128i packed = _mm_setr_epi8(
        b0, b1, b2, b3, b4, b5, b6, b7,
        0, 0, 0, 0, 0, 0, 0, 0
    );
    return _mm_cvtsi128_si64(packed);
}

uint8_t extract_epi8(uint64_t packed, int index)
{
	return static_cast<uint8_t>(packed >> (index * 8));
}

uint64_t byte_shuffle(uint64_t b, int b0, int b1, int b2, int b3, int b4, int b5, int b6, int b7)
{
	__m128i x = _mm_shuffle_epi8(
		_mm_cvtsi64_si128(b),
		_mm_setr_epi8(
			b0, b1, b2, b3, b4, b5, b6, b7,
			0, 0, 0, 0, 0, 0, 0, 0
		)
	);
	return _mm_cvtsi128_si64(x);
}

std::pair<uint64_t, uint64_t> byte_shuffle(
	uint64_t a, uint64_t b,
	int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7,
	int b0, int b1, int b2, int b3, int b4, int b5, int b6, int b7)
{
	__m128i x = _mm_shuffle_epi8(
		_mm_setr_epi64x(a, b),
		_mm_setr_epi8(
			a0, a1, a2, a3, a4, a5, a6, a7,
			b0, b1, b2, b3, b4, b5, b6, b7
		)
	);
	return { _mm_cvtsi128_si64(x), _mm_cvtsi128_si64(_mm_srli_si128(x, 8)) };
}
