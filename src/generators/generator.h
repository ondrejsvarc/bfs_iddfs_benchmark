/**
 * @file generator.h
 * @brief Declares the generator abstract base class for generating initial states of problems.
 *
 * This header file defines the `generator` abstract base class, which provides a common interface for
 * generating initial states for different problem types (e.g., Maze, SAT, Hanoi).
 *
 * @author Ondrej Svarc
 * @date Created on 12/29/2024
 */

#ifndef GENERATOR_H
#define GENERATOR_H

#pragma once

#include <memory>
#include "../state.h"

/**
 * @brief Type alias for a shared pointer to a constant state.
 */
using state_pointer = std::shared_ptr<const state>;


/**
 * @brief Abstract base class for generators of initial problem states.
 *
 * This class provides a common interface for generating initial states for different problem types.
 * Derived classes must implement the `generate` method to define the specific generation logic.
 */
class generator {
public:
    /**
     * @brief Virtual destructor for the generator class.
     *
     * Ensures proper cleanup of derived class objects when deleting through a base class pointer.
     */
    virtual ~generator() = default;

    /**
     * @brief Pure virtual function for generating the initial state of a problem.
     *
     * This method must be implemented by derived classes to define the specific generation logic
     * for a particular problem type.
     *
     * @return A state_pointer to the generated initial state.
     */
    virtual state_pointer generate() = 0;
};

#endif //GENERATOR_H
