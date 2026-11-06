cmake_minimum_required(VERSION 3.16)
project(RayTracer
    VERSION 0.1.0
    DESCRIPTION "C++ Ray Tracer based on The Ray Tracing Challenge"
    LANGUAGES CXX
)

# C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile commands for clang-tidy / IDEs
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Strict warnings helper
function(raytracer_enable_strict_warnings target)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${target} PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Werror
            -Wconversion
            -Wsign-conversion
            -Wnull-dereference
            -Wdouble-promotion
            -Wformat=2
            -Wunused
            -Wshadow
            -Wimplicit-fallthrough
        )
    elseif(MSVC)
        target_compile_options(${target} PRIVATE /W4 /WX /permissive-)
    endif()
endfunction()

# Options
option(BUILD_TESTING "Build unit tests" ON)

# clang-tidy
find_program(CLANG_TIDY_EXE NAMES clang-tidy)
if(CLANG_TIDY_EXE)
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
endif()

# clang-format target
find_program(CLANG_FORMAT_EXE NAMES clang-format)
if(CLANG_FORMAT_EXE)
    file(GLOB_RECURSE CLANG_FORMAT_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.[ch]pp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.[ch]pp"
        "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.[ch]pp"
    )
    add_custom_target(format
        COMMAND ${CLANG_FORMAT_EXE} -i ${CLANG_FORMAT_SOURCES}
        COMMENT "Running clang-format"
    )
endif()

# GoogleTest via FetchContent
include(FetchContent)
if(BUILD_TESTING)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    # Prevent overriding the parent project's compiler/linker settings on Windows.
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    enable_testing()
    add_subdirectory(tests)
endif()

add_library(raytracer_core STATIC
    src/tuple.cpp
    src/projectile.cpp
    src/canvas.cpp
    src/matrix.cpp
    src/ray.cpp
    src/intersection.cpp
    src/point_light.cpp
    src/material.cpp
    src/lighting.cpp
    src/world.cpp
    src/camera.cpp
)
target_include_directories(raytracer_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_features(raytracer_core PUBLIC cxx_std_20)
raytracer_enable_strict_warnings(raytracer_core)

add_executable(projectile_example
    examples/projectile/main.cpp
)
target_link_libraries(projectile_example PRIVATE raytracer_core)
target_compile_features(projectile_example PRIVATE cxx_std_20)
raytracer_enable_strict_warnings(projectile_example)

add_executable(trajectory_example
    examples/trajectory/main.cpp
)
target_link_libraries(trajectory_example PRIVATE raytracer_core)
target_compile_features(trajectory_example PRIVATE cxx_std_20)
raytracer_enable_strict_warnings(trajectory_example)

add_executable(clock_example
    examples/clock/main.cpp
)
target_link_libraries(clock_example PRIVATE raytracer_core)
target_compile_features(clock_example PRIVATE cxx_std_20)
raytracer_enable_strict_warnings(clock_example)

add_executable(world_scene_example
    examples/world_scene/main.cpp
)
target_link_libraries(world_scene_example PRIVATE raytracer_core)
target_compile_features(world_scene_example PRIVATE cxx_std_20)
raytracer_enable_strict_warnings(world_scene_example)

add_executable(ray_sphere_example
    examples/ray_sphere/main.cpp
)
target_link_libraries(ray_sphere_example PRIVATE raytracer_core)
target_compile_features(ray_sphere_example PRIVATE cxx_std_20)
raytracer_enable_strict_warnings(ray_sphere_example)

add_executable(ray_sphere_with_lighting_example
    examples/ray_sphere_with_lighting/main.cpp
)
target_link_libraries(ray_sphere_with_lighting_example PRIVATE raytracer_core)
target_compile_features(ray_sphere_with_lighting_example PRIVATE cxx_std_20)
raytracer_enable_strict_warnings(ray_sphere_with_lighting_example)