#include "Solvers/solvers.h"
#include <iostream>
#include <vector>
#include <intrin0.h>

static void const volatile* volatile global_force_escape_pointer;

// FIXME: Verify if LTO still messes this up?
void UseCharPointer(char const volatile* const v) {
	// We want to escape the pointer `v` so that the compiler can not eliminate
	// computations that produced it. To do that, we escape the pointer by storing
	// it into a volatile variable, since generally, volatile store, is not
	// something the compiler is allowed to elide.
	global_force_escape_pointer = reinterpret_cast<void const volatile*>(v);
}

template <class Tp>
inline void DoNotOptimize(Tp const& value) {
	UseCharPointer(&reinterpret_cast<char const volatile&>(value));
	_ReadWriteBarrier();
}

int main()
{
	unsigned long long min_time = 10000;
	int min_size = 0;

	for (int size = 10000000; size <= 1'000'000'000; size += 10000000)
	{
		const CloseSolutionTable<Cube3x3> table(7, size);

		std::vector<Cube3x3> hit_cubes;
		for (int dst = 0; dst <= table.max_distance(); dst++)
			for (const Cube3x3& cube : cube3x3_of_distance[dst])
				hit_cubes.push_back(cube);

		std::vector<Cube3x3> miss_cubes;
		for (int dst = table.max_distance() + 1; dst < cube3x3_of_distance.size(); dst++)
			for (const Cube3x3& cube : cube3x3_of_distance[dst])
				miss_cubes.push_back(cube);

		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 100; i++)
			for (const Cube3x3& cube : hit_cubes)
				DoNotOptimize(table[cube]);
		auto stop = std::chrono::high_resolution_clock::now();
		auto avg_hit = (stop - start) / hit_cubes.size();

		start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 100; i++)
			for (const Cube3x3& cube : miss_cubes)
				DoNotOptimize(table[cube]);
		stop = std::chrono::high_resolution_clock::now();
		auto avg_miss = (stop - start) / miss_cubes.size();

		auto avg = avg_hit + avg_miss;
		if (avg.count() / 100 < min_time)
		{
			min_time = avg.count() / 100;
			min_size = size;
			std::cout << min_time << " " << min_size << std::endl;
		}
	}
}