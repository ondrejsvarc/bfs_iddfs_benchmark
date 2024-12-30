//
// Created by Ondrej on 12/30/2024.
//

#ifndef HANOI_GENERATOR_H
#define HANOI_GENERATOR_H

#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include "../state.h"
#include "generator.h"

class hanoi_state : public state, public std::enable_shared_from_this<hanoi_state> {
public:
    hanoi_state ( const state_pointer predecessor, int num_pegs, int num_discs, const std::vector<std::vector<int>> &pegs )
        : state ( predecessor ), num_pegs ( num_pegs ), num_discs ( num_discs ), pegs ( pegs ) {}

    std::vector<state_pointer> get_descendents () const override;

    bool is_goal () const override;

    unsigned long long get_identifier () const override;

    void print_state () const;

    std::vector<std::vector<int>> get_pegs () const;
private:
    int num_pegs;
    int num_discs;
    std::vector<std::vector<int>> pegs;
};

class hanoi_generator : public generator{
public:
    hanoi_generator ( int num_pegs, int num_discs ) : num_pegs ( num_pegs ), num_discs ( num_discs ) {
        if ( num_pegs < 3 ) throw std::invalid_argument("Number of pegs must be at least 3.");
        if ( num_discs < 1 ) throw std::invalid_argument("Number of discs must be at least 1.");
    }

    state_pointer generate () override;

private:
    int num_pegs;
    int num_discs;
};



#endif //HANOI_GENERATOR_H
