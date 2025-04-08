#include "subset.h"
#include <array>
#include <algorithm>

uint64_t H0::subset_index(const Cube3x3& cube)
{
    const auto& c = cube.corners();
    const auto& e = cube.edges();
	// The parity of the corner's permutation is the same as the parity of the ud-edge's permutation; thus '/2'.
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
	uint64_t corner_prm = index * 2;

	std::array<uint8_t, 8> c;
	std::array<uint8_t, 12> e;
	std::ranges::iota(c, 0);
	std::ranges::iota(e, 0);

	nth_permutation(e.begin(), e.begin() + 8, ud_edges_prm);
	nth_permutation(e.begin() + 8, e.end(), ud_slice_prm);
	nth_permutation(c, corner_prm);
	if (is_even_permutation(c) != is_even_permutation(e))
		std::ranges::next_permutation(c);

	return Cube3x3{
		Corners{ c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7], 0, 0, 0, 0, 0, 0, 0, 0 },
		EdgesCenter{ e[0], e[1], e[2], e[3], e[4], e[5], e[6], e[7], e[8], e[9], e[10], e[11], 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
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
		if (std::ranges::find(ud, i) == ud.end())
			rest.push_back(e.cubie(i));
	for (uint8_t& loc : ud)
		loc = e.cubie(loc) - 8;
	uint64_t index = c.prm_index();
	index = index * factorial(4) + permutation_index(ud);
	index = index * factorial(8) + permutation_index(rest);
	return index;
}

Cube3x3 H0::from_coset(uint64_t number, uint64_t index)
{
	uint64_t ud_loc_index = number % binomial(12, 4);
	number /= binomial(12, 4);
	uint64_t edge_ori = number % EdgesCenter::ori_size;
	number /= EdgesCenter::ori_size;
	uint64_t corner_ori = number;

	uint64_t rest_prm = index % factorial(8);
	index /= factorial(8);
	uint64_t ud_prm = index % factorial(4);
	index /= factorial(4);
	uint64_t corner_prm = index;

	std::vector<uint8_t> edges(8);
	std::ranges::iota(edges, 0);
	nth_permutation(edges, rest_prm);

	auto ud_loc = nth_combination(12, 4, ud_loc_index);

	std::array<uint8_t, 4> ud_cubie;
	std::ranges::iota(ud_cubie, 0);
	nth_permutation(ud_cubie, ud_prm);

	for (int i = 0; i < 4; i++)
		edges.insert(edges.begin() + ud_loc[i], ud_cubie[i] + 8);

	return Cube3x3{
		Corners{ corner_prm, corner_ori },
		EdgesCenter{
			edges[0], edges[1], edges[2], edges[3],
			edges[4], edges[5], edges[6], edges[7],
			edges[8], edges[9], edges[10], edges[11],
			edge_ori }
	};
}