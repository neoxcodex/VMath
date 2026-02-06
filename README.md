# VMath : Module 1 For a Future Graphics Engine
This is a mathematics library for graphics programming built from the ground up designed to be close to 0 overhead and is super fast. 
## Tech Stack & Dependencies:
 - C++ 20
 - nanobench (for benchmarking)
 - glad
 - glfw
 - opengl 3.3 core
## Architecture: (Library Present in include/VMath)

1. The library is divided into 3 Modules Math, Profiler and Visualizer
2. The Math module has has 6 sub-modules where dim2, dim3, dim4 refer to the dimension of the arguments that the functions and data structures support.
3. VMath3D, VMath2D, VMath3D+ are modules optimized for graphics programming
4. VMathN is for AI stuff, it is currently not being actively developed on, currently it is unoptimized and uses <vector> library
5. The Visualizer Module contains files for a separately threaded visual debugger which can be used to visually debug unexpected results (given the code compiles), it works on a pull and push registry using ImGui which displays all vectors which have been spawned in the program and you can toggle the vectors to be shown in the Camera Space, World Space, Screen Space (uv) in non-homogenous coordinates
6. The Profiler submodule is just a abstraction of the nanobench interface

## How to Install & Build
- Linux : Run following commands
- ### Clone Repo
- `git clone https://github.com/neoxcodex/VMath.git`
- ### Ubuntu/Debian
  `sudo apt install libglfw3-dev libopenmp-dev cmake`
  ### Arch 
  `sudo pacman -S glfw-x11 openmp cmake`
  ### Arch : Wayland
  `sudo pacman -S glfw-wayland openmp cmake`
  ### Fedora
  `sudo dnf install glfw-devel libomp-devel cmake`
  ### Build & Run Unit Test
  `./runner.sh`
  - Tested on Ubuntu LTS 22.04 and Omarchy
  - Compiled with -O3 and -ffast-math flags for release version

## Performace Vs GLM

### GLM Performance

|               ns/op |                op/s |    err% |          ins/op |          cyc/op |    IPC |         bra/op |   miss% |     total | benchmark
|--------------------:|--------------------:|--------:|----------------:|----------------:|-------:|---------------:|--------:|----------:|:----------
|                1.02 |      985,095,052.15 |    0.7% |            9.00 |            1.81 |  4.968 |           0.00 |   16.2% |      0.36 | `G4: glm::vec2::op+`
|                1.48 |      673,671,254.42 |    0.3% |           10.00 |            2.65 |  3.768 |           0.00 |   45.7% |      0.54 | `G7: glm::dot(vec2)`
|                1.98 |      504,239,788.99 |    0.2% |           17.00 |            3.55 |  4.784 |           0.00 |   28.1% |      0.71 | `G9: glm::normalize(vec2)`
|               19.43 |       51,468,198.52 |    1.9% |           95.00 |           34.65 |  2.741 |           7.00 |    0.0% |      6.48 | `G11: glm::angle(vec2)`
|                2.24 |      445,744,061.71 |    0.6% |           15.00 |            4.00 |  3.751 |           0.00 |   64.2% |      0.82 | `G14: glm::vec3::op+`
|                1.94 |      514,745,403.69 |    0.7% |            8.00 |            3.47 |  2.309 |           0.00 |   12.4% |      0.70 | `G18: glm::mat3(1.0f)`
|                4.21 |      237,555,286.51 |    2.2% |           30.00 |            7.49 |  4.004 |           0.00 |    8.7% |      1.51 | `G23: glm::mat3::op*`
|                2.52 |      397,535,275.99 |    5.9% |           12.00 |            4.46 |  2.688 |           0.00 |   66.3% |      0.96 | :wavy_dash: `G24: glm::dot(vec3)` (Unstable with ~32,563,057.6 iters. Increase `minEpochIterations` to e.g. 325630576)
|                3.85 |      259,844,829.84 |    1.8% |           24.00 |            6.87 |  3.495 |           0.00 |    7.6% |      1.38 | `G26: glm::normalize(vec3)`
|                3.19 |      313,040,017.20 |    0.9% |           22.00 |            5.70 |  3.857 |           0.00 |   65.1% |      1.15 | `G32: glm::cross`
|                5.88 |      169,930,217.66 |    0.8% |           51.00 |           10.51 |  4.852 |           0.00 |   62.9% |      2.12 | `G35: glm::mat3*mat3`
|               16.24 |       61,582,901.34 |    1.8% |           76.00 |           28.98 |  2.623 |           5.00 |    0.0% |      5.83 | `G37: glm::rotate(X)`
|                1.91 |      524,675,514.57 |    0.3% |           10.00 |            3.40 |  2.939 |           0.00 |   11.6% |      0.70 | `G44: glm::mat4(1.0f)`
|                9.03 |      110,753,539.21 |    1.5% |           23.00 |           16.12 |  1.427 |           0.00 |    5.4% |      3.24 | `G49: glm::translate`
|                7.84 |      127,559,261.41 |    1.1% |           20.00 |           14.00 |  1.429 |           0.00 |    3.3% |      2.81 | `G50: glm::scale`
|                2.13 |      468,910,377.28 |    0.4% |           16.00 |            3.81 |  4.199 |           0.00 |    8.1% |      0.77 | `G55: glm::mat4::op*`
|               20.64 |       48,461,169.38 |    0.5% |          127.00 |           36.85 |  3.447 |           0.00 |    2.1% |      7.39 | `G70: glm::mat4*mat4`
|               11.11 |       90,016,610.48 |    0.7% |           69.00 |           19.83 |  3.480 |           0.00 |    1.8% |      3.98 | `G69: glm::project`

