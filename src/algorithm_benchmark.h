//
// Created by Ondrej on 12/31/2024.
//

#ifndef ALGORITHM_BENCHMARK_H
#define ALGORITHM_BENCHMARK_H

#pragma once

#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <stdexcept>
#include <functional>
#include <climits>
#include <algorithm>
#include <queue>
#include <map>

#include "algorithms/bfs_solver.h"
#include "algorithms/iddfs_solver.h"
#include "state.h"

enum class algorithm_type : int {
    BFS_SEQ,
    BFS_PAR,
    IDDFS_SEQ,
    IDDFS_PAR
};

struct algorithm_result {
    algorithm_type algorithm_type;
    std::string algorithm_name;
    std::chrono::duration<double> duration;
    bool found_solution;
};

class algorithm_benchmark {
public:
    algorithm_benchmark ( const state_pointer initial_state, int algorithm_mask )
        : initial_state ( initial_state ), algorithm_mask ( algorithm_mask ) {}

    void solve ();

    algorithm_result solve_bfs ( bool parallel );

    algorithm_result solve_iddfs ( bool parallel );
private:
    algorithm_result run_algorithm ( const std::string &name, std::function<algorithm_result()> algorithm );

    void print_results () const;

    state_pointer initial_state;
    int algorithm_mask;
    std::vector<algorithm_result> results;
};



#endif //ALGORITHM_BENCHMARK_H
