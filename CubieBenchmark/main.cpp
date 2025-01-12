#include "benchmark/benchmark.h"
#include "Cubies/cubies.h"
#include <chrono>
#include <random>
#include <iostream>

#define BENCH(cls, func) \
void cls##_##func(benchmark::State& state) \
{ \
	auto cube = RandomCube<cls>(); \
	for (auto _ : state) \
		benchmark::DoNotOptimize(cube.func()); \
} \
BENCHMARK(cls##_##func);

//BENCH(Corners, L1)
//BENCH(Corners, L2)
//BENCH(Corners, L3)
//BENCH(Corners, R1)
//BENCH(Corners, R2)
//BENCH(Corners, R3)
//BENCH(Corners, U1)
//BENCH(Corners, U2)
//BENCH(Corners, U3)
//BENCH(Corners, D1)
//BENCH(Corners, D2)
//BENCH(Corners, D3)
//BENCH(Corners, F1)
//BENCH(Corners, F2)
//BENCH(Corners, F3)
//BENCH(Corners, B1)
//BENCH(Corners, B2)
//BENCH(Corners, B3)
//BENCH(Corners, prm_index)
//BENCH(Corners, ori_index)
//BENCH(Corners, index)
BENCH(Corners, hash)
//
//BENCH(EdgesCenter, L1)
//BENCH(EdgesCenter, L2)
//BENCH(EdgesCenter, L3)
//BENCH(EdgesCenter, R1)
//BENCH(EdgesCenter, R2)
//BENCH(EdgesCenter, R3)
//BENCH(EdgesCenter, U1)
//BENCH(EdgesCenter, U2)
//BENCH(EdgesCenter, U3)
//BENCH(EdgesCenter, D1)
//BENCH(EdgesCenter, D2)
//BENCH(EdgesCenter, D3)
//BENCH(EdgesCenter, F1)
//BENCH(EdgesCenter, F2)
//BENCH(EdgesCenter, F3)
//BENCH(EdgesCenter, B1)
//BENCH(EdgesCenter, B2)
//BENCH(EdgesCenter, B3)
//BENCH(EdgesCenter, prm_index)
//BENCH(EdgesCenter, ori_index)
//BENCH(EdgesCenter, index)
BENCH(EdgesCenter, hash)

//BENCH(EdgesSide, L1)
//BENCH(EdgesSide, L2)
//BENCH(EdgesSide, L3)
//BENCH(EdgesSide, l1)
//BENCH(EdgesSide, l2)
//BENCH(EdgesSide, l3)
//BENCH(EdgesSide, R1)
//BENCH(EdgesSide, R2)
//BENCH(EdgesSide, R3)
//BENCH(EdgesSide, r1)
//BENCH(EdgesSide, r2)
//BENCH(EdgesSide, r3)
//BENCH(EdgesSide, U1)
//BENCH(EdgesSide, U2)
//BENCH(EdgesSide, U3)
//BENCH(EdgesSide, u1)
//BENCH(EdgesSide, u2)
//BENCH(EdgesSide, u3)
//BENCH(EdgesSide, D1)
//BENCH(EdgesSide, D2)
//BENCH(EdgesSide, D3)
//BENCH(EdgesSide, d1)
//BENCH(EdgesSide, d2)
//BENCH(EdgesSide, d3)
//BENCH(EdgesSide, F1)
//BENCH(EdgesSide, F2)
//BENCH(EdgesSide, F3)
//BENCH(EdgesSide, f1)
//BENCH(EdgesSide, f2)
//BENCH(EdgesSide, f3)
//BENCH(EdgesSide, B1)
//BENCH(EdgesSide, B2)
//BENCH(EdgesSide, B3)
//BENCH(EdgesSide, b1)
//BENCH(EdgesSide, b2)
//BENCH(EdgesSide, b3)
//BENCH(EdgesSide, prm_index)
//BENCH(EdgesSide, index)
BENCH(EdgesSide, hash)

BENCH(FacesCenter, l1)
BENCH(FacesCenter, l2)
BENCH(FacesCenter, l3)
BENCH(FacesCenter, r1)
BENCH(FacesCenter, r2)
BENCH(FacesCenter, r3)
BENCH(FacesCenter, u1)
BENCH(FacesCenter, u2)
BENCH(FacesCenter, u3)
BENCH(FacesCenter, d1)
BENCH(FacesCenter, d2)
BENCH(FacesCenter, d3)
BENCH(FacesCenter, f1)
BENCH(FacesCenter, f2)
BENCH(FacesCenter, f3)
BENCH(FacesCenter, b1)
BENCH(FacesCenter, b2)
BENCH(FacesCenter, b3)
BENCH(FacesCenter, prm_index)
BENCH(FacesCenter, index)
BENCH(FacesCenter, hash)

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
}

