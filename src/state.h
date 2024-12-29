//
// Created by Ondrej Svarc on 27.12.2024.
//

#ifndef BFS_IDDFS_BENCHMARK_STATE_H
#define BFS_IDDFS_BENCHMARK_STATE_H

#pragma once

#include <vector>
#include <memory>

class state;
using state_pointer = std::shared_ptr<const state>;

class state {
private:
    const unsigned int cost;
    const state_pointer predecessor;

public:

    virtual std::vector<state_pointer> get_descendents() const = 0;

    virtual bool is_goal() const = 0;

    unsigned int current_cost() const {
        return cost;
    }

    virtual unsigned long long get_identifier() const = 0;

    state_pointer get_predecessor() const {
        return predecessor;
    }

    virtual std::string to_string() const = 0;

    state(const state_pointer predecessor, unsigned int cost)
            : cost(cost), predecessor(predecessor) {}

    virtual ~state() {}
};

#endif //BFS_IDDFS_BENCHMARK_STATE_H
