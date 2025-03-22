#include "Solvers/solvers.h"
#include <iostream>
#include <vector>

int main()
{
	Corners c;
	std::mt19937_64 rng(std::random_device{}());
	std::uniform_int_distribution<std::size_t> dist(0, Corners::twists.size() - 1);
	for (int i = 0; i < 100; i++)
	{
		auto o0 = c.orientation(0);
		auto o1 = c.orientation(1);
		auto o2 = c.orientation(2);
		auto o3 = c.orientation(3);
		auto o4 = c.orientation(4);
		auto o5 = c.orientation(5);
		auto o6 = c.orientation(6);
		auto o7 = c.orientation(7);
		auto sum = o0 + o1 + o2 + o3 + o4 + o5 + o6 + o7;
		std::cout << o0 << " " << o1 << " " << o2 << " " << o3 << " " << o4 << " " << o5 << " " << o6 << " " << o7 << " " << sum << std::endl;
		c = c.twisted(Corners::twists[dist(rng)]);
	}
}