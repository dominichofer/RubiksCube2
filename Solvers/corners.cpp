#include "corners.h"
#include <algorithm>

CornersDistanceTable::CornersDistanceTable() noexcept
{
	const uint8_t sentinel = 0xFF;
	table = std::vector<uint8_t>(Corners::index_size, sentinel);

	// The solved state is at distance 0
	table[Corners().index()] = 0;

	std::vector<Corners> last = { Corners() };
	std::vector<Corners> next;
	for (uint8_t distance = 1; !last.empty(); ++distance)
	{
		next.clear();
		#pragma omp parallel
		{
			std::vector<Corners> next_private;
			#pragma omp for nowait
			for (int i = 0; i < last.size(); ++i)
				for (Corners::Twist twist : Corners::twists)
				{
					Corners n = last[i].twisted(twist);
					uint64_t index = n.index();
					if (table[index] == sentinel)
					{
						table[index] = distance;
						next_private.push_back(n);
					}
				}
			#pragma omp critical
			next.insert(next.end(), next_private.begin(), next_private.end());
		}
		std::swap(last, next);
	}
	max_distance_ = *std::max_element(table.begin(), table.end());
}

uint8_t CornersDistanceTable::operator[](const Corners& c) const
{
	return table[c.index()];
}

std::vector<Corners::Twist> CornersDistanceTable::solve(Corners c) const
{
	int dst = this->operator[](c);

	std::vector<Corners::Twist> solution;
	solution.reserve(dst);

	for (int d = dst; d > 0; --d)
		for (Corners::Twist twist : Corners::twists)
		{
			Corners next = c.twisted(twist);
			if (this->operator[](next) == d - 1)
			{
				solution.push_back(twist);
				c = next;
				break;
			}
		}
	return solution;
}

int CornersDistanceTable::max_distance() const
{
	return max_distance_;
}

std::vector<uint8_t>::const_iterator CornersDistanceTable::begin() const
{
	return table.begin();
}

std::vector<uint8_t>::const_iterator CornersDistanceTable::end() const
{
	return table.end();
}
