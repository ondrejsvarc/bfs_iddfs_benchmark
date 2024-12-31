//
// Created by Ondrej on 12/31/2024.
//

#ifndef PROBLEM_LOADER_H
#define PROBLEM_LOADER_H

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <map>

#include "generators/maze_generator.h"
#include "generators/sat_generator.h"
#include "generators/hanoi_generator.h"


class problem_loader {
public:
    static void save_problem ( const std::string &filename, const std::string &problem_type, const std::map<std::string, std::string> &parameters );

    static state_pointer load_problem ( const std::string &filename );

private:
    static state_pointer generate_maze ( const std::map<std::string, std::string> &parameters );

    static state_pointer generate_sat ( const std::map<std::string, std::string> &parameters );

    static state_pointer generate_hanoi ( const std::map<std::string, std::string> &parameters );
};



#endif //PROBLEM_LOADER_H
