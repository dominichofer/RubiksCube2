#pragma once
#include "Cube/cube.h"
#include "neighbours.h"
#include <algorithm>
#include <optional>
#include <vector>

template <typename Cube>
class CloseSolutionTable
{
	struct CubeAndTwists
	{
		Cube cube;
		std::vector<typename Cube::Twist> twists;

		bool operator<(const CubeAndTwists& o) const { return cube < o.cube; }
	};

	uint64_t index(const Cube& c) const { return c.hash() % size; }

	int max_distance_;
	std::size_t size;
	std::vector<std::vector<CubeAndTwists>> bins;
public:
	explicit CloseSolutionTable(int max_distance, std::size_t size)
		: max_distance_(max_distance), size(size)
	{
		bins.resize(size);
		auto map = neighbours(Cube{}, 0, max_distance);
		for (const auto& [cube, twists] : map)
			bins[index(cube)].push_back({ cube, inversed(twists) });
		for (auto& m : bins)
			std::sort(m.begin(), m.end());
	}

	std::optional<std::vector<typename Cube::Twist>> operator[](const Cube& c) const
	{
		auto& m = bins[index(c)];
		auto it = std::lower_bound(m.begin(), m.end(), CubeAndTwists{ c, {} });
		if (it == m.end() || it->cube != c)
			return std::nullopt;
		return it->twists;
	}

	int max_distance() const { return max_distance_; }

	std::size_t largest_bin_size() const
	{
		return std::max_element(bins.begin(), bins.end(), [](const auto& a, const auto& b) { return a.size() < b.size(); })->size();
	}
};
