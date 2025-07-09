#pragma once
#include "Math/math.h"
#include "cube2x2.h"
#include "cube3x3.h"
#include "cube4x4.h"
#include "cube5x5.h"
#include "corners.h"
#include "edges_center.h"
#include "edges_side.h"
#include "faces_center.h"
#include "faces_side.h"
#include "random.h"
#include "subset.h"
#include "twist.h"

template <typename T>
	requires requires(T t) { to_string(t); }
std::ostream& operator<<(std::ostream& os, const T& t)
{
	return os << to_string(t);
}
