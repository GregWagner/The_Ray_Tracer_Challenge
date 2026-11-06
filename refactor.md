# Refactoring Notes

No code has been changed for this document. It records notes for future
maintenance work discovered while reviewing the project.

## 1. Clarity and readability improvements

- `src/tuple.cpp` has a duplicated `#include <cmath>` at the top of the file.
- `tuple.cpp`, `canvas.cpp`, and several tests repeat setter/constructor code manually.
  Constructors and accessors could be simpler and more consistent.
- `Material::operator==` is very long and repeatedly computes absolute
  differences. A small helper such as
  `approxEqual(double, double, double tolerance = ...)` would remove most of
  the duplication.
- `World` keeps both `lights`/`objects` collections and redundant
  `hasLight`/`light` state. This can become inconsistent; prefer one clearly
  documented representation (either a single `PointLight light` plus boolean,
  or `std::vector<PointLight> lights`), with accessors if both are needed.
- `Intersection` stores a raw `const Sphere *object`. Consider a clearly
  named ownership policy or document that lifetimes are managed by the caller.
  The `Hit` wrapper class exists only to paper over pointer/optional return
  ambiguity and could be replaced by one well-chosen modern return type.
- `Canvas` stores pixel data without alias documentation. If `pixelAt()`
  remains the public API, document zero-based `(x, y)` ordering. `writePixel()`
  has pointer and reference overloads that can be confusing.
- `Matrix` is fixed to a 4x4 layout even when representing 2x2 or 3x3
  matrices. A clearly fixed-size 4x4 type plus named smaller aliases, or a
  proper generic matrix, would make intent clearer.
- Test helper constructors in `matrix_tests.cpp` and elsewhere accept many
  numeric arguments in row-major order without named dimensions. Small
  initializer helpers or literals could make tests self-documenting.
- The test tree is now large (`tuple_tests.cpp` contains many unrelated
  scenarios). Consider grouping tests by chapter or feature:
  `canvas_tests.cpp`, `matrix_tests.cpp`, `ray_tests.cpp`, etc. Already
  partially done, but tuple tests remain a catch-all.
- Example programs duplicate world construction, rendering loops, and PPM
  file writing. A tiny shared example utility (canvas saving, sphere
  creation helpers) could reduce copy/paste.

## 2. Modern C++ best practices

- Use `std::initializer_list`, `std::array`, and `std::vector` consistently.
  Several structures use C-style arrays plus parallel `int` dimensions. A
  fixed-size matrix template or `std::array<double, 16>` would improve safety.
- Pass large objects by `const &` where they are only read. Many functions
  currently take `World`, `Matrix`, `Intersection`, `Ray`, and `Tuple` by
  value (for example `shade_hit`, `intersect_world`, `color_at`,
  `prepare_computations`).
- Use `nullptr` instead of `0` for pointer assignment/comparison.
- Use `constexpr` for math constants such as `EPSILON` and `PI`.
- Prefer constructors and in-class default member initializers over assigning
  every field manually in the constructor body.
- Prefer constructor delegation and `= default`/`= delete` rather than
  writing manual default constructors that only zero fields.
- Use `std::numeric_limits<double>::epsilon()` or a named tolerance instead
  of hard-coded `0.00001` throughout equality and comparisons.
- Use `std::min`, `std::max`, `std::clamp`, and `std::fabs` instead of
  handwritten branches.
- Use `std::optional<Intersection>` (or a pointer) consistently instead of
  the custom `Hit` type that tries to behave as both a pointer and an
  optional.
- Avoid C-style casts in favor of `static_cast`, `const_cast`, and
  `reinterpret_cast` as appropriate.
- Consider `enum class` for semantic categories such as operation type or
  shape type.
- Use scope-based file I/O (RAII) or helper functions for writing PPM files
  instead of manually opening and closing streams in every example.
- `std::pow` is acceptable, but hot functions such as `lighting()` and
  `canvasToPpm()` should avoid unnecessary temporary allocations.
- `std::endl` in example output can be replaced with `'\n'` to avoid
  flushing the stream after every line. clang-tidy already flags this.
- Avoid broad `using namespace` aliases introduced only for compatibility if
  only a small compatibility layer is needed.
- Consider moving example-specific code and headers (projectile, canvas
  rendering helpers, scene setup) into clearly separate directories, keeping
  the core library minimal.
- The core library currently exposes `raytracer_core` as a static target.
  Document its public headers and link requirements more explicitly.

## 3. clang-tidy diagnostics and compiler warnings

clang-tidy reports the following main categories (counts are approximate
from the last full run; exact source locations are in generated output):

- `[readability-math-missing-parentheses]`: 41 occurrences.
  Parenthesize all mixed `*`, `+`, `-` expressions, especially matrix and
  tuple math in `src/matrix.cpp` and `src/tuple.cpp`.
