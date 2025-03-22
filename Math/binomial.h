#pragma once
#include <cstdint>
#include <vector>

// Returns the binomial coefficient "n choose k".
uint64_t binomial(uint64_t n, uint64_t k);

// Returns the index of the combination
// in the lexicographically sorted list of all possible
// combinations of n elements taken k at a time.
uint64_t combination_index(uint64_t n, const std::vector<int>& combination);

// Returns the index-th combination of n elements taken k at a time.
std::vector<int> nth_combination(uint64_t n, uint64_t k, uint64_t index);
