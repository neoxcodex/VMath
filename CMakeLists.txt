cmake_minimum_required(VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(VMathVisualizer VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Force Release mode if not specified (No more 10k ns overhead!)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# 2. Find GLFW
find_package(glfw3 REQUIRED)
find_package(OpenMP REQUIRED)
file(GLOB SOURCES "src/*.cpp")
set(GLAD_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/src/glad.c")

add_executable(VMathVisualizer ${SOURCES} ${GLAD_SOURCE})

# 3. Refined Include Paths
target_include_directories(VMathVisualizer
  PRIVATE
    ${PROJECT_SOURCE_DIR}/include

    ${PROJECT_SOURCE_DIR}/deps/glad/include
)

# 4. Link Libraries
target_link_libraries(VMathVisualizer
  PRIVATE
    glfw
    GL
    ${CMAKE_DL_LIBS}
    pthread
    OpenMP::OpenMP_CXX  # <--- LINK OPENMP HERE
)
# 5. Strict & Fast Flags
target_compile_options(VMathVisualizer
  PRIVATE
    # Base flags for everyone
    -Wall -Wextra -Wpedantic
    -Werror=return-type
    -Wfatal-errors

    # Release-specific "Nitro" flags
    $<$<CONFIG:Release>:
        -O3
        -march=native
        -ffast-math
        -fopenmp        # <--- Use the universal flag for GCC/Clang compatibility
    >
)

# Crucial: GLAD is C, not C++. Don't let C++ flags leak into it.
set_source_files_properties(${GLAD_SOURCE} PROPERTIES COMPILE_FLAGS -w)
if(OpenMP_C_FOUND)
    target_link_libraries(VMathVisualizer PRIVATE OpenMP::OpenMP_C)
endif()
