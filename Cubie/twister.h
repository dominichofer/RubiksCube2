#pragma once
#include "twist.h"
#include <array>
#include <cstdint>
#include <functional>
#include <utility>
#include <vector>

template <typename Cube, typename index_t>
class AllTwister
{
	std::vector<index_t> table;
	std::function<index_t(Cube)> index;
	std::function<Cube(index_t)> from_index;
public:
	AllTwister(
		const Twists& twists,
		std::function<index_t(Cube)> index,
		std::function<Cube(index_t)> from_index,
		std::size_t index_space)
		: table(index_space * twists.size())
		, index(std::move(index))
		, from_index(std::move(from_index))
	{
	}

	void fill()
	{
		const int64_t size = static_cast<int64_t>(table.size());
		#pragma omp parallel for schedule(static, 128)
		for (int64_t i = 0; i < size; i++)
			for (Twist t : all_twists)
				table[i * all_twists.size() + std::to_underlying(t)] = index(from_index(i).twisted(t));
	}

	index_t operator()(index_t i, Twist t) const
	{
		return table[i * all_twists.size() + std::to_underlying(t)];
	}
};
