//
// Created by Ondrej on 12/30/2024.
//

#include "hanoi_generator.h"

// Hanoi State implementation
std::vector<state_pointer> hanoi_state::get_descendents () const {
    std::vector<state_pointer> children;
    for ( int from_peg = 0; from_peg < num_pegs; ++from_peg ) {
        if ( pegs[from_peg].empty() ) continue;

        for ( int to_peg = 0; to_peg < num_pegs; ++to_peg ) {
            if ( from_peg == to_peg ) continue;

            if ( !pegs[to_peg].empty() && pegs[to_peg].back() < pegs[from_peg].back() ) continue;

            std::vector<std::vector<int>> new_pegs = pegs;
            int disc = new_pegs[from_peg].back();
            new_pegs[from_peg].pop_back();
            new_pegs[to_peg].push_back(disc);

            children.push_back(std::make_shared<const hanoi_state>(shared_from_this(), num_pegs, num_discs, new_pegs));
        }
    }
    return children;
}

bool hanoi_state::is_goal () const {
    if ( static_cast<int>(pegs.back().size()) != num_discs ) return false;
    for ( int i = 0; i < num_pegs - 1; ++i ) if ( !pegs[i].empty() ) return false;
    return true;
}

unsigned long long hanoi_state::get_identifier () const {
    unsigned long long identifier = 0;
    for ( int i = 0; i < num_pegs; ++i ) {
        for ( int j = 0; j < static_cast<int>(pegs[i].size()); ++j ) {
            identifier = identifier * num_discs + pegs[i][j];
        }
        identifier = identifier * (num_discs + 1);
    }
    return identifier;
}

void hanoi_state::print_state () const {
    for ( int i = 0; i < num_pegs; ++i ) {
        std::cout << "Peg " << i << ": ";
        for ( int disc : pegs[i] ) {
            std::cout << disc << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "----" << std::endl;
}

std::vector<std::vector<int>> hanoi_state::get_pegs () const {
    return pegs;
}


// Hanoi Generator implementation
state_pointer hanoi_generator::generate () {
    std::vector<std::vector<int>> initial_pegs(num_pegs);
    for ( int i = num_discs; i >= 1; --i ) {
        initial_pegs[0].push_back(i);
    }

    return std::make_shared<const hanoi_state>(nullptr, num_pegs, num_discs, initial_pegs);
}