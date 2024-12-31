//
// Created by Ondrej on 12/31/2024.
//

#include "algorithm_benchmark.h"

void algorithm_benchmark::solve () {
    const int BFS_SEQ = 1;
    const int BFS_PAR = 2;
    const int IDDFS_SEQ = 4;
    const int IDDFS_PAR = 8;

    if ( algorithm_mask & BFS_SEQ ) results.push_back(run_algorithm("BFS (Sequential)", [this]() { return solve_bfs(false); }));

    if ( algorithm_mask & BFS_PAR ) results.push_back(run_algorithm("BFS (Parallel)", [this]() { return solve_bfs(true); }));

    if ( algorithm_mask & IDDFS_SEQ ) results.push_back(run_algorithm("IDDFS (Sequential)", [this]() { return solve_iddfs(false); }));

    if ( algorithm_mask & IDDFS_PAR ) results.push_back(run_algorithm("IDDFS (Parallel)", [this]() { return solve_iddfs(true); }));

    print_results();
}

algorithm_result algorithm_benchmark::solve_bfs ( bool parallel ) {
    bfs_solver solver(initial_state);
    state_pointer solution;

    auto start_time = std::chrono::steady_clock::now();

    if ( parallel ) {
        solution = solver.solve_par();
    } else {
        solution = solver.solve_seq();
    }

    auto end_time = std::chrono::steady_clock::now();

    std::chrono::duration<double> duration = end_time - start_time;

    return { parallel ? algorithm_type::BFS_PAR : algorithm_type::BFS_SEQ,
             parallel ? "BFS (Parallel)" : "BFS (Sequential)",
             duration, solution != nullptr };
}

algorithm_result algorithm_benchmark::solve_iddfs ( bool parallel ) {
    iddfs_solver solver(initial_state);
    state_pointer solution;

    auto start_time = std::chrono::steady_clock::now();

    if ( parallel ) {
        solution = solver.solve_par();
    } else {
        solution = solver.solve_seq();
    }

    auto end_time = std::chrono::steady_clock::now();

    std::chrono::duration<double> duration = end_time - start_time;

    return { parallel ? algorithm_type::IDDFS_PAR : algorithm_type::IDDFS_SEQ,
             parallel ? "IDDFS (Parallel)" : "IDDFS (Sequential)",
             duration, solution != nullptr };
}

algorithm_result algorithm_benchmark::run_algorithm ( const std::string &name, std::function<algorithm_result()> algorithm ) {
    std::cout << "Running " << name << "..." << std::endl;
    return algorithm();
}

void algorithm_benchmark::print_results () const {
    std::cout << "\nResults:\n";
    std::cout << "--------------------\n";
    for ( const auto& result : results ) {
        std::cout << result.algorithm_name << ": ";
        if ( result.found_solution ) {
            std::cout << "Solution found in " << result.duration.count() << " seconds.\n";
        } else {
            std::cout << "Solution not found. Time: " << result.duration.count() << " seconds.\n";
        }
    }
    std::cout << "--------------------\n";
}