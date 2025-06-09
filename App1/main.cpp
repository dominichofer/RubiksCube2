#include "Solvers/solvers.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <ranges>

class CosetCover
{
	const DistanceTable<Cube3x3> &phase_1, &phase_2;
	std::vector<bool> coset;
	Twists stack;
	int64_t coset_number;
	uint8_t max_solution_length;
public:

	CosetCover(uint8_t max_solution_length)
		: phase_1(H0_coset_distance_table())
		, phase_2(H0_subset_distance_table())
		, coset(H0::set_size)
		, max_solution_length(max_solution_length)
	{}

	void reset(int64_t coset_number)
	{
		this->coset_number = coset_number;
		std::ranges::fill(coset, false);
	}

	void cover_with(const Twists& twists)
	{
		auto start = std::chrono::high_resolution_clock::now();
		uint8_t twists_count = static_cast<uint8_t>(twists.size());
		int64_t size = static_cast<int64_t>(H0::set_size);
		#pragma omp parallel for
		for (int64_t i = 0; i < size; i++)
		{
			if (phase_2[i] + twists_count > max_solution_length)
				continue; // skip cubes that cannot be covered with this many twists
			Cube3x3 subset_cube = H0::from_subset(i);
			Cube3x3 coset_cube = subset_cube.twisted(twists);
			auto index = H0::coset_index(coset_cube);
			coset[index] = true;
		}
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		uint64_t covered_count = std::ranges::count(coset, true);
		uint64_t uncovered_count = size - covered_count;
		std::cout << "Covering coset " << coset_number << " with " << (int)twists_count
				  << " twists took " << duration << " ms, covered count: "
			<< covered_count << ", uncovered count: " << uncovered_count << std::endl;
	}

	void search(const Cube3x3& cube, uint8_t phase1_depth)
	{
		if (phase1_depth == 0)
		{
			if (H0::in_subset(cube))
				cover_with(inversed(stack));
			return;
		}

		if (phase_1[cube] > phase1_depth)
			return;

		for (Twist t : (phase1_depth == 1 ? H0::non_twists : Cube3x3::twists))
		{
			if ((not stack.empty()) and same_plane(t, stack.back()))
				continue;
			stack.push_back(t);
			search(cube.twisted(t), phase1_depth - 1);
			stack.pop_back();
		}
	}

	void cover(uint8_t depth)
	{
		Cube3x3 cube = H0::from_coset(coset_number, 0);
		search(cube, depth);
	}
};



int main()
{
	CosetCover set{ 20 };
	for (int nr = 0; nr < H0::cosets; nr++)
	{
		set.reset(nr);
		for (int i = 0; i < 10; i++)
		{
			auto start = std::chrono::high_resolution_clock::now();
			set.cover(i);
			auto end = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
			std::cout << "Covering coset " << nr << " with depth " << i
				<< " took " << duration << " ms" << std::endl;
		}
	}
}
