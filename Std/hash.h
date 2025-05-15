#include <functional>

namespace
{
    inline void hash(std::size_t& seed) {}

    template <typename T, typename... Rest>
    void hash(std::size_t& seed, const T& v, Rest... rest)
    {
        std::hash<T> hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        hash(seed, rest...);
    }
}

template <typename T, typename... Rest>
std::size_t hash(const T& v, Rest... rest)
{
    std::size_t seed = 0;
    hash(seed, v, rest...);
    return seed;
}
