add_executable(raytracer_tests
    tuple_tests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/tuple.cpp
)

target_include_directories(raytracer_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(raytracer_tests PRIVATE
    GTest::gtest_main
)

target_compile_features(raytracer_tests PRIVATE cxx_std_20)
raytracer_enable_strict_warnings(raytracer_tests)

include(GoogleTest)
gtest_discover_tests(raytracer_tests)