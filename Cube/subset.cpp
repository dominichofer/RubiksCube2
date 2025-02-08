#include "subset.cpp"

const std::vector<Cube3x3::Twist> Cube3x3::twists = {
	Cube3x3::Twist::L2,
	Cube3x3::Twist::R2,
	Cube3x3::Twist::U1, Cube3x3::Twist::U2, Cube3x3::Twist::U3,
	Cube3x3::Twist::D1, Cube3x3::Twist::D2, Cube3x3::Twist::D3,
	Cube3x3::Twist::F2,
	Cube3x3::Twist::B2,
};

uint64_t subset_index(const Cube3x3& cube)
{
    auto& c = cube.corners();
    auto& e = cube.edges();
    auto corner_prm = c.prm_index();
    auto ud_edge_prm = permutation_index(e.cubie(0), e.cubie(1), e.cubie(2), e.cubie(3), e.cubie(4), e.cubie(5), e.cubie(6), e.cubie(7));
    auto ud_slice_edge_prm = e.ud_slice_prm_index();
    return corner_prm * factorial(8) * factorial(4) + ud_edge_prm * factorial(4) + ud_slice_edge_prm;
}

uint64_t coset_inedx(const Cube3x3& cube)
{
    auto& c = cube.corners();
    auto& e = cube.edges();
    auto corner_ori = c.ori_index();
    auto edge_ori = e.ori_index();
    auto ud_index = e.ud_slice_prm_index();
    return corner_ori * EdgesCenter::ori_size * EdgesCenter::ud_slice_size + edge_ori * EdgesCenter::ud_slice_size + ud_index;
}
