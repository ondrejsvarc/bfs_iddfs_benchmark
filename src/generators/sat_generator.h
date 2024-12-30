//
// Created by Ondrej on 12/29/2024.
//

#ifndef SAT_GENERATOR_H
#define SAT_GENERATOR_H

#pragma once

#include <vector>
#include <random>
#include <memory>
#include <map>

#include "generator.h"
#include "../state.h"


struct literal {
    int variable_id;
    bool negated;

    explicit literal ( int var_id, bool neg = false ) : variable_id ( var_id ), negated ( neg ) {}
};

struct clause {
    std::vector<literal> literals; // Literals in clause connected with disjunction
};

struct sat_problem {
    int num_variables;
    int num_clauses;
    std::vector<clause> clauses; // Clauses connected with conjunction
};

class sat_state : public state, public std::enable_shared_from_this<sat_state> {
public:
    sat_state ( const state_pointer predecessor, const sat_problem &problem, const std::map<int, bool> &assignment = {} )
        : state ( predecessor ), problem ( problem ), assignment ( assignment ) {}

    std::vector<state_pointer> get_descendents () const override;

    bool is_goal () const override;

    unsigned long long get_identifier () const override;

    std::map<int, bool> get_assignment () const;

    sat_problem get_problem () const;

private:
    sat_problem problem;
    std::map<int, bool> assignment; // Variable values (true or false)
};

class sat_generator : public generator {
public:
    sat_generator ( int num_vars, int num_clauses, int max_literals_per_clause, int seed )
        : num_variables ( num_vars ), num_clauses ( num_clauses ), max_literals_per_clause ( max_literals_per_clause ), random_engine ( seed ) {
        if ( num_vars <= 0 || num_clauses <= 0 || max_literals_per_clause <= 0 ) throw std::invalid_argument("Number of variables, clauses, and max literals per clause must be positive.");
    }

    state_pointer generate () override;

private:
    sat_problem generate_problem ();

    int num_variables;
    int num_clauses;
    int max_literals_per_clause;
    std::default_random_engine random_engine;
};



#endif //SAT_GENERATOR_H