template <typename T>
void perft()
{
	counter = 0;
	for (int i = 0; i < 9; i++)
	{
		auto start = std::chrono::high_resolution_clock::now();
		perft(T{}, i);
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
		std::cout << "Depth: " << i << " Nodes: " << counter << " Time: " << duration << " ms";
		if (duration > 0)
			std::cout << " (" << counter / 1000 / duration << " MN/s)";
		std::cout << std::endl;
	}
}

template <typename T>
void perft2(const T& cube, int depth)
{
	if (depth == 0) {
		counter++;
		return;
	}
	perft2(cube.L1(), depth - 1);
	perft2(cube.L2(), depth - 1);
	perft2(cube.L3(), depth - 1);
	perft2(cube.l1(), depth - 1);
	perft2(cube.l2(), depth - 1);
	perft2(cube.l3(), depth - 1);
	perft2(cube.R1(), depth - 1);
	perft2(cube.R2(), depth - 1);
	perft2(cube.R3(), depth - 1);
	perft2(cube.r1(), depth - 1);
	perft2(cube.r2(), depth - 1);
	perft2(cube.r3(), depth - 1);
	perft2(cube.U1(), depth - 1);
	perft2(cube.U2(), depth - 1);
	perft2(cube.U3(), depth - 1);
	perft2(cube.u1(), depth - 1);
	perft2(cube.u2(), depth - 1);
	perft2(cube.u3(), depth - 1);
	perft2(cube.D1(), depth - 1);
	perft2(cube.D2(), depth - 1);
	perft2(cube.D3(), depth - 1);
	perft2(cube.d1(), depth - 1);
	perft2(cube.d2(), depth - 1);
	perft2(cube.d3(), depth - 1);
	perft2(cube.F1(), depth - 1);
	perft2(cube.F2(), depth - 1);
	perft2(cube.F3(), depth - 1);
	perft2(cube.f1(), depth - 1);
	perft2(cube.f2(), depth - 1);
	perft2(cube.f3(), depth - 1);
	perft2(cube.B1(), depth - 1);
	perft2(cube.B2(), depth - 1);
	perft2(cube.B3(), depth - 1);
	perft2(cube.b1(), depth - 1);
	perft2(cube.b2(), depth - 1);
	perft2(cube.b3(), depth - 1);
}

template <typename T>
void perft2()
{
	counter = 0;
	for (int i = 0; i < 7; i++)
	{
		auto start = std::chrono::high_resolution_clock::now();
		perft2(T{}, i);
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
		std::cout << "Depth: " << i << " Nodes: " << counter << " Time: " << duration << " ms";
		if (duration > 0)
			std::cout << " (" << counter / 1000 / duration << " MN/s)";
		std::cout << std::endl;
	}
}


int main(int argc, char** argv)
{
	//perft<Corners>();
	//perft<EdgesCenter>();
	//perft2<EdgesSide>();
	//perft2<FacesCenter>();
	::benchmark::Initialize(&argc, argv);
	if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
	::benchmark::RunSpecifiedBenchmarks();
	::benchmark::Shutdown();
	return 0;
}