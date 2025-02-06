#pragma once
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <functional>
#include <vector>
#include <fstream>

template <typename Cube>
class DistanceTable
{
	std::function<std::size_t(const Cube&)> index;
	std::vector<uint8_t> table;
	std::vector<typename Cube::Twist> generators;
	int max_distance_;

	DistanceTable(
		std::vector<typename Cube::Twist> generators,
		std::function<std::size_t(const Cube&)> index_fkt)
		: index(std::move(index_fkt))
		, generators(std::move(generators))
	{}
public:
	DistanceTable(
		const Cube& origin,
		std::vector<typename Cube::Twist> generators,
		std::function<std::size_t(const Cube&)> index_fkt,
		std::size_t index_size)
		: index(std::move(index_fkt)), generators(std::move(generators))
	{
		const uint8_t sentinel = 0xFF;
		table = std::vector<uint8_t>(index_size, sentinel);

		// Origin is at distance 0
		table[index(origin)] = 0;

		std::vector<Cube> last = { origin };
		std::vector<Cube> next;
		for (uint8_t distance = 1; !last.empty(); ++distance)
		{
			next.clear();
			#pragma omp parallel
			{
				std::vector<Cube> next_private;
				#pragma omp for nowait
				for (int i = 0; i < last.size(); ++i)
					for (const auto& twist : generators)
					{
						Cube n = last[i].twisted(twist);
						std::size_t i = index(n);
						if (table[i] == sentinel)
						{
							table[i] = distance;
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

	static DistanceTable from_file(
		std::filesystem::path path,
		std::vector<typename Cube::Twist> generators,
		std::function<std::size_t(const Cube&)> index_fkt,
		std::size_t index_size)
	{
		DistanceTable table;
		table.index = std::move(index_fkt);
		table.generators = std::move(generators);
		table.table.reserve(index_size);
		std::ifstream file(path, std::ios::binary);
		file.read(reinterpret_cast<char*>(table.table.data()), size);
		return table;
	}

	void save(std::filesystem::path path) const
	{
		std::ofstream file(path, std::ios::binary);
		file.write(reinterpret_cast<const char*>(table.data()), table.size());
	}

	uint8_t operator[](const Cube& c) const
	{
		return table[index(c)];
	}


};