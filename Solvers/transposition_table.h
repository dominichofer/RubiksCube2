#pragma once
#include "Cube/cube.h"
#include <array>
#include <mutex>
#include <optional>
#include <shared_mutex>

template <typename Cube, typename Value>
struct Bucket
{
	Cube cube;
	Value value;
};

template <typename Cube, typename Value>
class TranspositionTable
{
	mutable std::array<std::shared_mutex, 256> mutexes;
	std::vector<Bucket<Cube, Value>> buckets;
	Bucket<Cube, Value> sentinel;
public:
	TranspositionTable(std::size_t size, const Cube& sentinel_cube, const Value& sentinel_value)
		: buckets(size, { sentinel_cube, sentinel_value }), sentinel{ sentinel_cube, sentinel_value }
	{}

	void insert(const Cube& cube, const Value& value)
	{
		auto index = cube.hash() % buckets.size();
		std::unique_lock lock(mutexes[index % mutexes.size()]);
		buckets[index] = { cube, value };
	}

	std::optional<Value> lookup(const Cube& cube) const
	{
		auto index = cube.hash() % buckets.size();
		std::shared_lock lock(mutexes[index % mutexes.size()]);
		auto& bucket = buckets[index];
		if (bucket.cube == cube)
			return bucket.value;
		return std::nullopt;
	}

	void clear()
	{
		buckets.assign(buckets.size(), sentinel);
	}
};
