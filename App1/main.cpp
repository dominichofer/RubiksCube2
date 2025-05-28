#include "Solvers/solvers.h"
#include <iostream>
#include <vector>

class Foo
{
	DistanceTable<Cube3x3> phase2_length{
		H0::twists,
		[](const Cube3x3& c) { return H0::subset_index(c); },
		[](uint64_t i) { return H0::from_subset(i); },
		H0::set_size
	};
	std::vector<bool> coset{ H0::set_size, false };
	int64_t coset_number;

	void fill(const Twists& twists, uint8_t depth)
	{
		int64_t size = static_cast<int64_t>(coset.size());
		for (int64_t i = 0; i < size; i++)
		{
			if (coset[i])
				continue;
			Cube3x3 cube = H0::from_coset(coset_number, i).twisted(twists);
			if (phase2_length[cube] <= depth)
				coset[i] = true;
		}
	}
};

int main()
{
	DistanceTable<Cube3x3> phase2_length{
		H0::twists,
		[](const Cube3x3& c) { return H0::subset_index(c); },
		[](uint64_t i) { return H0::from_subset(i); },
		H0::set_size
	};
	std::vector<bool> coset{ H0::set_size, false };

	for (int nr = 0; nr < H0::cosets; nr++)
	{
		Cube3x3 cube = H0::from_coset(nr, 0);
	}
}
