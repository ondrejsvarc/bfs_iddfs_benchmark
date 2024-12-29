//
// Created by Ondrej on 12/29/2024.
//

#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

#pragma once

#include "generator.h"

#include <vector>
#include <memory>
#include <random>
#include <algorithm>

class maze_state : public state, public std::enable_shared_from_this<maze_state> {
public:
    enum cell_type { WALL, PATH, START, GOAL };

    maze_state ( const state_pointer predecessor, const std::vector<std::vector<cell_type>> &grid, std::pair<int, int> start)
        : state( predecessor ), grid( grid ), current_position( start ) {}

    [[nodiscard]] std::vector<state_pointer> get_descendents () const override;

    [[nodiscard]] bool is_goal () const override;

    [[nodiscard]] unsigned long long get_identifier () const override;

    [[nodiscard]] cell_type get_cell(int x, int y) const;

private:
    std::vector<std::vector<cell_type>> grid;
    std::pair<int, int> current_position;
};

class maze_generator : public generator {
public:
    maze_generator (const int width, const int height, const int seed ) : width( width ), height( height ), random_engine( seed ) {
        if ( width % 2 == 0 || height % 2 == 0 ) {
            throw std::invalid_argument("Width and height must be odd numbers.");
        }
    }

    state_pointer generate () override;

private:
    void generate_maze_recursive ( std::vector<std::vector<maze_state::cell_type>>& grid, int x, int y );

    int width;
    int height;
    std::default_random_engine random_engine;
};



#endif //MAZE_GENERATOR_H
