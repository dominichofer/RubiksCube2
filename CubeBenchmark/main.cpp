#include "benchmark/benchmark.h"
#include "Cube/cube.h"
#include <chrono>
#include <iostream>

#define BENCH(cls, func) \
void cls##_##func(benchmark::State& state) \
{ \
	auto cube = RandomCube<cls>(); \
	for (auto _ : state) \
		benchmark::DoNotOptimize(cube.func()); \
} \
BENCHMARK(cls##_##func);

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
	auto cube = RandomCube<EdgesCenter>();
	auto cube2 = RandomCube<EdgesCenter>();
	for (auto _ : state)
		benchmark::DoNotOptimize(cube < cube2);
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

template <typename T>
void perft(const T& cube, int depth)
{
	if (depth == 0) {
		counter++;
		return;
	}
	perft(cube.L1(), depth - 1);
	perft(cube.L2(), depth - 1);
	perft(cube.L3(), depth - 1);
	perft(cube.R1(), depth - 1);
	perft(cube.R2(), depth - 1);
	perft(cube.R3(), depth - 1);
	perft(cube.U1(), depth - 1);
	perft(cube.U2(), depth - 1);
	perft(cube.U3(), depth - 1);
	perft(cube.D1(), depth - 1);
	perft(cube.D2(), depth - 1);
	perft(cube.D3(), depth - 1);
	perft(cube.F1(), depth - 1);
	perft(cube.F2(), depth - 1);
	perft(cube.F3(), depth - 1);
	perft(cube.B1(), depth - 1);
	perft(cube.B2(), depth - 1);
	perft(cube.B3(), depth - 1);
	if constexpr (cube.twists.size() > 18)
	{
		perft(cube.l1(), depth - 1);
		perft(cube.l2(), depth - 1);
		perft(cube.l3(), depth - 1);
		perft(cube.r1(), depth - 1);
		perft(cube.r2(), depth - 1);
		perft(cube.r3(), depth - 1);
		perft(cube.u1(), depth - 1);
		perft(cube.u2(), depth - 1);
		perft(cube.u3(), depth - 1);
		perft(cube.d1(), depth - 1);
		perft(cube.d2(), depth - 1);
		perft(cube.d3(), depth - 1);
		perft(cube.f1(), depth - 1);
		perft(cube.f2(), depth - 1);
		perft(cube.f3(), depth - 1);
		perft(cube.b1(), depth - 1);
		perft(cube.b2(), depth - 1);
		perft(cube.b3(), depth - 1);
	}
}

template <typename T>
void perft()
{
	counter = 0;
	for (int i = 0; i < 10; i++)
	{
		auto start = std::chrono::high_resolution_clock::now();
		perft(T{}, i);
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
		if (duration > 100)
		{
			std::cout << typeid(T).name() << "\t" << counter / 1000 / duration << " MN/s" << std::endl;
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
