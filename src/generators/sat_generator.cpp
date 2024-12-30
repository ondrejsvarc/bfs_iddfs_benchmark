//
// Created by Ondrej on 12/29/2024.
//

#include "sat_generator.h"

// SAT State implementation
std::vector<state_pointer> sat_state::get_descendents () const {
    std::vector<state_pointer> children;

    if ( is_goal() ) return children;

    int next_variable = -1;
    for ( int i = 1; i <= problem.num_variables; ++i ) {
        if ( assignment.find(i) == assignment.end() ) {
            next_variable = i;
            break;
        }
    }

    if ( next_variable == -1 ) return children;

    std::map<int, bool> assignment_true = assignment;
    assignment_true[next_variable] = true;

    std::map<int, bool> assignment_false = assignment;
    assignment_false[next_variable] = false;

    children.push_back(std::make_shared<const sat_state>(shared_from_this(), problem, assignment_true));
    children.push_back(std::make_shared<const sat_state>(shared_from_this(), problem, assignment_false));

    return children;
}

bool sat_state::is_goal () const {
    for ( const clause &clause : problem.clauses ) {
        bool clause_satisfied = false;
        for ( const literal &literal : clause.literals ) {

            if ( assignment.count(literal.variable_id) ) {
                if ( (literal.negated && !assignment.at(literal.variable_id)) || (!literal.negated && assignment.at(literal.variable_id)) ) {
                    clause_satisfied = true;
                    break;
                }
            }
        }
        if ( !clause_satisfied ) return false;
    }

    if ( assignment.size() != problem.num_variables ) return false;

    return true;
}

unsigned long long sat_state::get_identifier () const {
    unsigned long long identifier = 0;
    for ( int i = 1; i <= problem.num_variables; ++i ) {
        identifier = identifier << 2;
        if ( assignment.count(i) ) {
            identifier += (assignment.at(i) ? 2 : 1);
        }
    }
    return identifier;
}

std::map<int, bool> sat_state::get_assignment () const {
    return assignment;
}

sat_problem sat_state::get_problem () const {
    return problem;
}


// SAT Generator implementation
state_pointer sat_generator::generate () {
    sat_problem problem = generate_problem();
    return std::make_shared<const sat_state>(nullptr, problem);
}

sat_problem sat_generator::generate_problem () {
    sat_problem problem;
    problem.num_variables = num_variables;
    problem.num_clauses = num_clauses;

    std::uniform_int_distribution<> var_dist(1, num_variables);
    std::uniform_int_distribution<> bool_dist(0, 1);
    std::uniform_int_distribution<> literal_count_dist(1, max_literals_per_clause);

    for ( int i = 0; i < num_clauses; ++i ) {
        clause clause;
        int num_literals = literal_count_dist(random_engine);

        for ( int j = 0; j < num_literals; ++j ) {
            int var_id = var_dist(random_engine);
            bool negated = bool_dist(random_engine);
            clause.literals.emplace_back(var_id, negated);
        }
        problem.clauses.push_back(clause);
    }

    return problem;
}
