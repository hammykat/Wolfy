//
// Created by berke on 9/12/2026.
//

#ifndef WOLFY_LEVEL_HPP
#define WOLFY_LEVEL_HPP

#include <vector>
#include "Wall.hpp"
#include "Entities.hpp"

// A level should be the single source of truth for everything related to storing information about the level
struct Level {
    std::vector<Wall> walls;
    std::vector<Entity> entities;
};

#endif //WOLFY_LEVEL_HPP