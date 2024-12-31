/**
 * @file hanoi_generator.h
 * @brief Declares the hanoi_generator and hanoi_state classes for the Hanoi Towers problem.
 *
 * This header file defines the `hanoi_generator` class, which generates the initial state for the Hanoi Towers problem,
 * and the `hanoi_state` class, which represents a state in the Hanoi Towers problem.
 *
 * @author Ondrej Svarc
 * @date Created on 12/30/2024
 */

#ifndef HANOI_GENERATOR_H
#define HANOI_GENERATOR_H

#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include "../state.h"
#include "generator.h"


/**
 * @brief Represents a state in the Hanoi Towers problem.
 *
 * This class stores the configuration of the pegs and discs, and provides methods to
 * generate successor states, check for the goal state, and get a unique identifier.
 */
class hanoi_state : public state, public std::enable_shared_from_this<hanoi_state> {
public:
    /**
     * @brief Constructor for the hanoi_state class.
     *
     * @param predecessor A pointer to the predecessor state.
     * @param num_pegs The number of pegs.
     * @param num_discs The number of discs.
     * @param pegs A vector of vectors representing the pegs, where each inner vector contains the disc numbers on that peg.
     */
    hanoi_state ( const state_pointer predecessor, int num_pegs, int num_discs, const std::vector<std::vector<int>> &pegs )
        : state ( predecessor ), num_pegs ( num_pegs ), num_discs ( num_discs ), pegs ( pegs ) {}

    /**
     * @brief Generates the successor states from the current state.
     *
     * @return A vector of state_pointers representing the valid successor states.
     */
    std::vector<state_pointer> get_descendents () const override;

    /**
     * @brief Checks if the current state is the goal state.
     *
     * @return True if all discs are on the last peg, false otherwise.
     */
    bool is_goal () const override;

    /**
     * @brief Generates a unique identifier for the current state.
     *
     * @return An unsigned long long representing the unique identifier.
     */
    unsigned long long get_identifier () const override;

    /**
     * @brief Prints the current state of the Hanoi Towers to the console.
     *
     * Useful for debugging and visualizing the state.
     */
    void print_state () const;

    /**
     * @brief Gets the current configuration of pegs and discs.
     *
     * @return A vector of vectors representing the pegs.
     */
    std::vector<std::vector<int>> get_pegs () const;
private:
    int num_pegs; ///< The number of pegs.
    int num_discs; ///< The number of discs.
    std::vector<std::vector<int>> pegs; ///< The configuration of pegs, each represented by a vector of disc numbers.
};


/**
 * @brief Generator for the initial state of the Hanoi Towers problem.
 *
 * This class generates the initial state where all discs are stacked on the first peg in decreasing order of size.
 */
class hanoi_generator : public generator{
public:
    /**
     * @brief Constructor for the hanoi_generator class.
     *
     * @param num_pegs The number of pegs (must be >= 3).
     * @param num_discs The number of discs (must be >= 1).
     * @throws std::invalid_argument if num_pegs < 3 or num_discs < 1.
     */
    hanoi_generator ( int num_pegs, int num_discs ) : num_pegs ( num_pegs ), num_discs ( num_discs ) {
        if ( num_pegs < 3 ) throw std::invalid_argument("Number of pegs must be at least 3.");
        if ( num_discs < 1 ) throw std::invalid_argument("Number of discs must be at least 1.");
    }

    /**
     * @brief Generates the initial state for the Hanoi Towers problem.
     *
     * @return A state_pointer representing the initial state.
     */
    state_pointer generate () override;

private:
    int num_pegs; ///< The number of pegs.
    int num_discs; ///< The number of discs.
};

#endif //HANOI_GENERATOR_H
