add_library(
    Solvers STATIC
    brute_force.cpp
    brute_force.h
    corners.cpp
    corners.h
    neighbours.h
    one_phase.cpp
    one_phase.h
    solvers.h
    transposition_table.h
    two_phase.cpp
    two_phase.h
)

target_link_libraries(
    Solvers
    Cube
    gtest_main
)
