#pragma once
#include <utility>
#include <vector>

template <typename Twist>
Twist inversed(Twist twist)
{
	auto div = std::to_underlying(twist) / 3;
	auto mod = std::to_underlying(twist) % 3;
	return static_cast<Twist>(div * 3 + 2 - mod);
}

template <typename Twist>
std::vector<Twist> inversed(const std::vector<Twist>& twists)
{
	std::vector<Twist> r;
	r.reserve(twists.size());
	for (auto it = twists.rbegin(); it != twists.rend(); ++it)
		r.push_back(inversed(*it));
	return r;
}
