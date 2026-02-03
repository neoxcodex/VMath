# 🚀 3D Graphics Engine (From Scratch)

A custom C++ graphics engine built to explore the low-level mechanics of 3D rendering, linear algebra, and engine architecture. This project avoids standard math libraries (like GLM) to focus on a manual implementation of all geometric logic and memory-efficient design.

## 🛠 Project Objectives
* **Custom Graphics Pipeline:** Designing a renderer using C++ and OpenGL.
* **Zero-Dependency Math:** Manual implementation of all linear algebra (Matrices, Vectors, and NDS functions).
* **VDebugger Architecture:** Designing a thread-isolated visual debugger for real-time memory monitoring.
Focusing on raw performance and high-precision constants.

---

## 📐 VMath Library (Current Progress)

The engine is powered by **VMath**, a library designed to scale from 2D graphics to N-dimensional datasets.

### 1. Namespace Architecture
To balance generalization with performance, the library is split into three scopes:
* `dimN`: Generalized algorithms for N-dimensional vectors using `std::vector<double>`.
* `dim3` & `dim2`: Specialized, optimized `float` structs for 3D/2D graphics and homogeneous coordinates.
* `NDSF` (Non-Dimension Specific Functions): Utility logic for `clamp`, `lerp`, and "Fuzzy" equality checks using a custom `EPSILON`.

### 2. Safety & Performance Philosophy
> **"Performance is Key."**
>
> Currently, the library does not use runtime error-checking or bounds-validation. This removes the CPU overhead associated with branching in high-frequency math loops. The programmer is expected to handle data validity, ensuring the engine remains as lean as possible. Thought, I do plan to implement some form of compile-time error handling. Note runtime error handling will never be added to this lib.

---

## 🏗 Planned Architecture: VDebugger

One of the unique features of this project is the **VDebugger** (as outlined in `concept.txt`). This system is designed to solve the difficulty of debugging 3D transformations in real-time.

### The Logic:
* **Pointer Registry:** Any vector in the main program can push its memory address (`&vector`) to a central registry.
* **Thread Isolation:** * **Math Thread:** Executes physics and transformations at full speed.
    * **Visualizer Thread:** A separate OpenGL thread that monitors the registry addresses.
* **Real-time Monitoring:** The visualizer checks for value changes at the registered memory addresses per frame, rendering the updated vectors in a 3D coordinate system.
* **Automatic Cleanup:** The `unregister` function is integrated into the vector's destructor. When a vector goes out of scope, it automatically removes itself from the registry to prevent null pointer access.

---

## 🏗 Roadmap
- [x] **Phase 1:** Linear Algebra Foundation (Vectors, Dot/Cross products).
- [x] **Phase 1.5:** Matrix Transformations (Rodrigues' Rotation Formula, Scale, Translation).
- [ ] **Phase 2:** OpenGL Context & Shader Abstraction.
- [ ] **Phase 3:** VDebugger Implementation (Multi-threaded Registry).
- [ ] **Phase 4:** Raycasting & Collision (Möller–Trumbore, AABB).

## 💻 Tech Stack
* **Language:** C++17 (or higher)
* **API:** OpenGL
* **Math:** VMath (Custom-built)

---

### 📝 Note
I am a 14-year-old student and a beginner in engine architecture. I am building this project to understand how 3D software works under the hood.

**If you find "dogwater" code or logic errors in the implementation, please raise an issue! I am eager to learn from experienced engineers.**
