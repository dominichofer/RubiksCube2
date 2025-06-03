#include "Solvers/solvers.h"
#include <iostream>
#include <vector>

class Foo
{
	DistanceTable<Cube3x3> solution_dst{
		H0::twists,
		[](const Cube3x3& c) { return H0::subset_index(c); },
		H0::set_size
	};
	std::vector<bool> coset{ H0::set_size, false };
	int64_t coset_number;
public:
	Foo(int64_t coset_number) : coset_number(coset_number)
	{
		try
		{
			solution_dst.read("D:\\subset.dst");
		}
		catch (...)
		{
			solution_dst.fill(Cube3x3::solved(), &H0::from_subset);
			solution_dst.write("D:\\subset.dst");
		}
	}

	void fill(const Twists& twists, uint8_t max_solution_length)
	{
		uint8_t twists_count = static_cast<uint8_t>(twists.size());
		int64_t size = static_cast<int64_t>(coset.size());
		for (int64_t i = 0; i < size; i++)
		{
			if (coset[i])
				continue;
			Cube3x3 cube = H0::from_coset(coset_number, i).twisted(twists);
			if (twists_count + solution_dst[cube] <= max_solution_length)
				coset[i] = true;
		}
	}
};

int main()
{
	DistanceTable<Cube3x3> solution_dst{
		H0::twists,
		[](const Cube3x3& c) { return H0::subset_index(c); },
		H0::set_size
	};
	try
	{
		solution_dst.read("D:\\subset.dst");
	}
	catch (...)
	{
		solution_dst.fill(Cube3x3::solved(), &H0::from_subset);
		solution_dst.write("D:\\subset.dst");
	}
	std::vector<bool> coset{ H0::set_size, false };

	for (int nr = 0; nr < H0::cosets; nr++)
	{
		Cube3x3 cube = H0::from_coset(nr, 0);
	}
}
