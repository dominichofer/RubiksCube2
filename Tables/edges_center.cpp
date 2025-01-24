#include "Cube/cube.h"
#include "Math/math.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

static uint64_t SIZE = factorial(12) * std::pow(2, 11); // 12! * 2^11 = 980'995'276'800

class ByteInFile
{
	std::fstream& file;
	const uint64_t index;
public:
	ByteInFile(std::fstream& file, uint64_t index) noexcept : file(file), index(index) {}
	ByteInFile& operator=(uint8_t byte)
	{
		file.seekp(index);
		file.write(reinterpret_cast<const char*>(&byte), 1);
		return *this;
	}
	operator uint8_t() const
	{
		file.seekg(index);
		uint8_t byte;
		file.read(reinterpret_cast<char*>(&byte), 1);
		return byte;
	}
};

class DistanceTable
{
	mutable std::fstream file;
public:
	mutable uint64_t sets = 0;
	mutable uint64_t gets = 0;
	DistanceTable(std::filesystem::path file_path) noexcept
	{
		// Check if the file exists before opening
		bool file_exists = std::filesystem::exists(file_path);
		if (file_exists)
		{
			file.open(file_path, std::ios_base::in | std::ios_base::out | std::ios::binary);
			return;
		}

		// Create the file
		file.open(file_path, std::ios::binary | std::ios::app);
		file.close();
		file.open(file_path, std::ios_base::in | std::ios_base::out | std::ios::binary);

		auto start = std::chrono::high_resolution_clock::now();

		// Initialize the file with 0xFF
		std::size_t buffer_size = 4 * 1024 * 1024;
		std::vector<uint8_t> data(buffer_size, 0xFF);
		for (uint64_t i = 0; i < SIZE; i += buffer_size)
		{
			file.write(reinterpret_cast<const char*>(data.data()), std::min(buffer_size, SIZE - i));
			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
			if (duration.count() > 0)
			{
				auto MB_per_s = static_cast<double>(i + buffer_size) / 1024 / 1024 / duration.count() * 1000;
				std::cout << "Initializing " << (i + buffer_size) / 1024 / 1024 << " MB took " << duration.count() << " ms (" << MB_per_s << " MB/s)" << std::endl;
			}
		}
	}

	uint8_t get(uint64_t index) const
	{
		file.seekg(index);
		uint8_t byte;
		file.read(reinterpret_cast<char*>(&byte), 1);
		++gets;
		return byte;
	}
	uint8_t get(const Cubies& c) const
	{
		return get(c.index());
	}

	void set(uint64_t index, uint8_t value)
	{
		file.seekp(index);
		file.write(reinterpret_cast<const char*>(&value), 1);
		++sets;
	}
	void set(const Cubies& c, uint8_t value)
	{
		set(c.index(), value);
	}
};

int CreateCenterEdgesTable(std::filesystem::path file_path)
{
	DistanceTable table(file_path);

	auto start = std::chrono::high_resolution_clock::now();

	// The solved state is at distance 0
	table.set(Cubies(), 0);
	std::vector<Cubies> last = { Cubies() };
	std::vector<Cubies> next;
	uint8_t distance = 1;
	while (not last.empty())
	{
		next.clear();
		for (Cubies c : last)
			for (Cubies n : neighbours(c))
			{
				uint64_t index = n.index();
				//if (table.get(index) >= distance)
				{
					table.set(index, distance);
					next.push_back(n);
				}
			}
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		std::cout << "Distance " << static_cast<int>(distance) << " took " << next.size() << " states " << duration.count() << " ms" << std::endl;
		std::cout << "Sets: " << table.sets << " Gets: " << table.gets << std::endl;
		std::swap(last, next);
		++distance;
	}
	return 0;
}