//
// Created by Ondrej on 12/29/2024.
//

#include "iddfs_solver.h"

// Helper functions definitions
void dfs_with_limit ( const state_pointer& root, unsigned int depth_limit, unsigned int current_depth, std::unordered_set<unsigned long long> visited );
void dfs_with_limit_p ( const state_pointer& root, unsigned int depth_limit, unsigned int current_depth, std::unordered_set<unsigned long long>& visited );
void dfs_with_limit_seq ( const state_pointer& root, unsigned int depth_limit, unsigned int current_depth, std::unordered_set<unsigned long long> visited );

// Global vars
state_pointer result = nullptr;
state_pointer result_seq = nullptr;
int task_threshold = 8;
std::atomic<int> waiting_tasks = 0;


state_pointer iddfs_solver::solve_seq () {
    unsigned int depth_limit = 0;
    std::unordered_set<unsigned long long> visited;

    while ( result_seq == nullptr ) {
        depth_limit++;
        dfs_with_limit_seq( root, depth_limit, 0, visited );
    }

    return result_seq;
}

void dfs_with_limit_seq ( const state_pointer& root, unsigned int depth_limit, unsigned int current_depth, std::unordered_set<unsigned long long> visited ) {

    // Check for goal
    if ( root->is_goal() && ( result_seq == nullptr || root->get_identifier() < result_seq->get_identifier() ) ) {
        result_seq = root;
        return;
    }

    // Check depth limit
    if ( current_depth >= depth_limit ) return;
    visited.insert( root->get_identifier() );

    // Create tasks for children
    for ( state_pointer child : root->get_descendents() ) {
        if ( visited.find( child->get_identifier() ) == visited.end() ) {
            dfs_with_limit_seq( child, depth_limit, current_depth + 1, visited );
        }
    }

    visited.erase( root->get_identifier() );
}


state_pointer iddfs_solver::solve_par () {
    unsigned int depth_limit = 0;
    std::unordered_set<unsigned long long> visited;

    while ( result == nullptr ) {
        depth_limit++;

        #pragma omp parallel
        //task_threshold = omp_get_num_threads();
        #pragma omp single
        dfs_with_limit_p( root, depth_limit, 0, visited );
    }

    return result;
}

void dfs_with_limit ( const state_pointer& root, unsigned int depth_limit, unsigned int current_depth, std::unordered_set<unsigned long long> visited ) {
    --waiting_tasks;

    // Check for goal
    if ( root->is_goal() && ( result == nullptr || root->get_identifier() < result->get_identifier() ) ) {
        result = root;
        return;
    }

    // Check depth limit
    if ( current_depth >= depth_limit ) return;
    visited.insert( root->get_identifier() );

    // Create tasks for children
    for ( const state_pointer& child: root->get_descendents() ) {
        if ( visited.find(child->get_identifier()) == visited.end() ) {
            if ( waiting_tasks < task_threshold ) {
                ++waiting_tasks;
                #pragma omp task
                dfs_with_limit(child, depth_limit, current_depth + 1, visited);
            } else {
                dfs_with_limit_p(child, depth_limit, current_depth + 1, visited);
            }
        }
    }

    visited.erase( root->get_identifier() );
}

void dfs_with_limit_p ( const state_pointer& root, unsigned int depth_limit, unsigned int current_depth, std::unordered_set<unsigned long long>& visited ) {

    // Check for goal
    if ( root->is_goal() && ( result == nullptr || root->get_identifier() < result->get_identifier() ) ) {
        result = root;
        return;
    }

    // Check depth limit
    if ( current_depth >= depth_limit ) return;
    visited.insert( root->get_identifier() );

    // Create tasks for children
    for ( const state_pointer& child: root->get_descendents() ) {
        if ( visited.find(child->get_identifier()) == visited.end() ) {
            if ( waiting_tasks < task_threshold ) {
                ++waiting_tasks;
                #pragma omp task
                dfs_with_limit(child, depth_limit, current_depth + 1, visited);
            } else {
                dfs_with_limit_p(child, depth_limit, current_depth + 1, visited);
            }
        }
    }

    visited.erase( root->get_identifier() );
}