- `[readability-simplify-boolean-expr]`: 10 occurrences.
  Replace constructs such as `if (cond == true) return true; return false;`
  with `return cond;`. This appears throughout `Tuple` and intersection
  helper code.
- `[readability-use-std-min-max]`: 8 occurrences.
  Use `std::min`/`std::max` instead of manual if/else comparisons
  (for example canvas pixel clamping in `src/canvas.cpp`).
- `[performance-unnecessary-value-param]`: 8 occurrences.
  `World`, `Matrix`, and other aggregate parameters should be passed by
  `const &` when only read.
- `[bugprone-easily-swappable-parameters]`: 6 occurrences.
  Functions such as `Matrix::Matrix(...)`, `submatrix(...)`, and
  `viewTransform(...)` take adjacent similar-type arguments. Consider
  named/guarded types or at least documentation.
- `[bugprone-misplaced-widening-cast]`: 3 occurrences.
  Fix integer-to-size_t conversions in `src/world.cpp`.
- `[bugprone-implicit-widening-of-multiplication-result]`: 1 occurrence.
  Widen before multiplication in `src/matrix.cpp`.
- `[readability-redundant-nested-if]`: 1 occurrence.
- `[readability-make-member-function-const]`: 1 occurrence
  (`Matrix::RowProxy::operator[]`).
- `[readability-function-cognitive-complexity]`: 1 occurrence.
  Reduce complexity in the function flagged by clang-tidy.
- `[readability-duplicate-include]`: occurrences in `src/tuple.cpp` and
  `tests/tuple_tests.cpp` (duplicate `<cmath>`).
- `[readability-container-size-empty]`: 1 occurrence in `src/world.cpp`
  (`size() == 0` should be `empty()`).
- `[readability-identifier-length]`: historically flagged short parameter
  names such as `x`, `y`, `z`, and `t`; currently disabled in
  `.clang-tidy`. If this check is re-enabled, rename or suppress locally.
- `[readability-trailing-comma]`: several matrix test initializer lists
  should add trailing commas.

Compiler warnings also include:

- sign-conversion warnings in `src/canvas.cpp` from implicit `int` to
  `std::size_t`.
- any remaining `-Wconversion` issues from integer/floating-point mixing in
  matrix indexing and loop counters.
- potential pedantic warnings if any non-standard extensions are reintroduced.
  The code currently avoids anonymous structs in unions to stay ISO C++.

## 4. Tests

- Test names are mostly descriptive. Some scenario translations could use
  more distinctive case names rather than generated ones such as
  `ATupleWithWEqaulTo1IsAPoint`.
- A few tests use `EXPECT_TRUE(result == ...)` with an epsilon equality
  operator. Direct `EXPECT_NEAR` comparisons are usually clearer for
  floating-point values.
- Some temporary/debug test scaffolding should remain removed.
- Shared test helper functions for constructing matrices from lists could
  improve readability and reduce repeated initializer lists.
- Tests that construct `std::string` expected values by concatenation are
  difficult to maintain. Consider raw string literals or helper functions
  for PPM expectations.
- Test coverage for examples is absent. At least smoke tests that the example
  executables run and produce output would help.
- The CMake `gtest_discover_tests()` setup is good, but disabling automatic
  test discovery in restricted environments could be considered.

## 5. Build and tooling

- `CMAKE_CXX_CLANG_TIDY` is set automatically when clang-tidy is found.
  This makes every build slower and can surprise new contributors.
  Consider making it an explicit option, for example `ENABLE_CLANG_TIDY`.
- The `format` target rewrites files in place. It is useful, but should be
  documented in the README along with formatting expectations.
- `.gitignore` now ignores `*.ppm`. Keep generated example output outside
  the source tree where possible, or name output files explicitly.
- The project has many example programs. The README should document
  available targets and expected outputs.
- No continuous integration configuration is present. A simple CI workflow
  running `cmake --build` and `ctest` would catch regressions.
- All source files should include their associated header first, followed by
  standard headers, with no duplicates. `src/tuple.cpp` currently violates
  this with a duplicate `<cmath>` include.

## 6. Suggested refactoring order

1. Remove duplicate includes and trivial formatting issues.
2. Introduce `approxEqual()` and simplify all `operator==` implementations.
3. Pass read-only aggregates by `const &`.
4. Simplify `World` state and `Material` equality.
5. Replace handwritten `if`/ternary logic with standard algorithms and
   containers where appropriate.
6. Replace the custom `Hit` type with `std::optional<Intersection>` or a
   pointer.
7. Simplify the duplicated 2/3/4-dimensional matrix storage model.
8. Apply clang-tidy fixes in small batches, running `ctest` after each
   batch.
9. Add integration smoke tests for examples and CI.
