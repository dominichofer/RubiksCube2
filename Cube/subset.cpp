#include "subset.h"
#include <array>

uint64_t H0::subset_index(const Cube3x3& cube)
{
    const auto& c = cube.corners();
    const auto& e = cube.edges();
	// The parity of the corner's permutation is the same as the parity of the ud-edge's permutation; thus '/2'.
    uint64_t corner_prm = c.prm_index() / 2;
    uint64_t ud_edges_prm = permutation_index(e.cubie(0), e.cubie(1), e.cubie(2), e.cubie(3), e.cubie(4), e.cubie(5), e.cubie(6), e.cubie(7));
	uint64_t ud_slice_edge_prm = permutation_index(e.cubie(8) - 8, e.cubie(9) - 8, e.cubie(10) - 8, e.cubie(11) - 8);
	uint64_t index = corner_prm;
	index = index * factorial(8) + ud_edges_prm;
	index = index * factorial(4) + ud_slice_edge_prm;
	return index;
}

Cube3x3 H0::from_subset(uint64_t index)
{
	uint64_t ud_slice_edge_prm = index % factorial(4);
	index /= factorial(4);
	uint64_t ud_edges_prm = index % factorial(8);
	index /= factorial(8);
	uint64_t corner_prm = index * 2;

	std::array<uint8_t, 8> c;
	std::array<uint8_t, 12> e;
	std::ranges::iota(c, 0);
	std::ranges::iota(e, 0);

	nth_permutation(e.begin(), e.begin() + 8, ud_edges_prm);
	nth_permutation(e.begin() + 8, e.end(), ud_slice_edge_prm);
	nth_permutation(c, corner_prm);
	if (is_even_permutation(c) != is_even_permutation(e))
		std::swap(c[6], c[7]);

	return Cube3x3{
		Corners{ c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7], 0, 0, 0, 0, 0, 0, 0, 0 },
		EdgesCenter{ e[0], e[1], e[2], e[3], e[4], e[5], e[6], e[7], e[8], e[9], e[10], e[11], 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
}

uint64_t coset_number(const Cube3x3& cube)
{
	const auto& c = cube.corners();
	const auto& e = cube.edges();
	uint64_t index = c.ori_index();
	index = index * EdgesCenter::ori_size + e.ori_index();
	index = index * EdgesCenter::ud_slice_location_size + e.ud_slice_location_index();
	return index;
}

uint64_t H0::coset_index(const Cube3x3& cube)
{
	const auto& c = cube.corners();
	const auto& e = cube.edges();
	uint64_t index = c.prm_index();
	index = index * EdgesCenter::prm_size + e.ori_index();
}

Cube3x3 H0::from_coset_index(uint64_t index)
{
	uint64_t ud_slice_index = index % EdgesCenter::ud_slice_location_size;
	index /= EdgesCenter::ud_slice_location_size;
	uint64_t edge_ori = index % EdgesCenter::ori_size;
	index /= EdgesCenter::ori_size;
	uint64_t corner_ori = index;

	std::array<uint8_t, 8> c;
	for (int i = 0; i < 8; i++)
	{
		c[i] = corner_ori % 3;
		corner_ori /= 3;
	}

	std::array<uint8_t, 12> e;
	for (int i = 0; i < 12; i++)
	{
		e[i] = edge_ori % 2;
		edge_ori /= 2;
	}

	return Cube3x3{
		Corners{ 0, 1, 2, 3, 4, 5, 6, 7, c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7] },
		EdgesCenter{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, e[0], e[1], e[2], e[3], e[4], e[5], e[6], e[7], e[8], e[9], e[10], e[11] }
	};
}