#include "benchmark/benchmark.h"
#include "Cubie/cubie.h"
#include <chrono>
#include <iostream>
#include <random>

template <typename Cube>
uint64_t perft(const Cube& cube, int depth)
{
	if (depth == 0)
		return 1;
	uint64_t sum = 0;
	for (Twist t : all_twists)
		sum += perft(cube.twisted(t), depth - 1);
	return sum;
}

template <typename Cube>
void perft()
{
	auto start = std::chrono::high_resolution_clock::now();
	uint64_t counter = perft(Cube{}, /*depth*/ 6);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
	std::cout << typeid(Cube).name() << " " << counter / 1000 / duration << " MN/s" << std::endl;
}

#define BENCH(cls, func) \
void func##_##cls(benchmark::State& state) \
{ \
	auto cube = RandomCube<cls>(); \
	for (auto _ : state) \
		benchmark::DoNotOptimize(cube.func()); \
} \
BENCHMARK(func##_##cls);

BENCH(Corners, prm_index)
BENCH(Corners, ori_index)
BENCH(EdgesCenter, prm_index)
BENCH(EdgesCenter, slice_loc_index)
BENCH(EdgesCenter, ori_index)

int main(int argc, char** argv)
{
	perft<Corners>();
	perft<EdgesCenter>();
	std::cout << std::endl;

	::benchmark::Initialize(&argc, argv);
	if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
	::benchmark::RunSpecifiedBenchmarks();
	::benchmark::Shutdown();
	return 0;
}
