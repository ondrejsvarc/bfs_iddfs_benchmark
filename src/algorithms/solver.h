//
// Created by Ondrej on 12/29/2024.
//

#ifndef SOLVER_H
#define SOLVER_H

#pragma once

#include <memory>
#include <stdexcept>
#include "../state.h"

using state_pointer = std::shared_ptr<const state>;

class solver {
public:

    explicit solver ( const state_pointer initial_state ) : root( initial_state ) {
        if ( !root ) {
            throw std::invalid_argument("Initial state cannot be null.");
        }
    }

    virtual state_pointer solve_seq () = 0;

    virtual state_pointer solve_par () = 0;

    virtual ~solver () = default;

protected:
    const state_pointer root;
};

#endif //SOLVER_H
