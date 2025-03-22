#include "subset.h"

uint64_t H0::subset_index(const Cube3x3& cube)
{
    auto& c = cube.corners();
    auto& e = cube.edges();
	// The parity of the corner's permutation is the same as the parity of the ud-edge's permutation; thus '/ 2'.
    auto corner_prm = c.prm_index() / 2;
    auto ud_edges_prm = permutation_index(e.cubie(0), e.cubie(1), e.cubie(2), e.cubie(3), e.cubie(4), e.cubie(5), e.cubie(6), e.cubie(7));
	auto ud_slice_edge_prm = permutation_index(e.cubie(8) - 8, e.cubie(9) - 8, e.cubie(10) - 8, e.cubie(11) - 8);
    return (corner_prm * factorial(8) + ud_edges_prm) * factorial(4) + ud_slice_edge_prm;
}

uint64_t H0::coset_index(const Cube3x3& cube)
{
    auto& c = cube.corners();
    auto& e = cube.edges();
    auto corner_ori = c.ori_index();
    auto edge_ori = e.ori_index();
    auto ud_index = e.ud_slice_prm_index();
    return (corner_ori * EdgesCenter::ori_size + edge_ori) * EdgesCenter::ud_slice_size + ud_index;
}

Cube3x3 H0::from_coset_index(uint64_t index)
{
	return Cube3x3{};
	//auto ud_index = index % EdgesCenter::ud_slice_size;
	//index /= EdgesCenter::ud_slice_size;
	//auto edge_ori = index % EdgesCenter::ori_size;
	//index /= EdgesCenter::ori_size;
	//auto corner_ori = index;
	//auto e = EdgesCenter::from_ud_slice_prm_index(ud_index);
	//e.set_ori_index(edge_ori);
	//auto c = Corners(
	//return Cube3x3{ c, e };
}