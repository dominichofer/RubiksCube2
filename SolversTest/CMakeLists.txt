add_executable(
    SolversTest
    close_solution.cpp
    corners.cpp
    one_phase.cpp
    pch.cpp
    transposition_table.cpp
)

target_precompile_headers(SolversTest PRIVATE pch.h)

target_link_libraries(
    SolversTest
    Solvers
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(SolversTest)
