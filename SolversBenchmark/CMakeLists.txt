add_executable(
    SolversBenchmark
    main.cpp
)

target_link_libraries(
    SolversBenchmark
    Solvers
    benchmark::benchmark
)
