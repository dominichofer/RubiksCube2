#include "pch.h"
#include <iostream>

TEST(Cube3x3, even_permutations)
{
	RandomTwistGenerator gen{ 209123 };
	for (int i = 0; i < 1'000'000; i++)
	{
		Twists twists = gen(100);
		Corners c = Corners{}.twisted(twists);
		EdgesCenter e = EdgesCenter{}.twisted(twists);
		std::cout << Cube3x3(c, e) << std::endl;
	}
}
