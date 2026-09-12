//
// Created by berke on 9/12/2026.
//

#ifndef WOLFY_LEVELMANAGER_HPP
#define WOLFY_LEVELMANAGER_HPP

#include <filesystem>

#include "Objects/Level.hpp"

namespace LevelManager {
    Level& CurrentLevel();
    bool LoadLevelsFromPath(std::filesystem::path &path);
}

#endif //WOLFY_LEVELMANAGER_HPP