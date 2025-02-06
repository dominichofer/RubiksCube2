#pragma once
#include "Cube/cube.h"
#include <cstdint>
#include <vector>

class CornersDistanceTable
{
	int max_distance_;
	std::vector<uint8_t> table;
public:
	CornersDistanceTable() noexcept;

	uint8_t operator[](const Corners&) const;
	std::vector<Corners::Twist> solve(Corners) const;

	int max_distance() const;

	std::vector<uint8_t>::const_iterator begin() const;
	std::vector<uint8_t>::const_iterator end() const;
};
