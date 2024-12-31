/**
 * @file problem_loader.h
 * @brief Declares the problem_loader class, which handles saving and loading problems to/from files.
 *
 * This header file defines the `problem_loader` class. This class provides static methods for saving problem
 * configurations to files in a simple JSON-like format and loading them back to generate the corresponding
 * problem states. It supports Maze, SAT, and Hanoi Tower problems.
 *
 * @author Ondrej Svarc
 * @date Created on 12/31/2024
 */

#ifndef PROBLEM_LOADER_H
#define PROBLEM_LOADER_H

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <map>

#include "generators/maze_generator.h"
#include "generators/sat_generator.h"
#include "generators/hanoi_generator.h"


/**
 * @brief The problem_loader class handles saving and loading problem configurations.
 *
 * This class provides static methods to save problem configurations to a file in a simplified JSON format
 * and to load them back, generating the corresponding problem state using the appropriate generator.
 */
class problem_loader {
public:
    /**
     * @brief Saves a problem configuration to a file.
     *
     * @param filename The name of the file to save the problem to.
     * @param problem_type The type of the problem (e.g., "maze", "sat", "hanoi").
     * @param parameters A map containing the parameters for the problem.
     *
     * @throws std::runtime_error if the file cannot be opened for writing.
     */
    static void save_problem ( const std::string &filename, const std::string &problem_type, const std::map<std::string, std::string> &parameters );

    /**
     * @brief Loads a problem configuration from a file and generates the corresponding state.
     *
     * @param filename The name of the file to load the problem from.
     * @return A state_pointer representing the initial state of the loaded problem.
     *
     * @throws std::runtime_error if the file cannot be opened for reading,
     *                             if the problem type is unknown, or if a parameter is missing.
     */
    static state_pointer load_problem ( const std::string &filename );

private:
    /**
     * @brief Generates a maze problem based on the given parameters.
     *
     * @param parameters A map containing the parameters for the maze problem. Must include "width", "height", and "seed".
     * @return A state_pointer representing the initial state of the maze problem.
     *
     * @throws std::out_of_range if a required parameter is missing.
     */
    static state_pointer generate_maze ( const std::map<std::string, std::string> &parameters );

    /**
     * @brief Generates a SAT problem based on the given parameters.
     *
     * @param parameters A map containing the parameters for the SAT problem. Must include "num_variables", "num_clauses", "max_literals_per_clause", and "seed".
     * @return A state_pointer representing the initial state of the SAT problem.
     *
     * @throws std::out_of_range if a required parameter is missing.
     */
    static state_pointer generate_sat ( const std::map<std::string, std::string> &parameters );

    /**
     * @brief Generates a Hanoi Towers problem based on the given parameters.
     *
     * @param parameters A map containing the parameters for the Hanoi problem. Must include "num_pegs" and "num_discs".
     * @return A state_pointer representing the initial state of the Hanoi Towers problem.
     *
     * @throws std::out_of_range if a required parameter is missing.
     */
    static state_pointer generate_hanoi ( const std::map<std::string, std::string> &parameters );
};

#endif //PROBLEM_LOADER_H
