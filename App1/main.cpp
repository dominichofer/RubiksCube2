#include "Solvers/solvers.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <ranges>

class CosetCover
{
	const DistanceTable& phase_1;
	const DistanceTable& phase_2;
	const DistanceTable& corners;
	HashTable<Cube3x3, uint8_t> tt{ 1'000'000, Cube3x3::impossible(), 0 };
	std::vector<bool> coset;
	Twists twists;
	int max_solution_length;
	uint64_t coset_number;
public:

	CosetCover(int max_solution_length)
		: phase_1(H0_subset_distance_table())
		, phase_2(H0_solution_distance_table())
		, corners(Corners_distance_table())
		, coset(Cube3x3::set_size)
		, max_solution_length(max_solution_length)
	{}

	void reset(uint64_t coset_number)
	{
		this->coset_number = coset_number;
		std::ranges::fill(coset, false);
	}

	void cover_with(const Twists& twists)
	{
		auto start = std::chrono::high_resolution_clock::now();
		auto twists_count = twists.size();
		int64_t size = static_cast<int64_t>(coset.size());

		#pragma omp parallel for
		for (uint16_t e_non_slice_prm = 0; e_non_slice_prm < EdgesCenter::non_slice_prm_size; e_non_slice_prm++)
		{
			for (uint8_t e_slice_prm = 0; e_slice_prm < EdgesCenter::slice_prm_size; e_slice_prm++)
			{
				auto coset_cube = Cube3x3{};
				coset_cube.e_slice_prm = e_slice_prm;
				coset_cube.e_non_slice_prm = e_non_slice_prm;
				coset_cube = coset_cube.twisted(twists);

				bool even_edge_prm = is_even_permutation(e_non_slice_prm) xor is_even_permutation(e_slice_prm); // TODO: Add e_slice_loc!
				auto& lookup_table = even_edge_prm ? even_lookup_table : odd_lookup_table;

				for (uint16_t x = 0; x < Corners::prm_size / 2; x++)
				{
					if (phase_2.distance(i) + twists_count > max_solution_length)
						continue;

					uint16_t c_prm = lookup_table[x];
					coset_cube.c_prm = c_prm;
					coset[coset_cube.coset_index()] = true;
				}
			}
		}
		uint8_t e_slice_prm; // 4! = 24
		uint16_t e_non_slice_prm; // 8! = 40'320
		for (int64_t i = 0; i < size; i++)
		{
			if (phase_2.distance(i) + twists_count > max_solution_length)
				continue;
			Cube3x3 subset_cube = Cube3x3::from_subset(i);
			Cube3x3 coset_cube = subset_cube.twisted(twists);
			auto index = coset_cube.coset_index();
			coset[index] = true;
		}
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		uint64_t covered_count = std::ranges::count(coset, true);
		std::cout << "Covering coset " << coset_number << " with "
			<< (int)twists_count << " twists took " << duration << " ms, "
			<< "covered count: " << covered_count << ", %: " << covered_count * 100.0 / size << std::endl;
	}

	void search(const Cube3x3& cube, int p1_depth, Twist last = Twist::None)
	{
		bool in_subset = cube.in_subset();
		if (p1_depth == 0 and in_subset)
			cover_with(inversed(twists));
		if (p1_depth == 0 or in_subset)
			return;

		if (phase_1.distance(cube.coset_number()) > p1_depth)
			return;

		//if (corners.distance(cube.corners_index()) > max_solution_length - twists.size())
		//	return;

		if (tt.lookup(cube).value_or(0) >= p1_depth)
			return;

		for (Twist t : (p1_depth == 1 ? H0::non_twists : all_twists))
		{
			if (same_plane(t, last))
				continue;
			twists.push_back(t);
			search(cube.twisted(t), p1_depth - 1, t);
			twists.pop_back();
		}
	}

	void cover(int depth)
	{
		Cube3x3 cube = Cube3x3::from_coset(coset_number, 0);
		search(cube, depth);
	}
};



int main()
{
	CosetCover set{ 20 };
	for (int nr = 0; nr < Cube3x3::cosets; nr++)
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