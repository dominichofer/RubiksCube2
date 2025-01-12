#pragma once
#include "Cube/cube.h"
#include <optional>
#include <vector>

class CloseSolutionTableCube3x3
{
	struct CubeAndTwists
	{
		Cube3x3 cube;
		std::vector<Cube3x3::Twist> twists;
		bool operator<(const CubeAndTwists&) const;
	};

	static uint64_t ori_index(const Cube3x3&);

	std::vector<std::vector<CubeAndTwists>> table;
public:
	explicit CloseSolutionTableCube3x3(int max_distance);

	std::optional<std::vector<Cube3x3::Twist>> operator[](const Cube3x3&) const;
};