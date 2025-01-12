#pragma once
#include "Cube/cube.h"
#include <vector>

std::vector<uint8_t> CreateCornerTable();
int solution_distance(Cubies);
std::vector<Rotation> solution(Cubies);
