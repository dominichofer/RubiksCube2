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
		, coset(H1::set_size)
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
		int64_t size = static_cast<int64_t>(H1::set_size);

		#pragma omp parallel for
		for (int64_t i = 0; i < size / 10; i++)
		{
			if (phase_2[i] + twists_count > max_solution_length)
				continue; // skip cubes that cannot be covered with this many twists
			Cube3x3 subset_cube = H1::from_subset(i);
			Cube3x3 coset_cube = subset_cube.twisted(twists);
			auto index = H1::coset_index(coset_cube);
			coset[index] = true;
		}
		//#pragma omp parallel for
		//for (int64_t ud_edges_prm = 0; ud_edges_prm < factorial(8); ud_edges_prm++)
		//	for (int64_t ud_slice_prm = 0; ud_slice_prm < factorial(4); ud_slice_prm++)
		//	{
		//		int64_t subset_index = ((ud_edges_prm * factorial(4) + ud_slice_prm) * factorial(8) / 2);
		//		std::array<uint8_t, 12> e;
		//		nth_permutation(ud_edges_prm, e.begin(), 8);
		//		nth_permutation(ud_slice_prm, e.begin() + 8, 4);
		//		for (int i = 8; i < 12; i++)
		//			e[i] += 8;
		//		bool even_edges_prm = is_even_permutation(e);
		//		EdgesCenter edges{ e, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

		//		std::array<uint8_t, 8> c;
		//		std::ranges::iota(c, 0);
		//		do
		//		{
		//			if (is_even_permutation(c) != even_edges_prm)
		//				continue;
		//			if (phase_2[subset_index++] + twists_count > max_solution_length)
		//				continue; // skip cubes that cannot be covered with this many twists
		//			Cube3x3 subset_cube{
		//				Corners{ c, { 0, 0, 0, 0, 0, 0, 0, 0 } },
		//				EdgesCenter{ e, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } }
		//			};
		//			Cube3x3 coset_cube = subset_cube.twisted(twists);
		//			int64_t coset_index = H1::coset_index(coset_cube);
		//			coset[coset_index] = true;
		//		} while (std::next_permutation(c.begin(), c.end()));
		//	}
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		uint64_t covered_count = std::ranges::count(coset, true);
		std::cout << "Covering coset " << coset_number << " with "
			<< (int)twists_count << " twists took " << duration << " ms, "
			<< "covered count: " << covered_count << ", %: " << covered_count * 100.0 / size << std::endl;
	}

	void search(const Cube3x3& cube, uint8_t phase1_depth)
	{
		if (phase1_depth == 0)
		{
			if (H1::in_subset(cube))
				cover_with(inversed(stack));
			return;
		}

		if (phase_1[cube] > phase1_depth)
			return;

		for (Twist t : (phase1_depth == 1 ? H1::non_twists : Cube3x3::twists))
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
		Cube3x3 cube = H1::from_coset(coset_number, 0);
		search(cube, depth);
	}
};



int main()
{
	CosetCover set{ 20 };
	for (int nr = 0; nr < H1::cosets; nr++)
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
