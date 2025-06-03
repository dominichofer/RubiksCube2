#include "tables.h"

const DistanceTable<Cube3x3>& H0_subset_distance_table()
{
	static DistanceTable<Cube3x3> table{
		[](const Cube3x3& c) { return H0::subset_index(c); },
		H0::set_size
	};
	static bool initialized = false;
	if (!initialized)
	{
		try
		{
			table.read("D:\\subset.dst");
		}
		catch (...)
		{
			table.fill(Cube3x3::solved(), H0::twists, [](uint64_t i) { return H0::from_subset(i); });
			table.write("D:\\subset.dst");
		}
		initialized = true;
	}
	return table;
}

const DistanceTable<Cube3x3>& H0_coset_distance_table()
{
	static DistanceTable<Cube3x3> table{
		[](const Cube3x3& c) { return H0::coset_number(c); },
		H0::cosets
	};
	static bool initialized = false;
	if (!initialized)
	{
		try
		{
			table.read("D:\\coset.dst");
		}
		catch (...)
		{
			table.fill(Cube3x3::solved(), Cube3x3::twists, [](uint64_t i) { return H0::from_coset(i, 0); });
			table.write("D:\\coset.dst");
		}
		initialized = true;
	}
	return table;
}
