#include "tables.h"

const DistanceTable<Cube3x3>& H0_subset_distance_table()
{
	static DistanceTable<Cube3x3> table {
		H0::twists,
		&H0::subset_index,
		&H0::from_subset,
		H0::set_size
	};
	static bool initialized = false;
	if (!initialized)
	{
		try
		{
			table.read("..\\subset.dst");
		}
		catch (...)
		{
			table.fill(Cube3x3::solved());
			table.write("..\\subset.dst");
		}
		initialized = true;
	}
	return table;
}

const DistanceTable<Cube3x3>& H0_coset_distance_table()
{
	static DistanceTable<Cube3x3> table {
		Cube3x3::twists,
		&H0::coset_number,
		[](uint64_t i) { return H0::from_coset(i, 0); },
		H0::cosets
	};
	static bool initialized = false;
	if (!initialized)
	{
		try
		{
			table.read("..\\coset.dst");
		}
		catch (...)
		{
			table.fill(Cube3x3::solved());
			table.write("..\\coset.dst");
		}
		initialized = true;
	}
	return table;
}
