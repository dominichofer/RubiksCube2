#pragma once
#include <functional>
#include <optional>
#include <stdexcept>
#include <vector>

template <typename Key, typename Value>
class HashTable
{
	struct Bucket
	{
		Key key;
		Value value;
	};
	std::vector<Bucket> buckets;
	Bucket sentinel;
public:
	HashTable() = default;
	HashTable(std::size_t size, const Key& sentinel_key, const Value& sentinel_value)
		: buckets(size, { sentinel_key, sentinel_value })
		, sentinel({ sentinel_key, sentinel_value })
	{
	}

	void insert(Key key, Value value)
	{
		std::size_t index = std::hash<Key>{}(key) % buckets.size();
		buckets[index] = { std::move(key), std::move(value) };
	}

	template <class Compare = std::less<Value>>
	void insert_if_less(const Key& key, const Value& value, Compare comp = {})
	{
		std::size_t index = std::hash<Key>{}(key) % buckets.size();
		Bucket& data = buckets[index];
		if (comp(value, data.value)) // new < old
			data = { key, value };
	}

	template <class Compare = std::less<Value>>
	void insert_if_less_eq(const Key& key, const Value& value, Compare comp = {})
	{
		return insert_if_less(key, value, [&comp](const Value& a, const Value& b) { return !comp(b, a); });
	}

	template <class Compare = std::less<Value>>
	void insert_if_greater(const Key& key, const Value& value, Compare comp = {})
	{
		return insert_if_less(key, value, [&comp](const Value& a, const Value& b) { return comp(b, a); });
	}

	template <class Compare = std::less<Value>>
	void insert_if_greater_eq(const Key& key, const Value& value, Compare comp = {})
	{
		return insert_if_less(key, value, [&comp](const Value& a, const Value& b) { return !comp(a, b); });
	}

	std::optional<Value> lookup(const Key& key) const
	{
		std::size_t index = std::hash<Key>{}(key) % buckets.size();
		const Bucket& data = buckets[index];
		if (data.key == key)
			return data.value;
		return std::nullopt;
	}

	void clear()
	{
		buckets.assign(buckets.size(), sentinel);
	}
};
