/**
 * @file bfs_solver.h
 * @brief Declares the bfs_solver class, which implements the Breadth-First Search (BFS) algorithm.
 *
 * This header file defines the `bfs_solver` class, which inherits from the `solver` abstract base class.
 * It provides both sequential and parallel implementations of the BFS algorithm for solving state-space search problems.
 *
 * @author Ondrej Svarc
 * @date Created on 12/29/2024
 */

#ifndef BFS_SOLVER_H
#define BFS_SOLVER_H

#pragma once

#include "solver.h"
#include <queue>
#include <unordered_set>
#include <utility>

/**
 * @brief Implements the Breadth-First Search (BFS) algorithm for solving state-space problems.
 *
 * This class provides both sequential (`solve_seq`) and parallel (`solve_par`) implementations of the BFS algorithm.
 * It inherits from the `solver` abstract base class.
 */
class bfs_solver : public solver {
public:
    /**
     * @brief Constructor for the bfs_solver class.
     *
     * @param initial_state The initial state of the problem.
     */
    explicit bfs_solver( const state_pointer initial_state ) : solver( initial_state ) {};

    /**
     * @brief Solves the problem sequentially using the BFS algorithm.
     *
     * @return A state_pointer to the solution state, or nullptr if no solution is found.
     */
    state_pointer solve_seq () override;

    /**
     * @brief Solves the problem in parallel using the BFS algorithm.
     *
     * This implementation uses OpenMP for parallel execution.
     *
     * @return A state_pointer to the solution state, or nullptr if no solution is found.
     */
    state_pointer solve_par () override;
};

#endif //BFS_SOLVER_H
