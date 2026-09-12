//
// Created by berke on 9/12/2026.
//

#include "Headers/LevelManager.hpp"

namespace LevelManager {
    std::vector<Level> allLevels;
    uint32_t currentLevelIndex = std::numeric_limits<uint32_t>::max();

    Level &CurrentLevel() { return allLevels[currentLevelIndex]; }

    // Look at every single bson file inside a folder, deserialize them and load them into the vector
    // todo WOLFYTODO implement
    bool LoadLevelsFromPath(std::filesystem::path &path) {
        return true;
    }
}
