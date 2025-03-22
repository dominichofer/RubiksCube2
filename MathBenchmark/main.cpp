#include "benchmark/benchmark.h"
#include "Math/math.h"
#include <ranges>

std::vector<int> random_combination(int n, int k)
{
	std::vector<int> c;
	for (int i = 0; i < k; ++i)
		c.push_back(rand() % n);
	std::ranges::sort(c);
	return c;
}

void n_k_args(benchmark::internal::Benchmark* b)
{
	for (int n : { 8, 12, 24 })
		for (int k = 0; k <= n / 2; ++k)
			b->Args({ n, k });
}

void binomial(benchmark::State& state)
{
	int n = state.range(0);
	int k = state.range(1);
	for (auto _ : state)
		benchmark::DoNotOptimize(binomial(n, k));
}
BENCHMARK(binomial)->Apply(n_k_args);

void combination_index(benchmark::State& state)
{
	int n = state.range(0);
	int k = state.range(1);
	std::vector<int> comb = random_combination(n, k);
	for (auto _ : state)
		benchmark::DoNotOptimize(combination_index(n, comb));
}
BENCHMARK(combination_index)->Apply(n_k_args);

void nth_combination(benchmark::State& state)
{
	int n = state.range(0);
	int k = state.range(1);
	int index = rand() % binomial(n, k);
	for (auto _ : state)
		benchmark::DoNotOptimize(nth_combination(n, k, index));
}
BENCHMARK(nth_combination)->Apply(n_k_args);

void path_to_neighbours(benchmark::State& state)
{
	int max_length = state.range(0);
	std::vector<int> edges = { +1, +2, +4, +8, +16, +32, +64, +128, +256, +512 };
	auto traverse = [](int node, int edge) { return node + edge; };
	for (auto _ : state)
		benchmark::DoNotOptimize(path_to_neighbours(0, max_length, 5, edges, traverse));
}
BENCHMARK(path_to_neighbours)->DenseRange(0, 10);

void neighbours(benchmark::State& state)
{
	int max_length = state.range(0);
	std::vector<int> edges = { +1, +2, +4, +8, +16, +32, +64, +128, +256, +512 };
	auto traverse = [](int node, int edge) { return node + edge; };
	for (auto _ : state)
		benchmark::DoNotOptimize(neighbours(0, max_length, 5, edges, traverse));
}
BENCHMARK(neighbours)->DenseRange(0, 10);

BENCHMARK_MAIN();
