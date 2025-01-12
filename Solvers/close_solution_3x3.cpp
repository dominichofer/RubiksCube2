#include "close_solution_3x3.h"
#include "neighbours.h"
#include <algorithm>

bool CloseSolutionTableCube3x3::CubeAndTwists::operator<(const CubeAndTwists& o) const
{
	return cube < o.cube;
}

uint64_t CloseSolutionTableCube3x3::ori_index(const Cube3x3& cube)
{
	return 0;
	uint64_t o = cube.corners().ori_index();
	uint64_t e = cube.edges().ori_index();
	return o * EdgesCenter::ori_size + e;
}

CloseSolutionTableCube3x3::CloseSolutionTableCube3x3(int max_distance)
{
	table.resize(Corners::ori_size * EdgesCenter::ori_size);
	auto map = neighbours(Cube3x3(), max_distance);
	for (const auto& [cube, twists] : map)
		table[ori_index(cube)].push_back({ cube, twists });
	for (auto& m : table)
		std::sort(m.begin(), m.end());
}

std::optional<std::vector<Cube3x3::Twist>> CloseSolutionTableCube3x3::operator[](const Cube3x3& cube) const
{
	auto& m = table[ori_index(cube)];
	auto it = std::lower_bound(m.begin(), m.end(), CubeAndTwists{ cube, {} });
	if (it == m.end() || it->cube != cube)
		return std::nullopt;
	return it->twists;
}
