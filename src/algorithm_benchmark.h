/**
 * @file algorithm_benchmark.h
 * @brief Declares the algorithm_benchmark class, which is used to benchmark different search algorithms.
 *
 * This header file defines the `algorithm_benchmark` class. This class provides functionality to run
 * and benchmark different search algorithms (BFS, IDDFS) in both sequential and parallel implementations.
 * It measures the execution time of each algorithm and stores the results.
 *
 * @author Ondrej Svarc
 * @date Created on 12/31/2024
 */

#ifndef ALGORITHM_BENCHMARK_H
#define ALGORITHM_BENCHMARK_H

#pragma once

#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <stdexcept>
#include <functional>
#include <climits>
#include <algorithm>
#include <queue>
#include <map>

#include "algorithms/bfs_solver.h"
#include "algorithms/iddfs_solver.h"
#include "state.h"


/**
 * @brief Enum defining the types of algorithms available for benchmarking.
 */
enum class algorithm_type : int {
    BFS_SEQ,     ///< Sequential Breadth-First Search
    BFS_PAR,     ///< Parallel Breadth-First Search
    IDDFS_SEQ,   ///< Sequential Iterative Deepening Depth-First Search
    IDDFS_PAR    ///< Parallel Iterative Deepening Depth-First Search
};

/**
 * @brief Structure to store the result of an algorithm's execution.
 */
struct algorithm_result {
    algorithm_type algorithm_type; ///< The type of the algorithm.
    std::string algorithm_name;    ///< The name of the algorithm.
    std::chrono::duration<double> duration; ///< The execution time of the algorithm in seconds.
    bool found_solution;            ///< Flag indicating whether a solution was found.
};


/**
 * @brief Class for benchmarking search algorithms.
 *
 * This class runs specified search algorithms on a given initial state, measures their execution time,
 * and stores the results. It supports running BFS and IDDFS algorithms in both sequential and parallel modes.
 */
class algorithm_benchmark {
public:
    /**
     * @brief Constructor for the algorithm_benchmark class.
     *
     * @param initial_state The initial state of the problem.
     * @param algorithm_mask A bitmask specifying which algorithms to run.
     *                       - 1 (BFS_SEQ):  Run sequential BFS.
     *                       - 2 (BFS_PAR):  Run parallel BFS.
     *                       - 4 (IDDFS_SEQ): Run sequential IDDFS.
     *                       - 8 (IDDFS_PAR): Run parallel IDDFS.
     *                       - Combinations are possible (e.g., 1 | 2 to run both BFS versions).
     */
    algorithm_benchmark ( const state_pointer initial_state, int algorithm_mask )
        : initial_state ( initial_state ), algorithm_mask ( algorithm_mask ) {}

    /**
     * @brief Solves the problem using the selected algorithms and records the results.
     *
     * This function runs the algorithms specified in the `algorithm_mask` on the `initial_state`.
     * It measures the time taken by each algorithm and stores the result in the `results` vector.
     */
    void solve ();

    /**
     * @brief Solves the problem using the Breadth-First Search (BFS) algorithm.
     *
     * @param parallel If true, runs the parallel version of BFS; otherwise, runs the sequential version.
     * @return An algorithm_result struct containing the results of the BFS execution.
     */
    algorithm_result solve_bfs ( bool parallel );

    /**
     * @brief Solves the problem using the Iterative Deepening Depth-First Search (IDDFS) algorithm.
     *
     * @param parallel If true, runs the parallel version of IDDFS; otherwise, runs the sequential version.
     * @return An algorithm_result struct containing the results of the IDDFS execution.
     */
    algorithm_result solve_iddfs ( bool parallel );

private:
    /**
     * @brief Runs a specified algorithm, measures its execution time, and prints a message to the console.
     *
     * @param name The name of the algorithm to be displayed.
     * @param algorithm A function object (lambda or functor) that encapsulates the algorithm to be run.
     * @return An algorithm_result struct containing the results of the algorithm execution.
     */
    algorithm_result run_algorithm ( const std::string &name, std::function<algorithm_result()> algorithm );

    /**
     * @brief Prints the results of all executed algorithms.
     *
     * Iterates through the `results` vector and prints the name, execution time, and whether a solution was found
     * for each algorithm.
     */
    void print_results () const;

    state_pointer initial_state; ///< The initial state of the problem.
    int algorithm_mask;          ///< A bitmask specifying which algorithms to run.
    std::vector<algorithm_result> results; ///< A vector to store the results of each algorithm.
};

#endif //ALGORITHM_BENCHMARK_H
