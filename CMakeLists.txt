cmake_minimum_required(VERSION 3.18)
project(RubiksCube)
enable_testing()

set(CMAKE_CXX_STANDARD 23)
if (MSVC)
	set(CMAKE_CXX_FLAGS "/std:c++23 /EHsc /MP")
	set(CMAKE_CXX_FLAGS_DEBUG "/Od /MDd")
	set(CMAKE_CXX_FLAGS_RELEASE "/Ox /MD /GL")
else()
	set(CMAKE_CXX_FLAGS "-march=native -w")
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
endif()

include(FetchContent)

# Google Test
FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Google Benchmark
FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.8.5
)
FetchContent_MakeAvailable(googlebenchmark)

# OpenMP
find_package(OpenMP REQUIRED COMPONENTS CXX)
link_libraries(OpenMP::OpenMP_CXX)

include_directories(.)
add_subdirectory(Cube)
add_subdirectory(CubeTest)
add_subdirectory(CubeBenchmark)
add_subdirectory(Math)
add_subdirectory(MathTest)
add_subdirectory(Solvers)
add_subdirectory(SolversTest)
add_subdirectory(SolversBenchmark)
