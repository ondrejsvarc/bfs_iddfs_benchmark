/**
 * @file iddfs_solver.h
 * @brief Declares the iddfs_solver class, which implements the Iterative Deepening Depth-First Search (IDDFS) algorithm.
 *
 * This header file defines the `iddfs_solver` class, which inherits from the `solver` abstract base class.
 * It provides both sequential and parallel implementations of the IDDFS algorithm for solving state-space search problems.
 *
 * @author Ondrej Svarc
 * @date Created on 12/29/2024
 */


#ifndef IDDFS_SOLVER_H
#define IDDFS_SOLVER_H

#pragma once

#include "solver.h"
#include <climits>
#include <unordered_set>
#include <atomic>
#include <omp.h>


/**
 * @brief Implements the Iterative Deepening Depth-First Search (IDDFS) algorithm for solving state-space problems.
 *
 * This class provides both sequential (`solve_seq`) and parallel (`solve_par`) implementations of the IDDFS algorithm.
 * It inherits from the `solver` abstract base class.
 */
class iddfs_solver : public solver {
public:
    /**
     * @brief Constructor for the iddfs_solver class.
     *
     * @param initial_state The initial state of the problem.
     */
    explicit iddfs_solver( const state_pointer initial_state ) : solver( initial_state ) {};

    /**
     * @brief Solves the problem sequentially using the IDDFS algorithm.
     *
     * @return A state_pointer to the solution state, or nullptr if no solution is found.
     */
    state_pointer solve_seq () override;

    /**
     * @brief Solves the problem in parallel using the IDDFS algorithm.
     *
     * This implementation uses OpenMP for parallel execution.
     *
     * @return A state_pointer to the solution state, or nullptr if no solution is found.
     */
    state_pointer solve_par () override;
};

#endif //IDDFS_SOLVER_H
