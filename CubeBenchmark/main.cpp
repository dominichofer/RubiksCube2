#include "benchmark/benchmark.h"
#include "Cube/cube.h"
#include <chrono>
#include <iostream>

template <typename Cube>
uint64_t perft(const Cube& cube, int depth)
{
	if (depth == 0)
		return 1;
	uint64_t sum = 0;
	for (Twist t : Cube::twists)
		sum += perft(cube.twisted(t), depth - 1);
	return sum;
}

template <typename Cube>
void perft()
{
	for (int i = 0; i < 10; i++)
	{
		auto start = std::chrono::high_resolution_clock::now();
		uint64_t counter = perft(Cube::solved(), i);
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
		if (duration > 100)
		{
			std::cout << typeid(Cube).name() << " " << counter / 1000 / duration << " MN/s" << std::endl;
			break;
		}
	}
}

void EdgesCenter_lt(benchmark::State& state)
{
	auto cube1 = RandomCube<EdgesCenter>();
	auto cube2 = RandomCube<EdgesCenter>();
	for (auto _ : state)
		benchmark::DoNotOptimize(cube1 < cube2);
}
BENCHMARK(EdgesCenter_lt);

#define BENCH(cls, func) \
void func##_##cls(benchmark::State& state) \
{ \
	auto cube = RandomCube<cls>(); \
	for (auto _ : state) \
		benchmark::DoNotOptimize(cube.func()); \
} \
BENCHMARK(func##_##cls);

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

BENCH(EdgesCenter, lr_slice_location)
BENCH(EdgesCenter, ud_slice_location)
BENCH(EdgesCenter, fb_slice_location)

void same_permutation_EdgesCenter(benchmark::State& state)
{
	auto cube1 = RandomCube<EdgesCenter>();
	auto cube2 = RandomCube<EdgesCenter>();
	for (auto _ : state)
		benchmark::DoNotOptimize(same_permutation(cube1, cube2));
}
BENCHMARK(same_permutation_EdgesCenter);

void same_orientation_EdgesCenter(benchmark::State& state)
{
	auto cube1 = RandomCube<EdgesCenter>();
	auto cube2 = RandomCube<EdgesCenter>();
	for (auto _ : state)
		benchmark::DoNotOptimize(same_orientation(cube1, cube2));
}
BENCHMARK(same_orientation_EdgesCenter);

void same_lr_slice_location_EdgesCenter(benchmark::State& state)
{
	auto cube1 = RandomCube<EdgesCenter>();
	auto cube2 = RandomCube<EdgesCenter>();
	for (auto _ : state)
		benchmark::DoNotOptimize(same_lr_slice_location(cube1, cube2));
}
BENCHMARK(same_lr_slice_location_EdgesCenter);

void same_ud_slice_location_EdgesCenter(benchmark::State& state)
{
	auto cube1 = RandomCube<EdgesCenter>();
	auto cube2 = RandomCube<EdgesCenter>();
	for (auto _ : state)
		benchmark::DoNotOptimize(same_ud_slice_location(cube1, cube2));
}
BENCHMARK(same_ud_slice_location_EdgesCenter);

void same_fb_slice_location_EdgesCenter(benchmark::State& state)
{
	auto cube1 = RandomCube<EdgesCenter>();
	auto cube2 = RandomCube<EdgesCenter>();
	for (auto _ : state)
		benchmark::DoNotOptimize(same_fb_slice_location(cube1, cube2));
}
BENCHMARK(same_fb_slice_location_EdgesCenter);

void H0_subset_index(benchmark::State& state)
{
	auto cube = RandomCube<Cube3x3>();
	for (auto _ : state)
		benchmark::DoNotOptimize(H0::subset_index(cube));
}
BENCHMARK(H0_subset_index);

void H0_coset_number(benchmark::State& state)
{
	auto cube = RandomCube<Cube3x3>();
	for (auto _ : state)
		benchmark::DoNotOptimize(H0::coset_number(cube));
}
BENCHMARK(H0_coset_number);

void H0_coset_index(benchmark::State& state)
{
	auto cube = RandomCube<Cube3x3>();
	for (auto _ : state)
		benchmark::DoNotOptimize(H0::coset_index(cube));
}
BENCHMARK(H0_coset_index);

void H0_from_subset(benchmark::State& state)
{
	auto index = H0::subset_index(RandomCube<Cube3x3>());
	for (auto _ : state)
		benchmark::DoNotOptimize(H0::from_subset(index));
}
BENCHMARK(H0_from_subset);

void H0_from_coset(benchmark::State& state)
{
	auto cube = RandomCube<Cube3x3>(6844);
	auto number = H0::coset_number(cube);
	auto index = H0::coset_index(cube);
	for (auto _ : state)
		benchmark::DoNotOptimize(H0::from_coset(number, index));
}
BENCHMARK(H0_from_coset);

int main(int argc, char** argv)
{
	perft<Corners>();
	perft<EdgesCenter>();
	perft<EdgesSide>();
	perft<FacesCenter>();
	perft<FacesSide>();
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
