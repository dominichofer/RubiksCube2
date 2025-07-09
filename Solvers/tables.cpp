#include "tables.h"

template <typename T, typename... Args>
const DistanceTable<T>& get_distance_table(const char* filename, Args&&... args)
{
	static DistanceTable<T> table{ std::forward<Args>(args)... };
	static bool initialized = false;
	if (!initialized)
	{
		try
		{
			table.read(filename);
		}
		catch (...)
		{
			table.fill(T::solved());
			table.write(filename);
		}
		initialized = true;
	}
	return table;
}

const DistanceTable<Cube3x3>& H0_subset_distance_table()
{
	return get_distance_table<Cube3x3>(
		"..\\subset.dst",
		H0::twists,
		[](const Cube3x3& c) { return H0::coset_index(c); },
		[](uint64_t i) { return H0::from_coset(0, i); },
		H0::set_size
	);
}

const DistanceTable<Cube3x3>& H0_coset_distance_table()
{
	return get_distance_table<Cube3x3>(
		"..\\coset.dst",
		Cube3x3::twists,
		[](const Cube3x3& c) { return H0::coset_number(c); },
		[](uint64_t i) { return H0::from_coset(i, 0); },
		H0::cosets
	);
}

const DistanceTable<Corners>& Corners_distance_table()
{
	return get_distance_table<Corners>(
		"..\\corners.dst",
		Corners::twists,
		&Corners::index,
		[](uint64_t i) { return Corners::from_index(i); },
		Corners::index_space
	);
}
