#pragma once
#include "intrin.h"
#include "twist.h"
#include "Math/math.h"
#include <cstdint>
#include <vector>

class EdgesCenter : public Twistable<EdgesCenter>
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
	__m128i state{ _mm_setzero_si128() };

	EdgesCenter(__m128i state) noexcept : state(state) {}
public:
    static const uint64_t prm_size = factorial(12);
    static const uint64_t ori_size = powi(2, 11);
    static const uint64_t index_size = prm_size * ori_size;
    static const uint64_t ud_slice_location_size = binomial(12, 4);
    static const std::vector<Twist> twists;

	EdgesCenter() noexcept = default;
    EdgesCenter(
        uint8_t e0, uint8_t e1, uint8_t e2, uint8_t e3,
        uint8_t e4, uint8_t e5, uint8_t e6, uint8_t e7,
        uint8_t e8, uint8_t e9, uint8_t e10, uint8_t e11,
        uint8_t o0, uint8_t o1, uint8_t o2, uint8_t o3,
        uint8_t o4, uint8_t o5, uint8_t o6, uint8_t o7,
        uint8_t o8, uint8_t o9, uint8_t o10, uint8_t o11) noexcept;
    static EdgesCenter solved();
    static EdgesCenter impossible();

    bool operator==(const EdgesCenter&) const;
    bool operator!=(const EdgesCenter&) const;
    bool operator<(const EdgesCenter&) const;

    bool is_solved() const;
    int cubie(int) const;
    int orientation(int) const;

    using Twistable::twisted;
    EdgesCenter twisted(Twist) const override;

    uint64_t prm_index() const;
    uint64_t ori_index() const;
    uint64_t index() const;
    uint64_t ud_slice_location_index() const;
	uint64_t hash() const;
};

std::string to_string(const EdgesCenter&);

namespace std
{
    template <>
	struct hash<EdgesCenter>
	{
		size_t operator()(const EdgesCenter& c) const
		{
			return c.hash();
		}
	};
}
