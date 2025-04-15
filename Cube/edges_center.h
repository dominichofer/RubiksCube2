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
	EdgesCenter(std::initializer_list<int> edges, std::initializer_list<int> orientations)
		: EdgesCenter(std::vector(edges), std::vector(orientations))
	{}
	EdgesCenter(auto edges, std::initializer_list<int> orientations)
		: EdgesCenter(edges, std::vector(orientations))
	{}
    EdgesCenter(std::initializer_list<int> edges, auto orientations)
        : EdgesCenter(std::vector(edges), orientations)
    {}
    EdgesCenter(auto edges, auto orientations) noexcept
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
