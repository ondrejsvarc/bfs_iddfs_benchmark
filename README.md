# BFS and IDDFS Benchmark

This project implements and benchmarks Breadth-First Search (BFS) and Iterative Deepening Depth-First Search (IDDFS) algorithms, both sequential and parallel, on different problems:

*   **Maze Solving:** Finding a path from a start to a goal in a randomly generated maze.
*   **SAT Problem Solving:** Finding a satisfying assignment for a Boolean formula in Conjunctive Normal Form (CNF).
*   **Hanoi Towers Problem:** Finding the sequence of moves to solve the classic Hanoi Towers puzzle.

The project also includes a simple framework for generating these problems and saving/loading them in a basic JSON format.

## Project Structure

*   **`/` (Root Directory):**
    *   `CMakeLists.txt`: CMake configuration file for building the project.
    *   `README.md`: This file, providing an overview and instructions.
*   **`/src`:** Contains the source code for the application.
    *   `main.cpp`: Main entry point of the program, handles argument parsing and problem solving/generation.
    *   **`/algorithms`:** Contains the implementations of the search algorithms.
        *   `bfs_solver.h/cpp`: Breadth-First Search (BFS) solver (sequential and parallel).
        *   `iddfs_solver.h/cpp`: Iterative Deepening Depth-First Search (IDDFS) solver (sequential and parallel).
        *   `solver.h`: Abstract base class for solvers.
    *   **`/generators`:** Contains the generators for different problem types.
        *   `maze_generator.h/cpp`: Generates random maze problems.
        *   `sat_generator.h/cpp`: Generates random SAT problems in CNF.
        *   `hanoi_generator.h/cpp`: Generates the Hanoi Towers problem.
        *   `generator.h`: Abstract base class for problem generators.
    *   `problem_loader.h/cpp`: Handles saving and loading problems to/from JSON-like files.
    *   `algorithm_benchmark.h/cpp`: Class for running and benchmarking the different algorithms.
    *   `state.h`: Abstract base class representing a state in a search problem.
    *   `algorithm_result.h` Header defining the `algorithm_result` struct and `algorithm_type` enum.

## Help Page (Visualized)

Usage: ./problem_solver [OPTIONS]

Options:

  -m, --maze             Solve a maze problem.
                         If -g is not used, generates a default maze (width: 69, height: 69, seed: 8).

  -s, --sat              Solve a SAT problem.
                         If -g is not used, generates a default SAT problem (variables: 14, clauses: 9, max literals/clause: 4, seed: 1).

  -h, --hanoi            Solve a Hanoi Towers problem.
                         If -g is not used, generates a default Hanoi problem (pegs: 3, discs: 4).

  -f, --file <filename>  Load problem from file.
                         The file should be in the JSON-like format described in the README.

  -g, --generate         Generate a problem interactively.
                         The program will prompt for the problem type and parameters.
                         Cannot be used with algorithm selection options (-P, -S, --bfs, --iddfs).

  -P, --parallel         Run only parallel algorithms (BFS_PAR, IDDFS_PAR).
                         Cannot be used with -S or -g.

  -S, --sequential       Run only sequential algorithms (BFS_SEQ, IDDFS_SEQ).
                         Cannot be used with -P or -g.

  --bfs                  Run only BFS algorithms (BFS_SEQ, BFS_PAR).
                         Cannot be used with --iddfs or -g.

  --iddfs                Run only IDDFS algorithms (IDDFS_SEQ, IDDFS_PAR).
                         Cannot be used with --bfs or -g.

  -H, --help             Display this help message.

Examples:

  # Generate a maze problem with width 15, height 15, and seed 777, then save it to maze_15x15.json:
  ```
  ./problem_solver -g -m
  Enter width (odd number >= 5): 15
  Enter height (odd number >= 5): 15
  Enter seed: 777
  # ... (maze visualization) ...
  Save problem to file? (yes/no): yes
  Enter filename: maze_15x15.json
  ```

  # Solve the maze problem from the file 'maze_15x15.json' using sequential BFS:
  ```
  ./problem_solver -f maze_15x15.json -S --bfs
  ```

  # Solve a SAT problem with default parameters using parallel IDDFS:
  ```
  ./problem_solver -s -P --iddfs
  ```

  # Solve the Hanoi Towers problem with default parameters using all algorithms (sequential and parallel):
  ```
  ./problem_solver -h
  ```

  # Generate a SAT problem with 15 variables, 30 clauses, max 4 literals per clause, and seed 111, then save to sat_15_30_4.json
  ```
  ./problem_solver -g -s
  Enter number of variables: 15
  Enter number of clauses: 30
  Enter maximum number of literals per clause: 4
  Enter seed: 111
  # ... (SAT problem printed to console) ...
  Save problem to file? (yes/no): yes
  Enter filename: sat_15_30_4.json
  ```

  # Generate a Hanoi Towers problem with 4 pegs and 6 discs, then save to hanoi_4_6.json
  ```
  ./problem_solver -g -h
  Enter number of pegs (>= 3): 4
  Enter number of discs (>= 1): 6
  # ... (Hanoi problem state printed to console) ...
  Save problem to file? (yes/no): yes
  Enter filename: hanoi_4_6.json
  ```

  # Solve SAT problem from file sat_15_30_4.json using all algorithms
  ```
  ./problem_solver -f sat_15_30_4.json
  ```

  # Show this help page
  ```
  ./problem_solver -H
  ```

## Compilation and Running Instructions

This project uses CMake for building. You will need a C++17 compatible compiler (or higher) and CMake (version 3.15 or higher). The project also uses OpenMP for parallelization.

### **General Instructions (All Operating Systems):**

