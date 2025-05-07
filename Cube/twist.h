#pragma once
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

enum class Twist : uint8_t
{
	L1, L2, L3, l1, l2, l3,
	R1, R2, R3, r1, r2, r3,
	U1, U2, U3, u1, u2, u3,
	D1, D2, D3, d1, d2, d3,
	F1, F2, F3, f1, f2, f3,
	B1, B2, B3, b1, b2, b3,
	None
};

using Twists = std::vector<Twist>;

template <std::size_t N>
class nTwists
{
	int8_t size_;
	std::array<Twist, N> twists;
public:
	nTwists() noexcept : size_(0) { twists.fill(Twist::None); }
	nTwists(int8_t size) noexcept : size_(size) { twists.fill(Twist::None); }

	const Twist& operator[](int i) const { return twists[i]; }
	      Twist& operator[](int i)       { return twists[i]; }

	auto begin() const { return twists.begin(); }
	auto end() const { return twists.begin() + size_; }

	int8_t size() const { return size_; }

	void append(Twist t) { twists[size_++] = t; }

	void inverse()
	{
		for (int8_t i = 0; i < size_ / 2; ++i)
			std::swap(twists[i], twists[size_ - i - 1]);
		for (int8_t i = 0; i < size_; ++i)
			twists[i] = inversed(twists[i]);
	}
};

static inline std::vector<Twist> all_twists = {
	Twist::L1, Twist::L2, Twist::L3, Twist::l1, Twist::l2, Twist::l3,
	Twist::R1, Twist::R2, Twist::R3, Twist::r1, Twist::r2, Twist::r3,
	Twist::U1, Twist::U2, Twist::U3, Twist::u1, Twist::u2, Twist::u3,
	Twist::D1, Twist::D2, Twist::D3, Twist::d1, Twist::d2, Twist::d3,
	Twist::F1, Twist::F2, Twist::F3, Twist::f1, Twist::f2, Twist::f3,
	Twist::B1, Twist::B2, Twist::B3, Twist::b1, Twist::b2, Twist::b3,
	Twist::None
};

std::string to_string(Twist);

template <std::ranges::range R>
	requires std::same_as<std::ranges::range_value_t<R>, Twist>
std::string to_string(const R& twists)
{
	std::string result;
	for (Twist t : twists)
		result += to_string(t) + " ";
	result.pop_back();
	return result;
}

auto twist_from_string(std::string_view) -> Twist;
auto twists_from_string(std::string_view) -> std::vector<Twist>;


Twist inversed(Twist);

bool same_plane(Twist, Twist);

template <typename Cube, typename Iterator, typename Sentinel>
Cube twisted(const Cube& cube, Iterator begin, Sentinel end)
{
	Cube result = cube;
	for (auto it = begin; it != end; ++it)
		result = result.twisted(*it);
	return result;
}

template <typename Cube>
Cube twisted(const Cube& cube, const std::ranges::range auto& twists)
{
	return twisted(cube, std::ranges::begin(twists), std::ranges::end(twists));
}

template <typename Derived>
class Twistable
{
public:
	template <typename Iterator, typename Sentinel>
	Derived twisted(Iterator begin, Sentinel end) const
	{
		auto cube = static_cast<const Derived&>(*this);
		for (auto it = begin; it != end; ++it)
			cube = cube.twisted(*it);
		return cube;
	}

	Derived twisted(const std::ranges::range auto& twists) const
	{
		return twisted(twists.begin(), twists.end());
	}

	template <typename... Twists>
	Derived twisted(Twist t, Twists... ts) const
	{
		return twisted(t).twisted(ts...);
	}
}