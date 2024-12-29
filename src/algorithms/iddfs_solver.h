//
// Created by Ondrej on 12/29/2024.
//

#ifndef IDDFS_SOLVER_H
#define IDDFS_SOLVER_H

#pragma once

#include "solver.h"
#include <unordered_set>
#include <atomic>
#include <omp.h>


class iddfs_solver : public solver {
public:
    explicit iddfs_solver( const state_pointer initial_state ) : solver( initial_state ) {};

    state_pointer solve_seq () override;

    state_pointer solve_par () override;
};

#endif //IDDFS_SOLVER_H
