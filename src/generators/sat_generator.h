/**
 * @file sat_generator.h
 * @brief Declares the sat_generator and sat_state classes for generating and representing SAT problem instances.
 *
 * This header file defines the `sat_generator` class, which generates a random SAT problem in Conjunctive Normal Form (CNF),
 * and the `sat_state` class, which represents a state in the SAT problem (i.e., a partial or complete assignment of boolean values to variables).
 * It also defines the `literal`, `clause`, and `sat_problem` structs used to represent the SAT problem.
 *
 * @author Ondrej Svarc
 * @date Created on 12/29/2024
 */

#ifndef SAT_GENERATOR_H
#define SAT_GENERATOR_H

#pragma once

#include <vector>
#include <random>
#include <memory>
#include <map>

#include "generator.h"
#include "../state.h"


/**
 * @brief Represents a literal in a clause.
 *
 * A literal is a variable or its negation.
 */
struct literal {
    int variable_id; ///< The identifier of the variable (e.g., 1 for x1, 2 for x2).
    bool negated; ///< True if the literal is negated (e.g., ¬x1), false otherwise.

    /**
     * @brief Constructor for the literal struct.
     *
     * @param var_id The identifier of the variable.
     * @param neg    True if the literal is negated, false otherwise. Defaults to false.
     */
    explicit literal ( int var_id, bool neg = false ) : variable_id ( var_id ), negated ( neg ) {}
};

/**
 * @brief Represents a clause in a CNF formula.
 *
 * A clause is a disjunction (OR) of literals.
 */
struct clause {
    std::vector<literal> literals; ///< The literals in the clause.
};

/**
 * @brief Represents a SAT problem in Conjunctive Normal Form (CNF).
 */
struct sat_problem {
    int num_variables; ///< The number of boolean variables.
    int num_clauses; ///< The number of clauses.
    std::vector<clause> clauses; ///< The clauses in the problem (connected by conjunction/AND).
};


/**
 * @brief Represents a state in the SAT problem.
 *
 * A state is a partial or complete assignment of boolean values to variables.
 */
class sat_state : public state, public std::enable_shared_from_this<sat_state> {
public:
    /**
     * @brief Constructor for the sat_state class.
     *
     * @param predecessor A pointer to the predecessor state.
     * @param problem     The SAT problem instance.
     * @param assignment  A map representing the current assignment of boolean values to variables.
     */
    sat_state ( const state_pointer predecessor, const sat_problem &problem, const std::map<int, bool> &assignment = {} )
        : state ( predecessor ), problem ( problem ), assignment ( assignment ) {}

    /**
     * @brief Generates the successor states from the current state by assigning true/false to the next unassigned variable.
     *
     * @return A vector of state_pointers representing the valid successor states.
     */
    std::vector<state_pointer> get_descendents () const override;

    /**
     * @brief Checks if the current state is a goal state (i.e., a satisfying assignment).
     *
     * @return True if the current assignment satisfies all clauses, false otherwise.
     */
    bool is_goal () const override;

    /**
     * @brief Generates a unique identifier for the current state based on the variable assignment.
     *
     * @return An unsigned long long representing the unique identifier.
     */
    unsigned long long get_identifier () const override;

    /**
     * @brief Returns the current variable assignment.
     *
     * @return A map representing the assignment of boolean values to variables.
     */
    std::map<int, bool> get_assignment () const;

    /**
     * @brief Returns the SAT problem instance.
     *
     * @return The sat_problem struct.
     */
    sat_problem get_problem () const;

private:
    sat_problem problem; ///< The SAT problem instance.
    std::map<int, bool> assignment; ///< The current assignment of boolean values to variables.
};


/**
 * @brief Generator for random SAT problem instances in Conjunctive Normal Form (CNF).
 */
class sat_generator : public generator {
public:
    /**
     * @brief Constructor for the sat_generator class.
     *
     * @param num_vars                 The number of boolean variables.
     * @param num_clauses              The number of clauses.
     * @param max_literals_per_clause The maximum number of literals allowed in a single clause.
     * @param seed                     The seed for the random number generator.
     * @throws std::invalid_argument if num_vars, num_clauses, or max_literals_per_clause is not positive.
     */
    sat_generator ( int num_vars, int num_clauses, int max_literals_per_clause, int seed )
        : num_variables ( num_vars ), num_clauses ( num_clauses ), max_literals_per_clause ( max_literals_per_clause ), random_engine ( seed ) {
        if ( num_vars <= 0 || num_clauses <= 0 || max_literals_per_clause <= 0 ) throw std::invalid_argument("Number of variables, clauses, and max literals per clause must be positive.");
    }

    /**
     * @brief Generates an initial state for the SAT problem (an empty assignment).
     *
     * @return A state_pointer representing the initial state.
     */
    state_pointer generate () override;

private:
    /**
     * @brief Generates a random SAT problem instance.
     *
     * @return A sat_problem struct representing the generated problem.
     */
    sat_problem generate_problem ();

    int num_variables; ///< The number of boolean variables.
    int num_clauses; ///< The number of clauses.
    int max_literals_per_clause; ///< The maximum number of literals per clause.
    std::default_random_engine random_engine; ///< The random number generator.
};

#endif //SAT_GENERATOR_H
