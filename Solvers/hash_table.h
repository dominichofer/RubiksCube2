#pragma once
#include "Cube/cube.h"
#include <array>
#include <mutex>
#include <optional>
#include <shared_mutex>

template <typename Key, typename Value>
struct Bucket
{
	Key key;
	Value value;
};

template <typename Key, typename Value>
class HashTable
{
	mutable std::array<std::shared_mutex, 256> mutexes;
	std::vector<Bucket<Key, Value>> buckets;
	Bucket<Key, Value> sentinel;
public:
	HashTable() = default;
	HashTable(std::size_t size, const Key& sentinel_key, const Value& sentinel_value = Value{})
		: buckets(size, { sentinel_key, sentinel_value }), sentinel{ sentinel_key, sentinel_value }
	{}
	HashTable(const HashTable& o)
	{
		buckets = o.buckets;
		sentinel = o.sentinel;
	}
	HashTable(HashTable&& o) noexcept
	{
		buckets = std::move(o.buckets);
		sentinel = std::move(o.sentinel);
	}
	HashTable& operator=(const HashTable& o)
	{
		buckets = o.buckets;
		sentinel = o.sentinel;
		return *this;
	}
	HashTable& operator=(HashTable&& o) noexcept
	{
		buckets = std::move(o.buckets);
		sentinel = std::move(o.sentinel);
		return *this;
	}

	void insert(Key key, Value value)
	{
		auto index = std::hash<Key>{}(key) % buckets.size();
		std::unique_lock lock{ mutexes[index % mutexes.size()] };
		buckets[index] = { std::move(key), std::move(value) };
	}

	std::optional<Value> lookup(const Key& key) const
	{
		auto index = std::hash<Key>{}(key) % buckets.size();
		std::shared_lock lock{ mutexes[index % mutexes.size()] };
		auto& bucket = buckets[index];
		if (bucket.key == key)
			return bucket.value;
		return std::nullopt;
	}

	void clear()
	{
		buckets.assign(buckets.size(), sentinel);
	}
};
