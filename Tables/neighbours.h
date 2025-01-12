#pragma once
#include "Core/core.h"
#include <array>
#include <optional>
#include <vector>

std::optional<std::array<Rotation, 6>> solution(const Cube3x3&);
