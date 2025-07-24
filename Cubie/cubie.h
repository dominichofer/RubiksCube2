#pragma once
#include "Math/math.h"
#include "Std/std.h"
#include "corners.h"
#include "cube3x3.h"
#include "edges_center.h"
#include "random.h"
#include "subset.h"
#include "twist.h"

template <typename T>
	requires requires(T t) { to_string(t); }
std::ostream& operator<<(std::ostream& os, const T& t)
{
	return os << to_string(t);
}

namespace std
{
	template <typename T>
		requires requires(T t) { t.hash(); }
	struct hash<T>
	{
		size_t operator()(const T& c) const
		{
			return c.hash();
		}
	};
}
