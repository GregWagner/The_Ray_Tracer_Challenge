# The Ray Tracer Challenge

A C++20 / Qt-oriented implementation of Jamis Buck's _The Ray Tracing
Challenge_, built with CMake and GoogleTest.

## Build

```bash
cmake -S . -B build
cmake --build build
```

This builds the test executable and the example programs listed below.

## Run tests

```bash
ctest --test-dir build
```

## Run examples

```bash
./build/projectile_example
./build/trajectory_example
./build/clock_example
./build/ray_sphere_example
./build/ray_sphere_with_lighting_example
./build/world_scene_example
```

- `projectile_example` prints a text-based projectile trajectory.
- `trajectory_example` writes `trajectory.ppm`.
- `clock_example` writes `clock.ppm`.
- `ray_sphere_example` writes `ray_sphere.ppm`.
- `ray_sphere_with_lighting_example` writes
  `ray_sphere_with_lighting.ppm`.
- `world_scene_example` writes `world_scene.ppm` (renders at 1280x1024 and may
  take about a minute).

PPM files are ignored by Git (`*.ppm`).

## Code quality tools

- clang-tidy runs automatically during CMake builds when it is installed.
- Run `cmake --build build --target format` to apply `clang-format`.

## Project layout

- `include/` — header files (`tuple.hpp`, `matrix.hpp`, `ray.hpp`, etc.)
- `src/` — implementation files
- `tests/` — GoogleTest unit tests
- `examples/` — example programs
- `refactor.md` — notes for future refactoring work
- `AGENTS.md` — project conventions for agents/contributors

## Development conventions

See `AGENTS.md` for coding standards, precision rules, and test-driven
development guidance.