#pragma once
#include "intrin.h"
#include "twist.h"
#include "Math/math.h"
#include <array>
#include <cstdint>
#include <vector>

class EdgesCenter : public Twistable<EdgesCenter>
{
    //     +----1----+
    //    /|        /|
    //   4 11      5 10
    //  +----0----+  |
    //  |  |      |  |
    //  |  +----2-|--+
    //  8 /       9 /
    //  |7        |6
    //  +----3----+
	__m128i state{ _mm_setzero_si128() };

	EdgesCenter(__m128i state) noexcept : state(state) {}

    int byte(int) const;
public:
    static const uint64_t prm_size = factorial(12);
    static const uint64_t ori_size = powi(2, 11);
    static const uint64_t index_space = prm_size * ori_size;
    static const std::vector<Twist> twists;

    static std::array<uint8_t, 12> from_prm_index(uint64_t);
    static std::array<uint8_t, 12> from_ori_index(uint64_t);

	EdgesCenter() noexcept = default;
    EdgesCenter(
        uint8_t e0, uint8_t e1, uint8_t e2, uint8_t e3,
        uint8_t e4, uint8_t e5, uint8_t e6, uint8_t e7,
        uint8_t e8, uint8_t e9, uint8_t e10, uint8_t e11,
        uint8_t o0, uint8_t o1, uint8_t o2, uint8_t o3,
        uint8_t o4, uint8_t o5, uint8_t o6, uint8_t o7,
        uint8_t o8, uint8_t o9, uint8_t o10, uint8_t o11) noexcept;
	EdgesCenter(std::array<uint8_t, 12> edges, std::array<uint8_t, 12> orientations) noexcept;

    static EdgesCenter solved();
    static EdgesCenter impossible();

    bool operator==(const EdgesCenter&) const;
    bool operator!=(const EdgesCenter&) const;
    bool operator<(const EdgesCenter&) const;

    bool is_solved() const;
    uint8_t cubie(int) const;
    uint8_t orientation(int) const;
    std::array<uint8_t, 12> cubies() const;
    std::array<uint8_t, 12> orientations() const;

    using Twistable::twisted;
    EdgesCenter twisted(Twist) const override;

    std::array<uint8_t, 4> lr_slice_location() const;
    std::array<uint8_t, 4> ud_slice_location() const;
    std::array<uint8_t, 4> fb_slice_location() const;

    uint64_t prm_index() const;
    uint64_t ori_index() const;
    uint64_t index() const;
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
