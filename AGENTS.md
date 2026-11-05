# AGENTS.md — Guidelines for AI Agents (OpenCode)

This file defines the project standards, architectural conventions, and development practices for AI agents working on this Qt 6 / C++ implementation of Jamis Buck's _The Ray Tracing Challenge_ (RTC).

---

## 1. Project Overview & Context

- **Goal**: Build a fully functional software ray tracer in C++20 using Qt 6, strictly adhering to the test-driven development (TDD) approach outlined in _The Ray Tracing Challenge_ (RTC).
- **Framework**: Qt 6 (Core, GUI, Widgets/QML as specified for rendering UI).
- **Build System**: CMake (minimum version 3.16+).
- **Testing Framework**: GoogleTest (GTest) or Qt Test.

---

## 2. Core Architectural & Code Conventions

### 2.1 C++ & Qt Standards

- Use **C++20** modern language features (`auto`, `constexpr`, concepts, smart pointers) where appropriate.
- Prefer Qt container types (`QVector`, `QString`, etc.) when interfacing with Qt API/UI elements, but standard library containers (`std::vector`, `std::array`) may be used in performance-critical core math/ray-tracing code.
- Use `double` or `float` consistently for floating-point calculations across standard math classes (Tuple, Matrix, Ray, etc.).

### 2.2 Math & Precision Rules

- All floating-point comparisons **must** use an explicit epsilon constant (e.g., `EPSILON = 0.00001` or `1e-5`) rather than direct `==` checks.
- Vector/Point representation:
  - A **Point** has $w = 1.0$.
  - A **Vector** has $w = 0.0$.
- Matrix transformations should be composable (e.g., translation, scaling, rotation) and support efficient matrix inversion.

### 2.3 Ray Tracing Challenge Structure

- Keep the core engine decoupled from Qt UI components to allow headless rendering, unit testing, and CLI execution.
- Ensure data structures map clearly to the chapters in RTC:
  1. Tuples, Points, Vectors
  2. Canvas & Color operations
  3. Matrices & Transformations
  4. Rays & Spheres (Intersections)
  5. Light & Shading (Phong Reflection Model)
  6. World, Camera, and Scenes
  7. Shadows, Shapes, Patterns, Reflection, Refraction, and Acceleration Structures (Bounding Volume Hierarchies).

---

## 3. Agent Operating Rules

When fulfilling prompts or implementing features in this repository:

1. **Follow Test-Driven Development (TDD)**:
   - Write or update unit tests _first_ or in tandem with feature code based on the Cucumber/Gherkin scenarios provided in _The Ray Tracing Challenge_.
   - Ensure all unit tests pass before declaring a task complete.

2. **Modular File Structure**:
   - Keep header files (`.h` / `.hpp`) and implementation files (`.cpp`) clean and well-scoped.
   - Put math primitives inside a core namespace (e.g., `RTC::Core` or `RayTracer`).

3. **Qt Integration & Output**:
   - Canvas pixels should be exportable to `QImage` or PPM files (for chapter milestones).
   - Ensure any long-running render operations execute asynchronously (e.g., via `QThread`, `QtConcurrent`, or worker threads) so as not to block the Qt main GUI loop.

4. **Performance & Memory**:
   - Avoid unnecessary copies in inner loop ray-intersection checks; pass objects by `const&` or standard view structures.
   - Prefer value semantics for lightweight math types (`Tuple`, `Matrix4x4`, `Ray`, `Color`).

---

## 4. CMake & Dependencies

- `CMakeLists.txt` must clearly separate standard core libraries, test executables, and the Qt UI app.
- Ensure dependencies are modernly target-linked (`target_link_libraries(...)`).
