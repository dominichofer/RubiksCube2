#include "subset.h"
#include <array>
#include <algorithm>

uint64_t H0::subset_index(const Cube3x3& cube)
{
const auto& c = cube.corners();
const auto& e = cube.edges();
	// The parity of the corner permutation is the same as the parity of the edge permutation; thus '/2'.
uint64_t corner_prm = c.prm_index() / 2;
uint64_t ud_edges_prm = permutation_index(e.cubie(0), e.cubie(1), e.cubie(2), e.cubie(3), e.cubie(4), e.cubie(5), e.cubie(6), e.cubie(7));
	uint64_t ud_slice_prm = permutation_index(e.cubie(8) - 8, e.cubie(9) - 8, e.cubie(10) - 8, e.cubie(11) - 8);
	uint64_t index = corner_prm;
	index = index * factorial(8) + ud_edges_prm;
	index = index * factorial(4) + ud_slice_prm;
	return index;
}

Cube3x3 H0::from_subset(uint64_t index)
{
	uint64_t ud_slice_prm = index % factorial(4);
	index /= factorial(4);
	uint64_t ud_edges_prm = index % factorial(8);
	index /= factorial(8);
	// The parity of the corner permutation is the same as the parity of the edge permutation; thus '*2'.
	uint64_t corner_prm = index * 2;

	std::array<uint8_t, 12> e;
	nth_permutation(ud_edges_prm, e.begin(), 8);
	nth_permutation(ud_slice_prm, e.begin() + 8, 4);
	for (int i = 8; i < 12; i++)
		e[i] += 8;
	auto c = Corners::from_prm_index(corner_prm);
	if (is_even_permutation(c) != is_even_permutation(e))
		std::ranges::next_permutation(c);

	return Cube3x3{
		Corners{ c, { 0, 0, 0, 0, 0, 0, 0, 0 } },
		EdgesCenter{ e, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } }
	};
}

uint64_t H0::coset_number(const Cube3x3& cube)
{
	const auto& c = cube.corners();
	const auto& e = cube.edges();
	uint64_t index = c.ori_index();
	index = index * EdgesCenter::ori_size + e.ori_index();
	index = index * binomial(12, 4) + combination_index(12, e.ud_slice_location());
	return index;
}

uint64_t H0::coset_index(const Cube3x3& cube)
{
	const auto& c = cube.corners();
	const auto& e = cube.edges();
	auto ud = e.ud_slice_location();
	std::vector<uint8_t> rest;
	rest.reserve(8);
	for (uint8_t i = 0; i < 12; i++)
		if (not std::ranges::binary_search(ud, i))
			rest.push_back(e.cubie(i));
	for (uint8_t& loc : ud)
		loc = e.cubie(loc) - 8;
	// The parity of the corner permutation is the same as the parity of the edge permutation; thus '/2'.
	uint64_t index = c.prm_index() / 2;
	index = index * factorial(4) + permutation_index(ud);
	index = index * factorial(8) + permutation_index(rest);
	return index;
}

Cube3x3 H0::from_coset(int64_t number, int64_t index)
{
	int64_t ud_locs = binomial(12, 4);
	int64_t ud_loc_index = number % ud_locs;
	number /= ud_locs;
	int64_t edge_ori = number % EdgesCenter::ori_size;
	number /= EdgesCenter::ori_size;
	int64_t corner_ori = number;

	int64_t rest_prm = index % factorial(8);
	index /= factorial(8);
	int64_t ud_prm = index % factorial(4);
	index /= factorial(4);
	// The parity of the corner permutation is the same as the parity of the edge permutation; thus '*2'.
	int64_t corner_prm = index * 2;

	std::array<uint8_t, 4> ud_cubie;
	nth_permutation(ud_prm, ud_cubie);

	std::array<uint8_t, 12> e;
	nth_permutation(rest_prm, e.begin(), 8);

	auto ud_loc = nth_combination<4>(12, ud_loc_index);
	for (int i = 0; i < 4; i++)
	{
		e[i + 8] = ud_cubie[i] + 8;
		auto begin = e.rbegin() + 3 - i;
		auto end = e.rbegin() + 12 - ud_loc[i];
		std::rotate(begin, begin + 1, end);
	}

	auto c = Corners::from_prm_index(corner_prm);
	if (is_even_permutation(c) != is_even_permutation(e))
		std::ranges::next_permutation(c);

	return Cube3x3{
		Corners{ c, Corners::from_ori_index(corner_ori) },
		EdgesCenter{ e , EdgesCenter::from_ori_index(edge_ori) }
	};
}

bool H0::in_subset(const Cube3x3& c)
{
	return same_coset(c, Cube3x3::solved());
}

bool H0::same_coset(const Cube3x3& a, const Cube3x3& b)
{
	return same_orientation(a, b)
		&& same_ud_slice_location(a.edges(), b.edges());
}
