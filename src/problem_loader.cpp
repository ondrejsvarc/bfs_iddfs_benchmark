//
// Created by Ondrej on 12/31/2024.
//

#include "problem_loader.h"

void problem_loader::save_problem ( const std::string &filename, const std::string &problem_type, const std::map<std::string, std::string> &parameters ) {
    std::ofstream file(filename);

    if ( !file.is_open() ) throw std::runtime_error("Could not open file for writing: " + filename);

    file << "{\n";
    file << "  \"problem_type\": \"" << problem_type << "\",\n";
    file << "  \"parameters\": {\n";

    bool first = true;
    for ( const auto& pair : parameters ) {
        if ( !first ) file << ",\n";
        file << "    \"" << pair.first << "\": \"" << pair.second << "\"";
        first = false;
    }
    file << "\n  }\n";

    file << "}\n";

    file.close();
}

state_pointer problem_loader::load_problem ( const std::string &filename ) {
    std::ifstream file(filename);

    if ( !file.is_open() ) throw std::runtime_error("Could not open file for reading: " + filename);

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    file.close();

    size_t problem_type_start = content.find("\"problem_type\": \"") + 17;
    size_t problem_type_end = content.find("\"", problem_type_start);
    std::string problem_type = content.substr(problem_type_start, problem_type_end - problem_type_start);

    std::map<std::string, std::string> parameters;
    size_t param_start = content.find("\"parameters\": {") + 15;
    size_t param_end = content.find("}", param_start);
    std::string params_str = content.substr(param_start, param_end - param_start);

    std::stringstream ss(params_str);
    std::string line;
    while ( std::getline(ss, line, ',') ) {
        size_t key_start = line.find("\"") + 1;
        size_t key_end = line.find("\"", key_start);
        std::string key = line.substr(key_start, key_end - key_start);

        size_t value_start = line.find("\"", key_end + 1) + 1;
        size_t value_end = line.find("\"", value_start);
        std::string value = line.substr(value_start, value_end - value_start);

        parameters[key] = value;
    }

    if ( problem_type == "maze" ) {
        return generate_maze(parameters);
    } else if ( problem_type == "sat" ) {
        return generate_sat(parameters);
    } else if ( problem_type == "hanoi" ) {
        return generate_hanoi(parameters);
    } else {
        throw std::runtime_error("Unknown problem type: " + problem_type);
    }
}

state_pointer problem_loader::generate_maze ( const std::map<std::string, std::string> &parameters ) {
    int width = std::stoi(parameters.at("width"));
    int height = std::stoi(parameters.at("height"));
    int seed = std::stoi(parameters.at("seed"));

    std::shared_ptr<generator> generator = std::make_shared<maze_generator>(width, height, seed);
    return generator->generate();
}

state_pointer problem_loader::generate_sat ( const std::map<std::string, std::string> &parameters ) {
    int num_vars = std::stoi(parameters.at("num_variables"));
    int num_clauses = std::stoi(parameters.at("num_clauses"));
    int max_literals = std::stoi(parameters.at("max_literals_per_clause"));
    int seed = std::stoi(parameters.at("seed"));

    std::shared_ptr<generator> generator = std::make_shared<sat_generator>(num_vars, num_clauses, max_literals, seed);
    return generator->generate();
}

state_pointer problem_loader::generate_hanoi ( const std::map<std::string, std::string> &parameters ) {
    int num_pegs = std::stoi(parameters.at("num_pegs"));
    int num_discs = std::stoi(parameters.at("num_discs"));

    std::shared_ptr<generator> generator = std::make_shared<hanoi_generator>(num_pegs, num_discs);
    return generator->generate();
}