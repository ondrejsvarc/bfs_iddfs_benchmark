//
// Created by Ondrej on 12/29/2024.
//

#include "maze_generator.h"

// State implementation
[[nodiscard]] std::vector<state_pointer> maze_state::get_descendents () const {
    std::vector<state_pointer> children;
    int x = current_position.first;
    int y = current_position.second;

    // Up, Down, Left, Right
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        // Check if inside the grid and not a wall
        if ( nx >= 0 && nx < static_cast<int>(grid.size()) && ny >= 0 && ny < static_cast<int>(grid[0].size()) && grid[nx][ny] != WALL ) {
            children.push_back(std::make_shared<const maze_state>(shared_from_this(), grid, std::make_pair(nx, ny)));
        }
    }
    return children;
}

[[nodiscard]] bool maze_state::is_goal () const {
    // Check if goal
    return grid[current_position.first][current_position.second] == GOAL;
}

[[nodiscard]] unsigned long long maze_state::get_identifier () const {
    // Simple identifier - combination of x and y
    return (current_position.first * grid[0].size() + current_position.second);
}

[[nodiscard]] maze_state::cell_type maze_state::get_cell(int x, int y) const {
    return grid[x][y];
}


// Generator implementation
state_pointer maze_generator::generate () {
    // Init grid - everything is a wall
    std::vector<std::vector<maze_state::cell_type>> grid(height, std::vector<maze_state::cell_type>(width, maze_state::cell_type::WALL));

    // Random starting point (must be odd x and y)
    std::uniform_int_distribution<> dist_x(0, (width - 1) / 2);
    std::uniform_int_distribution<> dist_y(0, (height - 1) / 2);
    int start_x = dist_x(random_engine) * 2 + 1;
    int start_y = dist_y(random_engine) * 2 + 1;

    grid[start_y][start_x] = maze_state::cell_type::START;

    // Generate maze recursive
    generate_maze_recursive(grid, start_x, start_y);

    // Random goal point (must be odd x and y)
    int goal_x, goal_y;
    do {
        goal_x = dist_x(random_engine) * 2 + 1;
        goal_y = dist_y(random_engine) * 2 + 1;
    } while ( grid[goal_y][goal_x] != maze_state::cell_type::PATH || (goal_x == start_x && goal_y == start_y) );

    grid[goal_y][goal_x] = maze_state::cell_type::GOAL;

    return std::make_shared<const maze_state>(nullptr, grid, std::make_pair(start_x, start_y));
}

void maze_generator::generate_maze_recursive ( std::vector<std::vector<maze_state::cell_type>> &grid, int x, int y ) {
    // Mark current as PATH
    if ( grid[y][x] == maze_state::cell_type::WALL ) grid[y][x] = maze_state::cell_type::PATH;

    // Randomise directions
    std::vector<std::pair<int, int>> directions = {{0, -2}, {0, 2}, {-2, 0}, {2, 0}};
    std::shuffle(directions.begin(), directions.end(), random_engine);

    // Iterate directions
    for ( const auto &dir : directions ) {
        int nx = x + dir.first;
        int ny = y + dir.second;

        // Check if new position inside grid and wall
        if (nx > 0 && nx < width-1 && ny > 0 && ny < height-1 && grid[ny][nx] == maze_state::cell_type::WALL) {
            // Remove wall
            grid[y + dir.second / 2][x + dir.first / 2] = maze_state::cell_type::PATH;

            generate_maze_recursive(grid, nx, ny);
        }
    }
}