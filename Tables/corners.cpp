#include "Core/core.h"
#include <cmath>
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

static int SIZE = factorial(8) * std::pow(3, 7); // 8! * 3^7 = 88'179'840

std::vector<uint8_t> CreateCornerTable()
{
	std::vector<uint8_t> table(SIZE, 0xFF);

	// The solved state is at distance 0
	table[Cubies().index()] = 0;
	std::vector<Cubies> last = { Cubies() };
	std::vector<Cubies> next;
	for (uint8_t distance = 1; !last.empty(); ++distance)
	{
		next.clear();
		#pragma omp parallel
		{
			std::vector<Cubies> next_private;
			#pragma omp for nowait
			for (int i = 0; i < last.size(); ++i)
				for (Cubies n : neighbours(last[i]))
				{
					uint64_t index = n.index();
					if (table[index] == 0xFF)
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
			table.resize(SIZE);
			std::ifstream file(filename, std::ios::binary);
			file.read(reinterpret_cast<char*>(table.data()), SIZE);
		}
		else
		{
			table = CreateCornerTable();
			std::ofstream file(filename, std::ios::binary);
			file.write(reinterpret_cast<const char*>(table.data()), SIZE);
		}
	}

	uint8_t operator[](const Cubies& c) const noexcept
	{
		return table[c.index()];
	}
};

static const DistanceTable distance_table;

int solution_distance(Cubies c)
{
	return distance_table[c];
}

std::vector<Rotation> solution(Cubies c)
{
	int dst = solution_distance(c);
	std::vector<Rotation> solution;
	solution.reserve(dst);
	for (int d = dst; d > 0; --d)
		for (Rotation r : rotations)
		{
			Cubies n = c.rotated(r);
			if (solution_distance(n) == d - 1)
			{
				solution.push_back(r);
				c = n;
				break;
			}
		}
	return solution;
}
