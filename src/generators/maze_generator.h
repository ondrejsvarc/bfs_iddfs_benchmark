/**
 * @file maze_generator.h
 * @brief Declares the maze_generator and maze_state classes for generating and representing maze problems.
 *
 * This header file defines the `maze_generator` class, which generates a random maze using a recursive backtracking algorithm,
 * and the `maze_state` class, which represents a state in the maze problem (i.e., the current position within the maze).
 *
 * @author Ondrej Svarc
 * @date Created on 12/29/2024
 */

#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

#pragma once

#include "generator.h"

#include <vector>
#include <memory>
#include <random>
#include <algorithm>


/**
 * @brief Represents a state in the maze problem.
 *
 * This class stores the maze grid, the current position within the maze, and provides methods for
 * generating successor states, checking for the goal state, and generating a unique identifier.
 */
class maze_state : public state, public std::enable_shared_from_this<maze_state> {
public:
    /**
     * @brief Enum defining the possible types of cells in the maze.
     */
    enum cell_type {
        WALL,  ///< Represents a wall cell.
        PATH,  ///< Represents a path cell.
        START, ///< Represents the starting cell.
        GOAL   ///< Represents the goal cell.
    };

    /**
     * @brief Constructor for the maze_state class.
     *
     * @param predecessor A pointer to the predecessor state.
     * @param grid The 2D vector representing the maze grid.
     * @param start The starting position within the maze.
     */
    maze_state ( const state_pointer predecessor, const std::vector<std::vector<cell_type>> &grid, std::pair<int, int> start)
        : state( predecessor ), grid( grid ), current_position( start ) {}

    /**
     * @brief Generates the successor states (possible moves) from the current state.
     *
     * @return A vector of state_pointers representing the valid successor states.
     */
    std::vector<state_pointer> get_descendents () const override;

    /**
     * @brief Checks if the current state is the goal state.
     *
     * @return True if the current position is the goal, false otherwise.
     */
    bool is_goal () const override;

    /**
     * @brief Generates a unique identifier for the current state.
     *
     * @return An unsigned long long representing the unique identifier.
     */
    unsigned long long get_identifier () const override;

    /**
     * @brief Gets the cell type at the specified coordinates.
     *
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     * @return The cell_type at the specified coordinates.
     */
    cell_type get_cell(int x, int y) const;

private:
    std::vector<std::vector<cell_type>> grid; ///< The 2D vector representing the maze grid.
    std::pair<int, int> current_position; ///< The current position within the maze (x, y).
};


/**
 * @brief Generator for the initial state of a maze problem.
 *
 * This class generates a random maze of specified width and height using a recursive backtracking algorithm.
 */
class maze_generator : public generator {
public:
    /**
     * @brief Constructor for the maze_generator class.
     *
     * @param width The width of the maze (must be an odd number).
     * @param height The height of the maze (must be an odd number).
     * @param seed The seed for the random number generator.
     * @throws std::invalid_argument if width or height is not an odd number.
     */
    maze_generator (const int width, const int height, const int seed ) : width( width ), height( height ), random_engine( seed ) {
        if ( width % 2 == 0 || height % 2 == 0 ) {
            throw std::invalid_argument("Width and height must be odd numbers.");
        }
    }

    /**
     * @brief Generates the initial state for the maze problem.
     *
     * @return A state_pointer representing the initial state (the generated maze).
     */
    state_pointer generate () override;

private:
    /**
     * @brief Recursive function to generate the maze using the recursive backtracking algorithm.
     *
     * @param grid The 2D vector representing the maze grid.
     * @param x The current x-coordinate.
     * @param y The current y-coordinate.
     */
    void generate_maze_recursive ( std::vector<std::vector<maze_state::cell_type>>& grid, int x, int y );

    int width; ///< The width of the maze.
    int height; ///< The height of the maze.
    std::default_random_engine random_engine; ///< The random number generator.
};

#endif //MAZE_GENERATOR_H
