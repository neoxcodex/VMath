# 3D Graphics Engine (From Scratch)

A custom C++ graphics engine built to understand the low-level mechanics of 3D rendering, lighting, and raycasting. This project avoids standard math libraries (like GLM) to focus on a manual implementation of linear algebra and engine architecture.

## 🛠 Project Objectives
* **Custom Graphics Pipeline:** Build a renderer using C++ and OpenGL.
* **Zero-Dependency Math:** Manual implementation of all linear algebra and geometric logic.
* **Raycasting & Lighting:** Implementation of 3D lighting models and ray-intersection logic from the ground up.
* **Architecture Study:** Deep dive into memory management and engine design patterns.

---

## 📐 Phase 1: Vector Math Library (VMath)

The foundation of the engine is a specialized math library focused on N-dimensional flexibility and optimized 2D/3D operations.

### 1. Linear Algebra Capabilities
* Basic vector arithmetic (Addition, Subtraction, Scalar Multiplication).
* Dot and Cross products.
* Matrix operations: Gaussian Elimination and Gauss-Jordan Method for solving linear systems.
* Transformations and Projections.

### 2. Namespace Architecture
To balance generalization with performance, the library is split into three scopes:
* `dimN`: Generalized N-dimensional vectors (intended for future AI/Neural Network utility).
* `dim3`: Specialized and optimized for 3D graphics.
* `dim2`: Specialized and optimized for 2D graphics and UI.

### 3. Safety & Error Handling
Sadly, there is none
It is expected that the programmer handles these....
---

## 🏗 Planned Roadmap
* **Phase 1:** Math Library (Current)
* **Phase 2:** OpenGL Context & Shader Abstraction
* **Phase 3:** 3D Lighting (Phong/Blinn-Phong) & Material Systems
* **Phase 4:** Raycasting & Collision Detection Engine

## 💻 Tech Stack
* **Language:** C++
* **API:** OpenGL
* **Dependencies:** Minimal (GLFW/GLEW or GLAD for windowing/loading only)


PS Some of this README is AI cause I didn't know the technical terms; To make it clear, none of the code in the codebase is vibe-coded...

Please dont hate on me I am a beginner and if the code is dogwater please help...
