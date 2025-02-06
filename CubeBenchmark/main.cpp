#include "benchmark/benchmark.h"
#include "Cube/cube.h"
#include <chrono>
#include <iostream>
#include <iomanip>

#define BENCH(cls, func) \
void func##_##cls(benchmark::State& state) \
{ \
	auto cube = RandomCube<cls>(); \
	for (auto _ : state) \
		benchmark::DoNotOptimize(cube.func()); \
} \
BENCHMARK(func##_##cls);

#define BENCH_OUTER_TWISTS(cls) \
BENCH(cls, L1) \
BENCH(cls, L2) \
BENCH(cls, L3) \
BENCH(cls, R1) \
BENCH(cls, R2) \
BENCH(cls, R3) \
BENCH(cls, U1) \
BENCH(cls, U2) \
BENCH(cls, U3) \
BENCH(cls, D1) \
BENCH(cls, D2) \
BENCH(cls, D3) \
BENCH(cls, F1) \
BENCH(cls, F2) \
BENCH(cls, F3) \
BENCH(cls, B1) \
BENCH(cls, B2) \
BENCH(cls, B3)

#define BENCH_INNER_TWISTS(cls) \
BENCH(cls, l1) \
BENCH(cls, l2) \
BENCH(cls, l3) \
BENCH(cls, r1) \
BENCH(cls, r2) \
BENCH(cls, r3) \
BENCH(cls, u1) \
BENCH(cls, u2) \
BENCH(cls, u3) \
BENCH(cls, d1) \
BENCH(cls, d2) \
BENCH(cls, d3) \
BENCH(cls, f1) \
BENCH(cls, f2) \
BENCH(cls, f3) \
BENCH(cls, b1) \
BENCH(cls, b2) \
BENCH(cls, b3)

BENCH(Corners, hash)
BENCH(EdgesCenter, hash)
BENCH(EdgesSide, hash)
BENCH(FacesCenter, hash)
BENCH(FacesSide, hash)
BENCH(Cube3x3, hash)
BENCH(Cube4x4, hash)
BENCH(Cube5x5, hash)

BENCH(Corners, prm_index)
BENCH(EdgesCenter, prm_index)
BENCH(EdgesSide, prm_index)
BENCH(FacesCenter, prm_index)
BENCH(FacesSide, prm_index)

BENCH(Corners, ori_index)
BENCH(EdgesCenter, ori_index)

BENCH(Corners, index)
BENCH(EdgesCenter, index)
BENCH(EdgesSide, index)
BENCH(FacesCenter, index)
BENCH(FacesSide, index)

void EdgesCenter_lt(benchmark::State& state)
{
	auto cube1 = RandomCube<EdgesCenter>();
	auto cube2 = RandomCube<EdgesCenter>();
	for (auto _ : state)
		benchmark::DoNotOptimize(cube1 < cube2);
}
BENCHMARK(EdgesCenter_lt);

BENCH_OUTER_TWISTS(Corners)
BENCH_OUTER_TWISTS(EdgesCenter)
BENCH_OUTER_TWISTS(EdgesSide)
BENCH_INNER_TWISTS(EdgesSide)
BENCH_OUTER_TWISTS(FacesCenter)
BENCH_INNER_TWISTS(FacesCenter)
BENCH_OUTER_TWISTS(FacesSide)
BENCH_INNER_TWISTS(FacesSide)
BENCH_OUTER_TWISTS(Cube3x3)
BENCH_OUTER_TWISTS(Cube4x4)
BENCH_INNER_TWISTS(Cube4x4)
BENCH_OUTER_TWISTS(Cube5x5)
BENCH_INNER_TWISTS(Cube5x5)

uint64_t counter;

template <typename Cube>
void perft(const Cube& cube, int depth)
{
	if (depth == 0) {
		counter++;
		return;
	}
	for (const auto& t : Cube::twists)
		perft(cube.twisted(t), depth - 1);
}

template <typename Cube>
void perft()
{
	counter = 0;
	for (int i = 0; i < 10; i++)
	{
		auto start = std::chrono::high_resolution_clock::now();
		perft(Cube{}, i);
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
		if (duration > 0)
		{
            std::cout << typeid(Cube).name() << " " << counter / 1000 / duration << " MN/s" << std::endl;
			break;
		}
	}
}

int main(int argc, char** argv)
{
	perft<Corners>();
	perft<EdgesCenter>();
	perft<EdgesSide>();
	perft<FacesCenter>();
	perft<FacesSide>();
	perft<Cube2x2>();
	perft<Cube3x3>();
	perft<Cube4x4>();
	perft<Cube5x5>();
	std::cout << std::endl;

	::benchmark::Initialize(&argc, argv);
	if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
	::benchmark::RunSpecifiedBenchmarks();
	::benchmark::Shutdown();
	return 0;
}
