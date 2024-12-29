//
// Created by Ondrej on 12/29/2024.
//

#include "bfs_solver.h"

state_pointer bfs_solver::solve_seq () {
    // prep
    std::unordered_set<unsigned long long> visited;
    std::queue<state_pointer> q;
    q.push( root );


    state_pointer result;

    while ( !q.empty() ) {
        // Get item from queue
        state_pointer current = q.front();
        q.pop();

        // Check if visited
        bool vis = false;
        for ( auto p : visited ) {
            if ( p == current->get_identifier() ) vis = true;
        }
        if ( vis ) continue;
        visited.insert( current->get_identifier() );

        // Check for end
        if ( current->is_goal() ) {
            result = current;
            break;
        }

        // Get next steps
        std::vector<state_pointer> next = current->get_descendents();
        for ( auto p : next ) {
            q.push( p );
        }
    }
    return result;
}

state_pointer bfs_solver::solve_par() {
    std::unordered_set<unsigned long long> visited;
    std::vector<state_pointer> current_level = {};
    std::vector<state_pointer> next_level = {};

    state_pointer result = nullptr;

    next_level.push_back( root );
    visited.insert( root->get_identifier() );

    while ( !next_level.empty() && result == nullptr ) {

        // Swap current and next level
        current_level = std::exchange( next_level, {} );

        #pragma omp parallel for schedule(dynamic) shared( current_level, next_level, visited, result )
        for ( size_t i = 0; i < current_level.size(); ++i ) {
            state_pointer c_state = current_level[i];

            // Create next layer
            std::vector<state_pointer> local_neighbors = c_state->get_descendents();
            std::vector<state_pointer> next_states;

            for( size_t j = 0; j < local_neighbors.size(); ++j ) {
                state_pointer p = local_neighbors[j];
                unsigned long long p_id = p->get_identifier();
                #pragma omp critical
                {
                    // If not visited add to next layer else ignore the node
                    if ( visited.find(p_id) == visited.end() ) {
                        // Check if neighbor is target
                        if ( p->is_goal() && (result == nullptr || p_id < result->get_identifier() ) ) result = p;
                        visited.insert( p_id );
                        next_level.push_back( p );
                    }
                }
            }
        }
    }

    return result;
}

