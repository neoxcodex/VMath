cmake_minimum_required(VERSION 3.20)

project(MyCppProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- automatically include all cpp files in src ----
file(GLOB SOURCES "src/*.cpp")

add_executable(MyCppProject ${SOURCES})

target_include_directories(MyCppProject
  PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(MyCppProject
  PRIVATE
    -Wall -Wextra -Wpedantic
)
