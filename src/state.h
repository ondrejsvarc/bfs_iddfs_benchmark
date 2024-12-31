/**
 * @file state.h
 * @brief Defines the abstract base class for a state in a state-space search problem.
 *
 * This header file defines the `state` class, which serves as an abstract base class for representing
 * states in state-space search problems like the Maze, SAT, and Hanoi Towers problems.
 * It provides an interface for generating successor states, checking for goal states,
 * and generating unique identifiers for states.
 *
 * @author Ondrej Svarc
 * @date Created on 27.12.2024
 */

#ifndef STATE_H
#define STATE_H

#pragma once

#include <vector>
#include <memory>

class state;

/**
 * @brief Type alias for a shared pointer to a constant state.
 *
 * Using a shared pointer ensures proper memory management and prevents accidental modification of the state.
 */
using state_pointer = std::shared_ptr<const state>;


/**
 * @brief Abstract base class representing a state in a state-space search problem.
 *
 * This class provides a common interface for all state representations in the application.
 * Derived classes must implement the pure virtual functions to define the specific behavior of each problem.
 */
class state {
private:
    /**
     * @brief Pointer to the predecessor state.
     *
     * Represents the state from which the current state was reached. Can be `nullptr` for the initial state.
     */
    const state_pointer predecessor;

public:
    /**
     * @brief Pure virtual function to get the successor states of the current state.
     *
     * Generates all valid successor states from the current state.
     *
     * @return A vector of shared pointers to the successor states.
     */
    [[nodiscard]] virtual std::vector<state_pointer> get_descendents () const = 0;

    /**
     * @brief Pure virtual function to check if the current state is a goal state.
     *
     * Determines whether the current state satisfies the goal conditions of the problem.
     *
     * @return `true` if the current state is a goal state, `false` otherwise.
     */
    [[nodiscard]] virtual bool is_goal () const = 0;

    /**
     * @brief Pure virtual function to get a unique identifier for the current state.
     *
     * Generates a unique identifier (hash) for the current state. This identifier is used to
     * detect previously visited states during the search.
     *
     * @return A unique identifier for the current state.
     */
    [[nodiscard]] virtual unsigned long long get_identifier () const = 0;

    /**
     * @brief Returns the predecessor state of the current state.
     *
     * @return A shared pointer to the predecessor state, or `nullptr` if the current state is the initial state.
     */
    [[nodiscard]] state_pointer get_predecessor () const {
        return predecessor;
    }

    /**
     * @brief Constructor for the state class.
     *
     * @param predecessor A shared pointer to the predecessor state.
     */
    explicit state ( const state_pointer predecessor ) : predecessor( predecessor ) {}

    /**
     * @brief Virtual destructor for the state class.
     *
     * Ensures proper cleanup of derived class objects when deleting through a base class pointer.
     */
    virtual ~state() = default;
};

#endif // STATE_H
