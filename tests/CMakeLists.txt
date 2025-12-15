add_executable(raytracer_tests
    tuple_tests.cpp
)

target_link_libraries(raytracer_tests
    PRIVATE
        raytracer_lib
        Catch2::Catch2WithMain
)

include(Catch)
catch_discover_tests(raytracer_tests)

