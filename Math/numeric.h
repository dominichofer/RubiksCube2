#include <cstdint>
#include <numeric>

constexpr uint64_t powi(uint64_t base, uint64_t exp)
{
	uint64_t result = 1;
	for (uint64_t i = 0; i < exp; i++)
		result *= base;
	return result;
}
