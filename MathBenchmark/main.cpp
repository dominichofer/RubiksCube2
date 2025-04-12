#include "benchmark/benchmark.h"
#include "Math/math.h"
#include <ranges>
#include <random>

std::vector<int> random_combination(int n, int k)
{
	std::vector<int> c;
	for (int i = 0; i < k; ++i)
		c.push_back(rand() % n);
	std::ranges::sort(c);
	return c;
}

std::vector<int> random_permutation(int size)
{
	std::vector<int> p(size);
	std::ranges::iota(p, 0);
	std::ranges::shuffle(p, std::mt19937{ std::random_device{}() });
	return p;
}

void n_k_args(benchmark::internal::Benchmark* b)
{
	for (int n : { 8, 12, 24 })
		for (int k = 0; k <= n / 2; ++k)
			b->Args({ n, k });
}

void bm_permutation_index(benchmark::State& state)
{
	int n = state.range(0);
	std::vector<int> perm = random_permutation(n);
	for (auto _ : state)
		benchmark::DoNotOptimize(permutation_index(perm));
}
BENCHMARK(bm_permutation_index)->DenseRange(0, 10);

void bm_nth_permutation(benchmark::State& state)
{
	int n = state.range(0);
	uint64_t index = rand() % factorial(n);
	std::vector<int> p(n);
	for (auto _ : state)
	{
		nth_permutation(index, p.size(), p.begin());
		benchmark::DoNotOptimize(p);
	}
}
BENCHMARK(bm_nth_permutation)->DenseRange(0, 10);

void bm_binomial(benchmark::State& state)
{
	int n = state.range(0);
	int k = state.range(1);
	for (auto _ : state)
		benchmark::DoNotOptimize(binomial(n, k));
}
BENCHMARK(bm_binomial)->Apply(n_k_args);

void bm_combination_index(benchmark::State& state)
{
	int n = state.range(0);
	int k = state.range(1);
	std::vector<int> comb = random_combination(n, k);
	for (auto _ : state)
		benchmark::DoNotOptimize(combination_index(n, comb));
}
BENCHMARK(bm_combination_index)->Apply(n_k_args);

void bm_nth_combination(benchmark::State& state)
{
	int n = state.range(0);
	int k = state.range(1);
	int index = rand() % binomial(n, k);
	for (auto _ : state)
		benchmark::DoNotOptimize(nth_combination(n, k, index));
}
BENCHMARK(bm_nth_combination)->Apply(n_k_args);

void bm_path_to_neighbours(benchmark::State& state)
{
	int max_length = state.range(0);
	std::vector<int> edges = { +1, +2, +4, +8, +16, +32, +64, +128, +256, +512 };
	auto traverse = [](int node, int edge) { return node + edge; };
	for (auto _ : state)
		benchmark::DoNotOptimize(path_to_neighbours(0, max_length, 5, edges, traverse));
}
BENCHMARK(bm_path_to_neighbours)->DenseRange(0, 10);

void bm_neighbours(benchmark::State& state)
{
	int max_length = state.range(0);
	std::vector<int> edges = { +1, +2, +4, +8, +16, +32, +64, +128, +256, +512 };
	auto traverse = [](int node, int edge) { return node + edge; };
	for (auto _ : state)
		benchmark::DoNotOptimize(neighbours(0, max_length, 5, edges, traverse));
}
BENCHMARK(bm_neighbours)->DenseRange(0, 10);

BENCHMARK_MAIN();
