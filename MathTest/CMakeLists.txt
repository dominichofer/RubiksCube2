add_executable(
    MathTest
    pch.cpp
    permutation.cpp
    statistic.cpp
)

target_precompile_headers(MathTest PRIVATE pch.h)

target_link_libraries(
    MathTest
    Math
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(MathTest)
