add_executable(raytracer_tests
    tuple_tests.cpp
    canvas_tests.cpp
    matrix_tests.cpp
    ray_tests.cpp
    sphere_tests.cpp
)

target_link_libraries(raytracer_tests PRIVATE
    raytracer_core
    GTest::gtest_main
)

target_compile_features(raytracer_tests PRIVATE cxx_std_20)
raytracer_enable_strict_warnings(raytracer_tests)

include(GoogleTest)
gtest_discover_tests(raytracer_tests)