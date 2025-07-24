#include "Solvers/solvers.h"
#include <iostream>
#include <chrono>

void time(auto func, const std::string& name)
{
	auto start = std::chrono::high_resolution_clock::now();
	const auto& table = func();
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	std::cout << name << " took " << elapsed.count() << " seconds." << std::endl;

	for (int i = 0; i <= 20; i++)
	{
		auto count = std::ranges::count(table, i);
		if (count == 0)
			break;
		std::cout << "Distance " << i << ": " << count << " cubes." << std::endl;
	}
}

static DistanceTable some_table(all_twists, EdgesCenter::slice_loc_size);

const DistanceTable& some_table_fill()
{
	some_table.fill(
		EdgesCenter{},
		[](const EdgesCenter& c) { return c.slice_loc_index(); },
		[](uint16_t i) { return EdgesCenter::from_index(0, 0, i, 0); }
	);
	return some_table;
}

int main()
{
	time(&some_table_fill, "c_ori distance table generation");
	time(&Corners_distance_table, "Corners distance table generation");
	time(&H0_solution_distance_table, "H0 solution distance table generation");
	time(&H0_subset_distance_table, "H0 subset distance table generation");
}

// c_ori
//Distance 0: 1 cubes.
//Distance 1 : 4 cubes.
//Distance 2 : 34 cubes.
//Distance 3 : 186 cubes.
//Distance 4 : 816 cubes.
//Distance 5 : 1018 cubes.
//Distance 6 : 128 cubes.

// c_prm
//Distance 0 : 1 cubes.
//Distance 1 : 18 cubes.
//Distance 2 : 243 cubes.
//Distance 3 : 2646 cubes.
//Distance 4 : 12516 cubes.
//Distance 5 : 17624 cubes.
//Distance 6 : 7080 cubes.
//Distance 7 : 192 cubes.

// c_ori + c_prm
//Distance 00 : 1 cubes.
//Distance 01 : 18 cubes.
//Distance 02 : 243 cubes.
//Distance 03 : 2874 cubes.
//Distance 04 : 28000 cubes.
//Distance 05 : 205416 cubes.
//Distance 06 : 1168516 cubes.
//Distance 07 : 5402628 cubes.
//Distance 08 : 20776176 cubes.
//Distance 09 : 45391616 cubes.
//Distance 10 : 15139616 cubes.
//Distance 11 : 64736 cubes.

// e_ori
//Distance 0: 1 cubes.
//Distance 1 : 2 cubes.
//Distance 2 : 25 cubes.
//Distance 3 : 202 cubes.
//Distance 4 : 620 cubes.
//Distance 5 : 900 cubes.
//Distance 6 : 285 cubes.
//Distance 7 : 13 cubes.

// slice_loc_size
//Distance 0 : 1 cubes.
//Distance 1 : 4 cubes.
//Distance 2 : 50 cubes.
//Distance 3 : 286 cubes.
//Distance 4 : 152 cubes.
//Distance 5 : 2 cubes.

// c_ori + e_ori + e_slice_loc
//Distance 00 : 1 cubes.
//Distance 01 : 4 cubes.
//Distance 02 : 50 cubes.
//Distance 03 : 592 cubes.
//Distance 04 : 7156 cubes.
//Distance 05 : 87236 cubes.
//Distance 06 : 1043817 cubes.
//Distance 07 : 12070278 cubes.
//Distance 08 : 124946368 cubes.
//Distance 09 : 821605960 cubes.
//Distance 10 : 1199128738 cubes.
//Distance 11 : 58202444 cubes.
//Distance 12 : 476 cubes.