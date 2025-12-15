cmake_minimum_required(VERSION 3.16)

project(RayTracerChallenge
    VERSION 0.1.0
    DESCRIPTION "Ray tracer inspired by The Ray Tracer Challenge"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(RAYTRACER_ENABLE_WARNINGS "Enable compiler warnings" ON)

include(CTest)
option(RAYTRACER_BUILD_TESTS "Build tests" ${BUILD_TESTING})

set(raytracer_warnings "")
if(RAYTRACER_ENABLE_WARNINGS)
    if(MSVC)
        list(APPEND raytracer_warnings /W4 /permissive-)
    else()
        list(APPEND raytracer_warnings -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion)
    endif()
endif()

add_library(raytracer_lib
    src/lib/tuple.cpp
    src/lib/color.cpp
    src/lib/canvas.cpp
)
target_include_directories(raytracer_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_options(raytracer_lib PRIVATE ${raytracer_warnings})

add_executable(raytracer
    apps/raytracer_main.cpp
)
target_link_libraries(raytracer PRIVATE raytracer_lib)
target_compile_options(raytracer PRIVATE ${raytracer_warnings})

if(RAYTRACER_BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.3
    )
    FetchContent_MakeAvailable(catch2)

    add_subdirectory(tests)
endif()
