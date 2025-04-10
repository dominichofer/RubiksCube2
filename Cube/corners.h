#pragma once
#include "twist.h"
#include "Math/math.h"
#include <array>
#include <cstdint>
#include <vector>
#include <string>

class Corners : public Twistable<Corners>
{
    //   2 - 3
    //  /   /|
    // 0 - 1 |
    // | 6 | 7
    // 4 - 5/
    uint64_t state{ 0 };

    Corners(uint64_t state) noexcept : state(state) {}
public:
	static const uint64_t prm_size = factorial(8);
	static const uint64_t ori_size = powi(3, 7);
    static const uint64_t index_size = prm_size * ori_size;
    static const std::vector<Twist> twists;

    static std::array<uint8_t, 8> from_prm_index(uint64_t);
    static std::array<uint8_t, 8> from_ori_index(uint64_t);

	Corners() noexcept = default;
	Corners(std::initializer_list<int> corners, std::initializer_list<int> orientations)
        : Corners(std::vector(corners), std::vector(orientations))
    {}
	Corners(auto corners, std::initializer_list<int> orientations)
		: Corners(corners, std::vector(orientations))
	{}
	Corners(std::initializer_list<int> corners, auto orientations)
		: Corners(std::vector(corners), orientations)
	{}
    Corners(auto corners, auto orientations)
    {
        state = 0;
        for (int i = 0; i < 8; i++)
            state += static_cast<uint64_t>(orientations[i] << 4 | corners[i]) << (i * 8);
    }

    static Corners solved();
	static Corners impossible();

    auto operator<=>(const Corners&) const = default;

    bool is_solved() const;
    uint8_t cubie(int) const;
    uint8_t orientation(int) const;
    std::array<uint8_t, 8> cubies() const;
	std::array<uint8_t, 8> orientations() const;

    using Twistable::twisted;
    Corners twisted(Twist) const override;

    uint64_t prm_index() const;
    uint64_t ori_index() const;
    uint64_t index() const;
    uint64_t hash() const;
};

std::string to_string(const Corners&);

namespace std
{
	template <>
	struct hash<Corners>
	{
		size_t operator()(const Corners& c) const
		{
			return c.hash();
		}
	};
}