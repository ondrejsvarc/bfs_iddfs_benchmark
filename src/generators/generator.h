//
// Created by Ondrej on 12/29/2024.
//

#ifndef GENERATOR_H
#define GENERATOR_H

#pragma once

#include <memory>
#include "../state.h"

using state_pointer = std::shared_ptr<const state>;

class generator {
public:
    virtual ~generator() = default;

    virtual state_pointer generate() = 0;
};

#endif //GENERATOR_H
