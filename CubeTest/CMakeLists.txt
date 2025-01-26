add_executable(
    CubeTest
    corners.cpp
    cube2x2.cpp
    cube3x3.cpp
    cube4x4.cpp
    cube5x5.cpp
    edges_center.cpp
    edges_side.cpp
    faces_center.cpp
    faces_side.cpp
    pch.cpp
    random.cpp
    twist.cpp
)

target_precompile_headers(CubeTest PRIVATE pch.h)

target_link_libraries(
    CubeTest
    Cube
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(CubeTest)
