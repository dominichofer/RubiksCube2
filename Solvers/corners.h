#pragma once
#include "Cube/cube.h"
#include <vector>

int solution_distance(Corners);
std::vector<Corners::Twist> solution(Corners);

std::vector<uint8_t> CreateCornerTable();
