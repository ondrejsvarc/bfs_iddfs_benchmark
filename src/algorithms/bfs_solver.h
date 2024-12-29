//
// Created by Ondrej on 12/29/2024.
//

#ifndef BFS_SOLVER_H
#define BFS_SOLVER_H

#pragma once

#include "solver.h"
#include <queue>
#include <unordered_set>
#include <utility>

class bfs_solver : public solver {
public:
    explicit bfs_solver( const state_pointer initial_state ) : solver( initial_state ) {};

    state_pointer solve_seq () override;

    state_pointer solve_par () override;
};

#endif //BFS_SOLVER_H
