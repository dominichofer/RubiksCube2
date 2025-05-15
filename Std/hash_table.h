#pragma once
#include "mutexed_access.h"
#include <optional>

template <typename Key, typename Value>
class HashTable
{
	struct Bucket
	{
		Key key;
		Value value;
	};
	std::vector<Bucket> buckets;
	MutexedAccess<std::vector<Bucket>> access{buckets};
	Bucket sentinel;
public:
	HashTable() = default;
	HashTable(std::size_t size, const Key& sentinel_key, const Value& sentinel_value = Value{})
		: buckets(size, { sentinel_key, sentinel_value }), sentinel{ sentinel_key, sentinel_value }
	{}
	//HashTable(const HashTable& o)
	//{
	//	buckets = o.buckets;
	//	sentinel = o.sentinel;
	//}
	//HashTable(HashTable&& o) noexcept
	//{
	//	buckets = std::move(o.buckets);
	//	sentinel = std::move(o.sentinel);
	//}
	//HashTable& operator=(const HashTable& o)
	//{
	//	buckets = o.buckets;
	//	sentinel = o.sentinel;
	//	return *this;
	//}
	//HashTable& operator=(HashTable&& o) noexcept
	//{
	//	buckets = std::move(o.buckets);
	//	sentinel = std::move(o.sentinel);
	//	return *this;
	//}

	void insert(Key key, Value value)
	{
		access.store(std::hash<Key>{}(key) % buckets.size(), { std::move(key), std::move(value) });
	}

	std::optional<Value> lookup(const Key& key) const
	{
		auto bucket = access.load(std::hash<Key>{}(key) % buckets.size());
		if (bucket.key == key)
			return bucket.value;
		return std::nullopt;
	}

	void clear()
	{
		buckets.assign(buckets.size(), sentinel);
	}
};
