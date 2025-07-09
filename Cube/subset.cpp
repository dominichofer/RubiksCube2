#include "subset.h"
#include <array>
#include <algorithm>

using namespace H0;

uint64_t H0::coset_number(uint64_t corner_ori, uint64_t edge_ori, uint64_t slice_loc)
{
	uint64_t number = corner_ori;
	number = number * EdgesCenter::ori_size + edge_ori;
	number = number * EdgesCenter::ud_slice_loc_size + slice_loc;
	return number;
}

uint64_t H0::coset_number(const Cube3x3& cube)
{
	return coset_number(
		cube.corners().ori_index(),
		cube.edges().ori_index(),
		cube.edges().ud_slice_loc_index()
	);
}

uint64_t H0::coset_index(uint64_t corner_prm, uint64_t edge_prm)
{
	return edge_prm * (Corners::prm_size / 2) + corner_prm / 2;
}

uint64_t H0::coset_index(const Cube3x3& cube)
{
	return coset_index(
		cube.corners().prm_index(),
		cube.edges().ud_prm_index()
	);
}

CosetNumber H0::from_coset_number(uint64_t number)
{
	uint64_t e_slice_loc = number % EdgesCenter::ud_slice_loc_size;
	number /= EdgesCenter::ud_slice_loc_size;
	uint64_t e_ori = number % EdgesCenter::ori_size;
	number /= EdgesCenter::ori_size;
	uint64_t c_ori = number;
	return { e_slice_loc, e_ori, c_ori };
}

CosetIndex H0::from_coset_index(uint64_t index)
{
	uint64_t c_prm = index % (Corners::prm_size / 2);
	index /= (Corners::prm_size / 2);
	uint64_t e_prm = index;
	return { e_prm, c_prm };
}

Cube3x3 H0::from_coset(uint64_t number, uint64_t index)
{
	auto N = from_coset_number(number);
	auto I = from_coset_index(index);

	auto e = EdgesCenter::from_index(N.e_slice_loc, I.e_prm, N.e_ori);
	auto c = Corners::from_index(I.c_prm * 2, N.c_ori);
	if (c.is_even_permutation() != e.is_even_permutation())
		c.next_permutation();

	return Cube3x3{ c, e };
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
