add_executable(
    MathTest
    pch.cpp
    pch.h
    permutation.cpp
    statistic.cpp
)

target_link_libraries(
    MathTest
    Math
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(MathTest)
