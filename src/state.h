//
// Created by Ondrej Svarc on 27.12.2024.
//

#ifndef STATE_H
#define STATE_H

#pragma once

#include <vector>
#include <memory>

class state;
using state_pointer = std::shared_ptr<const state>;

class state {
private:
    const state_pointer predecessor;

public:

    [[nodiscard]] virtual std::vector<state_pointer> get_descendents () const = 0;

    [[nodiscard]] virtual bool is_goal () const = 0;

    [[nodiscard]] virtual unsigned long long get_identifier () const = 0;

    [[nodiscard]] state_pointer get_predecessor () const {
        return predecessor;
    }

    explicit state ( const state_pointer predecessor ) : predecessor( predecessor ) {}

    virtual ~state() = default;
};

#endif // STATE_H
