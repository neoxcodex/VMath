cmake_minimum_required(VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(VMathLib VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Build Type Logic
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# 2. Find Dependencies
find_package(glfw3 REQUIRED)
find_package(OpenMP REQUIRED)
find_package(benchmark REQUIRED)

# 3. Sources
file(GLOB SOURCES "src/*.cpp")
set(GLAD_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/src/glad.c")

add_executable(VMathLib ${SOURCES} ${GLAD_SOURCE})

# 4. Include Paths
target_include_directories(VMathLib
  PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/deps/glad/include
)

# 5. Link Libraries
target_link_libraries(VMathLib
  PRIVATE
    pthread
    benchmark::benchmark
    glfw
    GL
    ${CMAKE_DL_LIBS}
    OpenMP::OpenMP_CXX
)

# 6. Flags
target_compile_options(VMathLib
  PRIVATE
    -Wall -Wextra -Wpedantic
    -Werror=return-type
    -Wfatal-errors

   $<$<CONFIG:Release>:
        -O3
        -march=native
        -ffast-math
        -fopenmp
        -mavx2
        -mfma
        -fvectorize
        -fslp-vectorize
    >
    $<$<CONFIG:Debug>:
        -g -O0
    >
)

# 7. GLAD specific (C, not C++)
set_source_files_properties(${GLAD_SOURCE} PROPERTIES COMPILE_FLAGS -w)
if(OpenMP_C_FOUND)
    target_link_libraries(VMathLib PRIVATE OpenMP::OpenMP_C)
endif()