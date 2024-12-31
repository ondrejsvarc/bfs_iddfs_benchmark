/**
 * @file solver.h
 * @brief Declares the solver abstract base class for solving state-space search problems.
 *
 * This header file defines the `solver` class, which serves as an abstract base class for different
 * search algorithm implementations (e.g., BFS, IDDFS). It provides a common interface for solving
 * problems sequentially and in parallel.
 *
 * @author Ondrej Svarc
 * @date Created on 12/29/2024
 */

#ifndef SOLVER_H
#define SOLVER_H

#pragma once

#include <memory>
#include <stdexcept>
#include "../state.h"

/**
 * @brief Type alias for a shared pointer to a constant state.
 */
using state_pointer = std::shared_ptr<const state>;

/**
 * @brief Abstract base class for solvers of state-space search problems.
 *
 * This class provides a common interface for different search algorithm implementations.
 * Derived classes must implement the `solve_seq` and `solve_par` methods to define
 * the specific sequential and parallel solution logic.
 */
class solver {
public:
    /**
     * @brief Constructor for the solver class.
     *
     * @param initial_state The initial state of the problem.
     * @throws std::invalid_argument if the initial state is null.
     */
    explicit solver ( const state_pointer initial_state ) : root( initial_state ) {
        if ( !root ) {
            throw std::invalid_argument("Initial state cannot be null.");
        }
    }

    /**
     * @brief Pure virtual function for solving the problem sequentially.
     *
     * This method must be implemented by derived classes to define the sequential search algorithm.
     *
     * @return A state_pointer to the solution state, or nullptr if no solution is found.
     */
    virtual state_pointer solve_seq () = 0;

    /**
     * @brief Pure virtual function for solving the problem in parallel.
     *
     * This method must be implemented by derived classes to define the parallel search algorithm.
     *
     * @return A state_pointer to the solution state, or nullptr if no solution is found.
     */
    virtual state_pointer solve_par () = 0;

    /**
     * @brief Virtual destructor for the solver class.
     *
     * Enables proper cleanup of derived class objects when deleting through a base class pointer.
     */
    virtual ~solver () = default;

protected:
    /**
     * @brief The initial state of the problem.
     *
     * This shared pointer holds the root of the search tree. It is protected so that derived classes can access it.
     */
    const state_pointer root;
};

#endif //SOLVER_H
