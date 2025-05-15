#pragma once
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <vector>

template <std::ranges::random_access_range Range>
class MutexedAccess
{
	mutable std::vector<std::shared_mutex> mutexes;
	Range& data;
	using value_type = typename std::remove_reference_t<Range>::value_type;
public:
	MutexedAccess(Range& data, std::size_t mutexes = std::thread::hardware_concurrency())
		: data(data), mutexes(mutexes)
	{
		if (mutexes == 0)
			throw std::invalid_argument("mutexes must be > 0");
	}

	void store(std::size_t index, value_type desired)
	{
		std::unique_lock lock{ mutexes[index % mutexes.size()] };
		data[index] = std::move(desired);
	}

	value_type load(std::size_t index) const
	{
		std::shared_lock lock{ mutexes[index % mutexes.size()] };
		return data[index];
	}
};
