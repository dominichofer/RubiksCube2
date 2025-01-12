#include "corners.h"
#include <cmath>
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

std::vector<uint8_t> CreateCornerTable()
{
	const uint8_t sentinel = 0xFF;
	std::vector<uint8_t> table(Corners::index_size, sentinel);

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
	return table;
}

class DistanceTable
{
	std::vector<uint8_t> table;
public:
	DistanceTable() noexcept
	{
		std::string filename = "corners_table.bin";
		if (std::ifstream(filename).good())
		{
			table.resize(Corners::index_size);
			std::ifstream file(filename, std::ios::binary);
			file.read(reinterpret_cast<char*>(table.data()), Corners::index_size);
		}
		else
		{
			table = CreateCornerTable();
			std::ofstream file(filename, std::ios::binary);
			file.write(reinterpret_cast<const char*>(table.data()), Corners::index_size);
		}
	}

	uint8_t operator[](const Corners& c) const noexcept
	{
		return table[c.index()];
	}
};

static const DistanceTable distance_table;

int solution_distance(Corners c)
{
	return distance_table[c];
}

std::vector<Corners::Twist> solution(Corners c)
{
	int dst = solution_distance(c);

	std::vector<Corners::Twist> solution;
	solution.reserve(dst);

	for (int d = dst; d > 0; --d)
		for (Corners::Twist twist : Corners::twists)
		{
			Corners n = c.twisted(twist);
			if (solution_distance(n) == d - 1)
			{
				solution.push_back(twist);
				c = n;
				break;
			}
		}
	return solution;
}
