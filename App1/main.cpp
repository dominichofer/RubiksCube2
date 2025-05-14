#include "Solvers/solvers.h"
#include <iostream>
#include <vector>

int main()
{
	auto cube1 = Cube3x3::solved();
	auto cube2 = cube1.twisted(Twist::B1);
	auto number = H0::coset_number(cube2);
	auto cube3 = H0::from_coset(number, 0);
	bool same_o = same_orientation(cube2, cube3);
	bool same_ud = same_ud_slice_location(cube2.edges(), cube3.edges());
	bool same = H0::same_coset(cube2, cube3);
	auto cube4 = cube3.twisted(Twist::L1);
	auto cube5 = cube4.twisted(inversed({ Twist::B1, Twist::L1 }));
	auto cube6 = cube2.twisted(Twist::L1).twisted(inversed({ Twist::B1, Twist::L1 }));
	bool in_subset = H0::in_subset(cube5);
	std::cout << "Cube1: " << to_string(cube1) << std::endl;
	std::cout << "Cube2: " << to_string(cube2) << std::endl;
	std::cout << "Cube3: " << to_string(cube3) << std::endl;
	std::cout << "Same orientation: " << (same_o ? "true" : "false") << std::endl;
	std::cout << "Same UD slice location: " << (same_ud ? "true" : "false") << std::endl;
	std::cout << "Same: " << (same ? "true" : "false") << std::endl;
	std::cout << "Cube4: " << to_string(cube4) << std::endl;
	std::cout << "Cube5: " << to_string(cube5) << std::endl;
	std::cout << "Cube6: " << to_string(cube6) << std::endl;
	std::cout << "Coset number: " << number << std::endl;
	std::cout << "In subset: " << (in_subset ? "true" : "false") << std::endl;
}