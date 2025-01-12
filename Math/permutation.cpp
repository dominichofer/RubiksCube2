#include "permutation.h"

static const std::array<uint64_t, 21> factorials = {
	1, // factorial(0)
	1, // factorial(1)
	2, // factorial(2)
	6, // factorial(3)
	24, // factorial(4)
	120, // factorial(5)
	720, // factorial(6)
	5040, // factorial(7)
	40320, // factorial(8)
	362880, // factorial(9)
	3628800, // factorial(10)
	39916800, // factorial(11)
	479001600, // factorial(12)
	6227020800, // factorial(13)
	87178291200, // factorial(14)
	1307674368000, // factorial(15)
	20922789888000, // factorial(16)
	355687428096000, // factorial(17)
	6402373705728000, // factorial(18)
	121645100408832000, // factorial(19)
	2432902008176640000, // factorial(20)
};

uint64_t factorial(uint64_t n)
{
	return factorials[n];
}
