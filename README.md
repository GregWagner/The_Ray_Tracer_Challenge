# The Ray Tracer Challenge

A C++20 / Qt-oriented implementation of Jamis Buck's _The Ray Tracing Challenge_, built with CMake and GoogleTest.

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run tests

```bash
ctest --test-dir build
```

## Project layout

- `include/` — header files (e.g. `tuple.hpp`)
- `src/` — implementation files
- `tests/` — GoogleTest unit tests

## Development conventions

See `AGENTS.md` for coding standards, precision rules, and test-driven development guidance.