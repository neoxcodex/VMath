cmake_minimum_required(VERSION 3.20)
project(VMathVisualizer VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Find GLFW (Crucial for linking on Linux)
find_package(glfw3 REQUIRED)

file(GLOB SOURCES "src/*.cpp")
set(GLAD_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/src/glad.c")

add_executable(VMathVisualizer ${SOURCES} ${GLAD_SOURCE})

# 2. Refined Include Paths
target_include_directories(VMathVisualizer
  PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/deps/glad/include
)

# 3. Use the formal GLFW target
target_link_libraries(VMathVisualizer
  PRIVATE
    glfw      # or glfw3 if using find_package
    GL
    ${CMAKE_DL_LIBS} # More portable than just 'dl'
    pthread
)

target_compile_options(VMathVisualizer
  PRIVATE
    -Wall -Wextra -Wpedantic
)
