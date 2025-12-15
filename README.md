# Ray Tracer Challenge (C++17)

Project for implementing the exercises from *The Ray Tracer Challenge* using modern C++ and CMake.

### Build With Ninja (from the build directory)
```bash
cmake -S .. -G Ninja
cmake --build .
```


## Run
```bash
./build/raytracer
```

## Build and Run Tests (from the build directory)
```bash
cmake -S .. -DRAYTRACER_BUILD_TESTS=ON -G Ninja
cmake --build .
ctest --test-dir .
```

