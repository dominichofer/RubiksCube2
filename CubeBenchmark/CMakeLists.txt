add_executable(
    CubeBenchmark
    main.cpp
)

target_link_libraries(
    CubeBenchmark
    Cube
    benchmark::benchmark
)
