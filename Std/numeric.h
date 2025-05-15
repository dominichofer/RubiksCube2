#include <cstdint>
#include <numeric>

constexpr uint64_t powi(uint64_t base, uint64_t exp)
{
    uint64_t result = 1;
    while (exp) {
        if (exp & 1)
            result *= base;
        base *= base;
        exp >>= 1;
    }
    return result;
}
