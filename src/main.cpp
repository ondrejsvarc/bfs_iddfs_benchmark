/**
 * @file main.cpp
 * @brief Main file for the algorithm benchmarking application.
 *
 * This program solves various problems (Maze, SAT, Hanoi) using different search algorithms (BFS, IDDFS)
 * in both sequential and parallel implementations. It allows users to generate problems with custom parameters,
 * load problems from JSON files, and benchmark the performance of the algorithms.
 *
 * @author Ondrej Svarc
 * @date Created on 27.12.2024
*/

#include <iostream>
#include <string>
#include <stdexcept>
#include <map>

#include "problem_loader.h"
#include "algorithm_benchmark.h"
#include "generators/maze_generator.h"
#include "generators/sat_generator.h"
#include "generators/hanoi_generator.h"

/**
 * @brief Global variables to store command-line argument flags.
 * These flags control the behavior of the program based on user input.
 */
bool is_maze = false;
bool is_sat = false;
bool is_hanoi = false;
bool is_file = false;
bool is_generate = false;
bool is_parallel = false;
bool is_sequential = false;
bool is_bfs = false;
bool is_iddfs = false;
bool is_help = false;
std::string filename;


/**
 * @brief Parses command-line arguments and sets global flags.
 *
 * This function iterates through the command-line arguments provided to the program.
 * It recognizes and sets flags for various options like problem type, algorithm type,
 * whether to generate a problem, and whether to use parallel or sequential execution.
 * It also performs checks to ensure that conflicting arguments are not specified together.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of C-style strings containing the command-line arguments.
 *
 * @throws std::runtime_error if conflicting arguments are specified or an unknown argument is encountered.
 */
void parse_arguments ( int argc, char *argv[] );

/**
 * @brief Prints the help message for the program.
 *
 * Displays a usage message that lists all available command-line options and their descriptions.
 */
void print_help ();

/**
 * @brief Generates a problem based on user input and optionally saves it to a file.
 *
 * Prompts the user to select a problem type (maze, SAT, or Hanoi) and enter the necessary parameters.
 * It then generates the problem, displays it to the console, and asks the user if they want to save it to a file.
 *
 * @throws std::runtime_error if an unknown problem type is selected.
 */
void generate_problem ();

/**
 * @brief Benchmarks the selected algorithms on the specified problem.
 *
 * Loads or generates the problem based on the command-line arguments, then runs the selected
 * algorithms (BFS, IDDFS, sequential, parallel) on the problem. It measures and prints the
 * execution time of each algorithm.
 */
void benchmark_algorithms ();


/**
 * @brief Main function of the program.
 *
 * Parses command-line arguments, sets global flags, and calls the appropriate functions
 * to either generate a problem or benchmark algorithms on a loaded/generated problem.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return 0 if the program executes successfully, 1 otherwise.
 */