### VMath Performance


|               ns/op |                op/s |    err% |          ins/op |          cyc/op |    IPC |         bra/op |   miss% |     total | benchmark
|--------------------:|--------------------:|--------:|----------------:|----------------:|-------:|---------------:|--------:|----------:|:----------
|                0.99 |    1,014,913,170.93 |    0.3% |            8.00 |            1.76 |  4.543 |           0.00 |   55.9% |      0.36 | `F1: NDSF::clamp`
|                1.58 |      632,345,220.94 |    0.7% |           11.00 |            2.82 |  3.894 |           0.00 |   67.6% |      0.57 | `F2: NDSF::epEqual`
|                1.86 |      538,498,087.07 |    1.0% |           14.00 |            3.32 |  4.218 |           0.00 |   55.9% |      0.67 | `F3: NDSF::lerp`
|                1.20 |      836,672,195.01 |    1.8% |            9.00 |            2.13 |  4.220 |           0.00 |   52.4% |      0.45 | `F4: dim2::Vec2::op+`
|                1.20 |      834,052,647.57 |    1.1% |            9.00 |            2.14 |  4.205 |           0.00 |   65.2% |      0.43 | `F5: dim2::Vec2::op-`
|                1.18 |      848,108,015.52 |    0.6% |            9.00 |            2.11 |  4.268 |           0.00 |   77.6% |      0.43 | `F6: dim2::Vec2::op*`
|                1.75 |      570,028,399.40 |    0.5% |           10.00 |            3.13 |  3.194 |           0.00 |   10.9% |      0.63 | `F7: dim2::dotProduct`
|                1.05 |      953,469,189.14 |    0.8% |            9.00 |            1.87 |  4.808 |           0.00 |   16.5% |      0.38 | `F8: dim2::magSquared`
|                2.64 |      379,291,610.76 |    0.6% |           20.00 |            4.71 |  4.247 |           1.00 |    0.0% |      0.95 | `F9: dim2::normalize`
|                1.70 |      586,905,504.35 |    1.0% |           12.00 |            3.04 |  3.947 |           0.00 |   10.2% |      0.62 | `F10: dim2::distanceSquared`
|               19.31 |       51,786,040.18 |    0.9% |           95.00 |           34.44 |  2.758 |           9.00 |    0.0% |      6.93 | `F11: dim2::angleRAD`
|               20.05 |       49,885,920.99 |    1.6% |           96.00 |           35.79 |  2.683 |           9.00 |    0.0% |      7.15 | `F12: dim2::angleDEG`
|                2.03 |      493,349,029.90 |    2.0% |           15.00 |            3.62 |  4.145 |           0.00 |   60.9% |      0.81 | `F13: dim2::lerp`
|                2.30 |      434,529,419.26 |    2.6% |           15.00 |            4.10 |  3.654 |           0.00 |   46.0% |      0.83 | `F14: dim3::Vec3::op+`
|                2.21 |      451,659,765.45 |    0.7% |           15.00 |            3.95 |  3.794 |           0.00 |    8.8% |      0.82 | `F15: dim3::Vec3::op-`
|                2.07 |      482,782,113.48 |    0.5% |           15.00 |            3.70 |  4.053 |           0.00 |    7.0% |      0.75 | `F16: dim3::Vec3::op*`
|                1.18 |      850,398,019.83 |    0.5% |            9.00 |            2.10 |  4.284 |           1.00 |    0.0% |      0.43 | `F17: dim3::Vec3::op==`
|                7.30 |      136,911,337.55 |    2.0% |           12.00 |           13.03 |  0.921 |           0.00 |    3.8% |      2.65 | `F18: dim3::Mat3::identity`
|               19.37 |       51,633,220.34 |    2.7% |          100.00 |           34.48 |  2.900 |           5.00 |    0.0% |      6.94 | `F19: dim3::Mat3::genRotator`
|               15.35 |       65,126,842.68 |    0.7% |           75.00 |           27.42 |  2.736 |           5.00 |    0.0% |      5.54 | `F20: dim3::Mat3::genRotationX`
|               15.77 |       63,424,240.54 |    0.8% |           75.00 |           28.08 |  2.671 |           5.00 |    0.0% |      5.69 | `F21: dim3::Mat3::genRotationY`
|               16.96 |       58,946,013.88 |    6.4% |           74.00 |           30.17 |  2.452 |           5.00 |    0.0% |      6.39 | :wavy_dash: `F22: dim3::Mat3::genRotationZ` (Unstable with ~32,563,057.6 iters. Increase `minEpochIterations` to e.g. 325630576)
|                8.00 |      124,938,445.97 |    8.4% |           24.00 |           14.23 |  1.687 |           0.00 |   46.7% |      2.98 | :wavy_dash: `F23: dim3::Mat3::op*` (Unstable with ~32,563,057.6 iters. Increase `minEpochIterations` to e.g. 325630576)
|                2.39 |      417,829,010.76 |    2.6% |           12.00 |            4.27 |  2.810 |           0.00 |   77.9% |      1.00 | `F24: dim3::dotProduct`
|                1.34 |      744,990,283.83 |    1.5% |           11.00 |            2.39 |  4.598 |           0.00 |   15.7% |      0.49 | `F25: dim3::magSquared`
|                4.57 |      218,661,575.94 |    9.4% |           27.00 |            8.15 |  3.314 |           1.00 |    0.0% |      1.69 | :wavy_dash: `F26: dim3::normalize` (Unstable with ~32,563,057.6 iters. Increase `minEpochIterations` to e.g. 325630576)
|                2.61 |      383,619,223.55 |   10.2% |           15.00 |            4.63 |  3.237 |           0.00 |   58.5% |      0.95 | :wavy_dash: `F27: dim3::distanceSquared` (Unstable with ~32,563,057.6 iters. Increase `minEpochIterations` to e.g. 325630576)
|               16.30 |       61,350,634.84 |    4.8% |          100.00 |           29.14 |  3.432 |           9.00 |    0.0% |      7.06 | `F28: dim3::angleRAD`
|               16.41 |       60,954,414.73 |    0.8% |          101.00 |           29.40 |  3.436 |           9.00 |    0.0% |      5.88 | `F29: dim3::angleDEG`
|                2.71 |      368,974,988.25 |    0.3% |           21.00 |            4.86 |  4.322 |           0.00 |   13.6% |      0.97 | `F30: dim3::scalarProject`
|                2.98 |      335,196,774.14 |    0.7% |           24.00 |            5.33 |  4.499 |           0.00 |   17.2% |      1.07 | `F31: dim3::vectorProject`
|                2.20 |      455,532,334.01 |    0.1% |           22.00 |            3.93 |  5.592 |           0.00 |   26.9% |      0.79 | `F32: dim3::crossProduct`
|                1.35 |      741,685,768.73 |    0.2% |           12.00 |            2.42 |  4.969 |           1.00 |    0.0% |      0.48 | `F33: dim3::epVectorEqual`
|                2.42 |      412,729,373.74 |    0.1% |           24.00 |            4.35 |  5.517 |           0.00 |    8.9% |      0.90 | `F34: dim3::lerp`
|                6.36 |      157,215,519.39 |    2.1% |           53.00 |           11.36 |  4.666 |           0.00 |   14.4% |      2.51 | `F35: dim3::matrixMultiply`
|               20.38 |       49,062,621.40 |    7.3% |          106.00 |           36.08 |  2.938 |           5.00 |    0.0% |      7.53 | :wavy_dash: `F36: dim3::rotationCustomAxis` (Unstable with ~32,563,057.6 iters. Increase `minEpochIterations` to e.g. 325630576)
|               13.47 |       74,251,994.76 |    2.2% |           73.00 |           23.99 |  3.043 |           5.00 |    0.0% |      5.23 | `F37: dim3::rotationXAxis`
|               13.20 |       75,740,298.52 |    1.4% |           72.00 |           23.57 |  3.054 |           5.00 |    0.0% |      4.85 | `F38: dim3::rotationYAxis`
|               13.85 |       72,227,793.05 |    1.9% |           74.00 |           24.70 |  2.996 |           5.00 |    0.0% |      5.08 | `F39: dim3::rotationZAxis`
|                1.17 |      856,932,122.95 |    1.5% |            9.00 |            2.08 |  4.322 |           1.00 |    0.0% |      0.43 | `F40: dim4::Vec4::op==`
|                1.18 |      848,566,099.77 |    1.8% |            8.00 |            2.10 |  3.818 |           0.00 |   20.9% |      0.43 | `F41: dim4::Vec4::op+`
|                1.21 |      824,719,389.35 |    0.8% |            8.00 |            2.16 |  3.700 |           0.00 |   16.9% |      0.44 | `F42: dim4::Vec4::op-`
|                1.16 |      860,896,537.96 |    0.7% |            8.00 |            2.07 |  3.864 |           0.00 |   80.5% |      0.42 | `F43: dim4::Vec4::op*`
|               12.30 |       81,280,811.10 |    1.3% |           14.00 |           21.90 |  0.639 |           0.00 |   43.8% |      4.39 | `F44: dim4::Mat4::identity`
|               20.42 |       48,972,084.48 |    2.7% |          107.00 |           36.32 |  2.946 |           5.00 |    0.0% |      8.30 | `F45: dim4::Mat4::genRotator`
|               13.79 |       72,508,005.98 |    7.6% |           76.00 |           24.40 |  3.115 |           5.00 |    0.0% |      5.21 | :wavy_dash: `F46: dim4::Mat4::genRotationX` (Unstable with ~32,563,057.6 iters. Increase `minEpochIterations` to e.g. 325630576)
|               27.05 |       36,964,546.20 |   11.3% |           76.00 |           47.36 |  1.605 |           5.00 |    0.0% |      9.53 | :wavy_dash: `F47: dim4::Mat4::genRotationY` (Unstable with ~32,563,057.6 iters. Increase `minEpochIterations` to e.g. 325630576)
|               20.20 |       49,493,484.74 |    8.6% |           76.00 |           35.85 |  2.120 |           5.00 |    0.0% |      8.01 | :wavy_dash: `F48: dim4::Mat4::genRotationZ` (Unstable with ~32,563,057.6 iters. Increase `minEpochIterations` to e.g. 325630576)
|               15.29 |       65,412,686.66 |    4.5% |           24.00 |           27.15 |  0.884 |           0.00 |   59.6% |      5.54 | `F49: dim4::Mat4::genTranslation`
|               14.36 |       69,648,377.43 |    2.0% |           21.00 |           25.55 |  0.822 |           0.00 |    9.5% |      5.19 | `F50: dim4::Mat4::genScaling`
|                2.21 |      452,377,552.45 |    2.8% |           15.00 |            3.94 |  3.808 |           0.00 |   29.4% |      0.81 | `F51: dim4::Mat4::homoToVec3`
|                1.30 |      769,249,690.78 |    1.4% |            9.00 |            2.32 |  3.882 |           0.00 |   13.8% |      0.48 | `F52: dim4::Mat4::Vec3toHomo`
|               11.33 |       88,298,206.27 |   21.3% |           23.00 |           20.14 |  1.142 |           0.00 |   29.0% |      3.71 | :wavy_dash: `F53: dim4::Mat4::genIntrinsic` (Unstable with ~32,563,057.6 iters. Increase `minEpochIterations` to e.g. 325630576)
|               15.26 |       65,514,239.39 |    2.1% |           73.00 |           26.88 |  2.716 |           2.00 |    0.0% |      5.53 | `F54: dim4::Mat4::genExtrinsic`
|                5.16 |      193,643,857.27 |    2.6% |           36.00 |            9.22 |  3.905 |           0.00 |   48.8% |      1.89 | `F55: dim4::Mat4::op*`
|                1.44 |      696,344,142.19 |    2.6% |           12.00 |            2.56 |  4.696 |           0.00 |   96.4% |      0.56 | `F56: dim4::dotProduct`
|                1.00 |      998,221,831.07 |    1.9% |           11.00 |            1.76 |  6.237 |           0.00 |   96.2% |      0.36 | `F57: dim4::magSquared`
|                1.21 |      826,701,984.04 |    2.8% |           12.00 |            2.13 |  5.641 |           0.00 |   95.8% |      0.43 | `F58: dim4::magnitude`
|                1.39 |      721,510,085.54 |    2.8% |           12.00 |            2.45 |  4.901 |           1.00 |    0.0% |      0.50 | `F59: dim4::epVectorEqual`
|                2.44 |      410,363,204.05 |    2.0% |           18.00 |            4.34 |  4.146 |           0.00 |   54.3% |      0.86 | `F60: dim4::normalize`
|                1.75 |      571,715,362.02 |    0.8% |           15.00 |            3.14 |  4.783 |           0.00 |   44.7% |      0.69 | `F61: dim4::lerp`
|               23.44 |       42,667,480.03 |    5.9% |           97.00 |           41.45 |  2.340 |           7.00 |    0.0% |      8.66 | :wavy_dash: `F62: dim4::angleRAD` (Unstable with ~32,563,057.6 iters. Increase `minEpochIterations` to e.g. 325630576)
|               23.30 |       42,910,955.18 |    3.9% |           98.00 |           41.37 |  2.369 |           7.00 |    0.0% |      8.53 | `F63: dim4::angleDEG`
|                1.37 |      731,138,644.26 |    5.0% |            9.00 |            2.43 |  3.707 |           0.00 |   90.7% |      0.51 | `F64: dim4::toVec4`
|               35.74 |       27,979,585.64 |    6.8% |          189.00 |           63.44 |  2.979 |          18.00 |    0.0% |     13.17 | :wavy_dash: `F65: dim4::calcFocalLength` (Unstable with ~32,563,057.6 iters. Increase `minEpochIterations` to e.g. 325630576)
|                0.37 |    2,710,609,964.34 |    2.0% |            4.00 |            0.66 |  6.082 |           0.00 |   74.1% |      0.14 | `F66: dim4::calcOffsets`
|                3.14 |      318,558,971.94 |    5.2% |           21.00 |            5.58 |  3.764 |           0.00 |   10.2% |      1.08 | :wavy_dash: `F67: dim4::cameraSpaceVecToImgSpace` (Unstable with ~32,563,057.6 iters. Increase `minEpochIterations` to e.g. 325630576)
|                0.37 |    2,699,676,131.96 |    3.3% |            2.00 |            0.66 |  3.037 |           0.00 |   92.9% |      0.14 | `F68: dim4::worldSpaceToCameraSpace`
|                0.39 |    2,542,962,130.08 |    4.9% |            4.00 |            0.70 |  5.753 |           0.00 |   92.5% |      0.14 | `F69: dim4::worldToScreen`
|               20.15 |       49,640,050.45 |    2.0% |          130.00 |           35.93 |  3.618 |           0.00 |    7.7% |      6.86 | `F70: dim4::matrixMultiply`
|                4.29 |      233,267,388.32 |    0.4% |           49.00 |            7.69 |  6.375 |           7.00 |    0.0% |      1.54 | `F71: dimN::magnitude`
|              138.95 |        7,196,789.92 |   12.7% |          924.00 |          247.33 |  3.736 |         191.00 |    0.0% |     50.58 | :wavy_dash: `F72: dimN::normalize` (Unstable with ~32,563,057.6 iters. Increase `minEpochIterations` to e.g. 325630576)