1.  **Clone the repository:**
    ```bash
    git clone bfs_ihttps://github.com/ondrejsvarc/bfs_iddfs_benchmark.git
    cd bfs_iddfs_benchmark
    ```
2.  **Create a build directory:**
    ```bash
    mkdir build
    cd build
    ```

### **Linux:**

1.  **Install dependencies (if necessary):**
    ```bash
    sudo apt-get update  # For Debian/Ubuntu
    sudo apt-get install g++ cmake make libopenmp-dev # For Debian/Ubuntu

    # Or use equivalent commands for your distribution (e.g., yum for Fedora/CentOS)
    ```
2.  **Generate build files:**
    ```bash
    cmake .. -DCMAKE_BUILD_TYPE=Release
    ```
3.  **Compile:**
    ```bash
    make -j$(nproc) # Use all available cores
    ```
4.  **Run:**
    ```bash
    ./bfs_iddfs_benchmark [OPTIONS] 
    # For example: ./bfs_iddfs_benchmark -m -P --bfs
    ```

### **macOS:**

1.  **Install dependencies (if necessary):**
    ```bash
    brew update
    brew install gcc cmake llvm # llvm provides OpenMP
    ```
2.  **Generate build files (using GCC and OpenMP from Homebrew):**
    ```bash
    cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=/opt/homebrew/opt/gcc/bin/gcc-13 -DCMAKE_CXX_COMPILER=/opt/homebrew/opt/gcc/bin/g++-13 -DOpenMP_CXX_FLAGS="-fopenmp -Xpreprocessor -fopenmp /opt/homebrew/opt/libomp/lib/libomp.dylib -I/opt/homebrew/opt/libomp/include"
    ```
3.  **Compile:**
    ```bash
    make -j$(sysctl -n hw.ncpu) # Use all available cores
    ```
4.  **Run:**
    ```bash
    ./bfs_iddfs_benchmark [OPTIONS]
    ```

### **Windows (using MinGW-w64 and MSYS2):**

1.  **Install MSYS2:** Follow the instructions on the official website: [https://www.msys2.org/](https://www.msys2.org/)
2.  **Install dependencies:**
    ```bash
    pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake make mingw-w64-x86_64-openmp
    ```
3.  **Generate build files (using MinGW-w64):**
    *   Open the MSYS2 MinGW 64-bit terminal.
    *   Navigate to your `build` directory.
    ```bash
    cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
    ```
4.  **Compile:**
    ```bash
    mingw32-make -j<number_of_cores> # Replace <number_of_cores> with the number of cores you want to use
    ```
5.  **Run:**
    *   You might need to add the MinGW-w64 bin directory to your PATH environment variable or copy the necessary DLLs (e.g., `libgomp-1.dll`, `libstdc++-6.dll`, `libwinpthread-1.dll` from `<MSYS2_INSTALL_DIR>\mingw64\bin`) to the directory containing the executable.
    ```bash
    ./bfs_iddfs_benchmark.exe [OPTIONS]
    ```

**Note:**
* If you don't have super user privileges you might want to install dependencies to a local directory.
* If you prefer to use other tools (like Visual Studio), you'll need to adapt the build instructions accordingly. The key is to ensure that your compiler supports C++17 (or higher) and OpenMP, and that CMake can find the necessary libraries.

**Warning:**
* Solving large problem instances, especially with sequential algorithms, can take a significant amount of time.
  For large problems, it is recommended to use parallel algorithms (-P, --parallel) to leverage multi-core processors.
  Even with parallel algorithms, solving very large instances might still require considerable time and computational resources.
  Be mindful of the problem size and complexity when choosing algorithms and parameters.


## Benchmark Results

The following table shows the execution times (in seconds) of the different algorithms on various problem instances. The benchmarks were performed on a Windows 11 system with an **Intel Core i9-13900KF** processor on commit '6cac689'.

| Problem Type | Problem Configuration | BFS (Sequential) | BFS (Parallel) | IDDFS (Sequential) | IDDFS (Parallel) |
|---|---|---|---|---|---|
| SAT | 10 variables, 5 clauses, 3 literals/clause, seed 420 | 0.0435 | 0.0176 | 0.0095 | 0.0097 |
| SAT | 15 variables, 9 clauses, 3 literals/clause, seed 2 | 36.0034 | 0.9032 | 0.4688 | 0.3536 |
| SAT | 15 variables, 5 clauses, 7 literals/clause, seed 1 | 51.1371 | 0.7979 | 0.4335 | 0.3195 |
| MAZE | 49x49, seed 6 | 0.0124 | 0.0704 | 7.5354 | 3.9187 |
| MAZE | 67x25, seed 4 | 0.0021 | 0.0021 | 0.2942 | 0.2066 |
| HANOI | 3 pegs, 4 discs | 0.0002 | 0.0046 | 0.04741 | 0.0338 |
| HANOI | 4 pegs, 3 discs | 0.0002 | 0.003 | 0.0019 | 0.0024 |
| HANOI | 3 pegs, 5 discs | 0.0008 | 0.0081 | 198.57 | 92.1586 |

**Observations:**

* Parallel versions of BFS and IDDFS generally outperform their sequential counterparts, especially on larger problem instances.
* IDDFS tends to be significantly faster than BFS for the SAT problem, likely due to the depth-limited nature of the search, which helps prune the search space.
* For the Hanoi Towers problem with 3 pegs and 5 discs, both sequential and parallel IDDFS are much slower, which is likely due to the large search space and the overhead of iterative deepening.
* The performance of parallel algorithms can vary depending on the specific problem instance and the number of available cores.

**Note:** These results are specific to the hardware and software configuration used for the benchmark. Your results may vary depending on your system.
