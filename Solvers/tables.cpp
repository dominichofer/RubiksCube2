#include "tables.h"

template <typename Cube, typename F1, typename F2>
const DistanceTable& get_distance_table(
	const char* filename,
	Twists twists,
	const Cube& origin,
	F1 index,
	F2 from_index,
	std::size_t index_space)
{
	static DistanceTable table{ std::move(twists), index_space };
	static bool initialized = false;
	if (!initialized)
	{
		try
		{
			table.read(filename);
		}
		catch (...)
		{
			table.fill(origin, index, from_index);
			table.write(filename);
		}
		initialized = true;
	}
	return table;
}

const DistanceTable& Corners_distance_table()
{
	return get_distance_table(
		"..\\corners.dst",
		all_twists,
		Corners{},
		[](const Corners& c) { return c.index(); },
		[](uint32_t i) { return Corners::from_index(i); },
		Corners::size
	);
}

const DistanceTable& H0_solution_distance_table()
{
	return get_distance_table(
		"..\\subset.dst",
		H0::twists,
		SubsetCube{},
		[](const SubsetCube& c) { return c.subset_index(); },
		&SubsetCube::from_subset_index,
		SubsetCube::size
	);
}

const DistanceTable& H0_subset_distance_table()
{
	return get_distance_table(
		"..\\coset.dst",
		all_twists,
		CosetNumberCube{},
		[](const CosetNumberCube& c) { return c.coset_number(); },
		&CosetNumberCube::from_coset_number,
		CosetNumberCube::size
	);
}