int main ( int argc, char** argv ) {
    try {
        parse_arguments( argc, argv );

        if ( is_help ) {
            print_help();
            return 0;
        }

        if ( is_generate ) {
            generate_problem();
        } else {
            benchmark_algorithms();
        }

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}

void parse_arguments ( int argc, char *argv[] ) {
    for ( int i = 1; i < argc; ++i ) {
        std::string arg = argv[i];
        if ( arg == "--maze" || arg == "-m" ) {
            is_maze = true;
        } else if ( arg == "--sat" || arg == "-s" ) {
            is_sat = true;
        } else if ( arg == "--hanoi" || arg == "-h" ) {
            is_hanoi = true;
        } else if ( arg == "--file" || arg == "-f" ) {
            is_file = true;
            if ( i + 1 < argc ) {
                filename = argv[++i];
            } else throw std::runtime_error("Error: Missing filename after --file.");
        } else if ( arg == "--generate" || arg == "-g" ) {
            is_generate = true;
        } else if ( arg == "--parallel" || arg == "-P" ) {
            is_parallel = true;
        } else if ( arg == "--sequential" || arg == "-S" ) {
            is_sequential = true;
        } else if ( arg == "--bfs" ) {
            is_bfs = true;
        } else if ( arg == "--iddfs" ) {
            is_iddfs = true;
        } else if ( arg == "--help" || arg == "-H" ) {
            is_help = true;
        } else throw std::runtime_error("Error: Unknown argument: " + arg);
    }

    if ( (is_maze + is_sat + is_hanoi + is_file) > 1 ) throw std::runtime_error("Error: Only one of --maze, --sat, --hanoi, or --file can be specified.");
    if ( (is_maze + is_sat + is_hanoi + is_file) < 1 && !is_generate ) is_sat = true;
    if ( is_generate && (is_parallel || is_sequential || is_bfs || is_iddfs) ) throw std::runtime_error("Error: --generate cannot be used with --parallel, --sequential, --bfs, or --iddfs.");
    if ( (is_bfs && is_iddfs) || (is_parallel && is_sequential) ) throw std::runtime_error("Error: --bfs cannot be used with --iddfs, and --parallel cannot be used with --sequential.");
}

void print_help () {
    std::cout << "Usage: problem_solver [OPTIONS]\n\n"
                << "Options:\n"
                << "  -m, --maze             Solve a maze problem (default: 69x69, seed 8)\n"
                << "  -s, --sat              Solve a SAT problem (default: vars 14, clauses 9, literals per clause 4, seed 1)\n"
                << "  -h, --hanoi            Solve a Hanoi Towers problem (default: pegs 3, discs 4)\n"
                << "  -f, --file <filename>  Load problem from file\n"
                << "  -g, --generate         Generate a problem and prompt for details\n"
                << "  -P, --parallel         Run only parallel algorithms\n"
                << "  -S, --sequential       Run only sequential algorithms\n"
                << "  --bfs                  Run only BFS algorithms\n"
                << "  --iddfs                Run only IDDFS algorithms\n"
                << "  -H, --help             Print this help message\n" << std::endl;
}

void generate_problem () {
    state_pointer initial_state = nullptr;
    std::string problem_type;
    std::map<std::string, std::string> problem_params;

    std::cout << "Select problem type (maze, sat, hanoi): ";
    std::cin >> problem_type;

    if ( problem_type == "maze" ) {
        int width, height, seed;
        std::cout << "Enter width (odd number >= 5): ";
        std::cin >> width;
        std::cout << "Enter height (odd number >= 5): ";
        std::cin >> height;
        std::cout << "Enter seed: ";
        std::cin >> seed;

        problem_params["width"] = std::to_string(width);
        problem_params["height"] = std::to_string(height);
        problem_params["seed"] = std::to_string(seed);

        std::shared_ptr<generator> generator = std::make_shared<maze_generator>(width, height, seed);
        initial_state = generator->generate();

        const auto *maze = dynamic_cast<const maze_state*>(initial_state.get());
        if ( maze ) {
            for ( int y = 0; y < height; ++y ) {
                for ( int x = 0; x < width; ++x ) {
                    switch ( maze->get_cell(y, x) ) {
                        case maze_state::cell_type::WALL:  std::cout << "#"; break;
                        case maze_state::cell_type::PATH:  std::cout << " "; break;
                        case maze_state::cell_type::START: std::cout << "S"; break;
                        case maze_state::cell_type::GOAL:  std::cout << "G"; break;
                    }
                }
                std::cout << std::endl;
            }
        }

    } else if ( problem_type == "sat" ) {
        int num_vars, num_clauses, max_literals, seed;
        std::cout << "Enter number of variables: ";
        std::cin >> num_vars;
        std::cout << "Enter number of clauses: ";
        std::cin >> num_clauses;
        std::cout << "Enter maximum number of literals per clause: ";
        std::cin >> max_literals;
        std::cout << "Enter seed: ";
        std::cin >> seed;

        problem_params["num_variables"] = std::to_string(num_vars);
        problem_params["num_clauses"] = std::to_string(num_clauses);
        problem_params["max_literals_per_clause"] = std::to_string(max_literals);
        problem_params["seed"] = std::to_string(seed);

        std::shared_ptr<generator> generator = std::make_shared<sat_generator>(num_vars, num_clauses, max_literals, seed);
        initial_state = generator->generate();

        const auto *sat = dynamic_cast<const sat_state*>(initial_state.get());
        if ( sat ) {
            sat_problem problem;
            for ( auto &desc : initial_state->get_descendents() ) {
                problem = dynamic_cast<const sat_state*>(desc.get())->get_problem();
                break;
            }

            std::cout << "SAT Problem (Number of variables: " << problem.num_variables << ", Number of clauses: " << problem.num_clauses << ")" << std::endl;
            bool first_clause = true;
            for ( const auto &clause : problem.clauses ) {
                if ( first_clause ) {
                    std::cout << "(";
                    first_clause = false;
                } else std::cout << " & (";
                bool first_literal = true;
                for ( const auto &literal : clause.literals ) {
                    if ( !first_literal ) std::cout << " v ";
                    if ( literal.negated ) std::cout << "~";
                    std::cout << literal.variable_id;
                    first_literal = false;
                }
                std::cout << ")";
            }
            std::cout << std::endl;
        }

    } else if ( problem_type == "hanoi" ) {
        int num_pegs, num_discs;
        std::cout << "Enter number of pegs (>= 3): ";
        std::cin >> num_pegs;
        std::cout << "Enter number of discs (>= 1): ";
        std::cin >> num_discs;

        problem_params["num_pegs"] = std::to_string(num_pegs);
        problem_params["num_discs"] = std::to_string(num_discs);

        std::shared_ptr<generator> generator = std::make_shared<hanoi_generator>(num_pegs, num_discs);
        initial_state = generator->generate();

        const auto *hanoi = dynamic_cast<const hanoi_state*>(initial_state.get());
        if ( hanoi ) {
            hanoi->print_state();
        }

    } else throw std::runtime_error("Error: Unknown problem type: " + problem_type);

    std::string save_problem;
    std::cout << "Save problem to file? (yes/no): ";
    std::cin >> save_problem;

    if ( save_problem == "yes" ) {
        std::string save_filename;
        std::cout << "Enter filename: ";
        std::cin >> save_filename;
        problem_loader::save_problem(save_filename, problem_type, problem_params);
        std::cout << "Problem saved to " << save_filename << std::endl;
    }
}

void benchmark_algorithms () {
    state_pointer initial_state = nullptr;

    if ( is_file ) {
        initial_state = problem_loader::load_problem(filename);
    } else {
        if ( is_maze ) {
            std::shared_ptr<generator> generator = std::make_shared<maze_generator>(69, 69, 8);
            initial_state = generator->generate();
        } else if ( is_sat ) {
            std::shared_ptr<generator> generator = std::make_shared<sat_generator>(14, 9, 4, 1);
            initial_state = generator->generate();
        } else if ( is_hanoi ) {
            std::shared_ptr<generator> generator = std::make_shared<hanoi_generator>(3, 4);
            initial_state = generator->generate();
        }
    }

    int algorithm_mask = 0;
    if ( is_parallel ) {
        if ( is_bfs ) algorithm_mask |= (2);
        else if ( is_iddfs ) algorithm_mask |= (8);
        else algorithm_mask |= (2 | 8);
    } else if ( is_sequential ) {
        if ( is_bfs ) algorithm_mask |= (1);
        else if ( is_iddfs ) algorithm_mask |= (4);
        else algorithm_mask |= (1 | 4);
    } else if ( is_bfs ) {
        algorithm_mask |= (1 | 2);
    } else if ( is_iddfs ) {
        algorithm_mask |= (4 | 8);
    } else {
        algorithm_mask |= (1 | 2 | 4 | 8);
    }

    algorithm_benchmark benchmarker(initial_state, algorithm_mask);
    benchmarker.solve();
}