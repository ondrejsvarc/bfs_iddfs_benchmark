cmake_minimum_required(VERSION 3.15)
project(bfs_iddfs_benchmark)

set(CMAKE_CXX_STANDARD 20)

# force release build
set(CMAKE_BUILD_TYPE "Release")
# enable more warnings
add_compile_options("-Wall" "-Wextra" "-Wpedantic")
# target the instruction set of the current CPU
add_compile_options("-march=native")
# enable LTO
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

find_package(OpenMP REQUIRED)
link_libraries(OpenMP::OpenMP_CXX)

add_executable(bfs_iddfs_benchmark "src/main.cpp" "src/algorithms/bfs_solver.cpp" "src/algorithms/iddfs_solver.cpp" "src/generators/maze_generator.cpp"
        "src/generators/sat_generator.cpp" "src/generators/hanoi_generator.cpp" "src/problem_loader.cpp" "src/algorithm_benchmark.cpp")
