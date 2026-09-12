//
// Created by berke on 5/3/2026.
//
#include "Headers/Engine/ProjectManager.hpp"

#include <cstdlib>
#include <filesystem>
#include <fstream>

#include <SDL3/SDL_filesystem.h>
#include <spdlog/spdlog.h>

namespace fs = std::filesystem;

namespace ProjectManager {

    fs::path GetUserHomeDirectory() {
#if _WIN32
        const char* userProfile = std::getenv("USERPROFILE");
#else
        const char* userProfile = std::getenv("HOME");
#endif

        if (userProfile != nullptr) return fs::path(userProfile);

        spdlog::warn("Could not find user home directory. Falling back to current working directory.");
        return fs::current_path();
    }

    fs::path GetContentRootPath() {
#ifdef TILKY_CONTENT_ROOT
        return fs::path(TILKY_CONTENT_ROOT);
#else
        spdlog::warn("TILKY_CONTENT_ROOT is not defined. Falling back to current working directory.");
        return fs::current_path();
#endif
    }

    void CreateEngineFolder() {
        fs::path folderPath = GetEngineFolder();

        // Check if it exists, and create it (along with any missing parent folders) if it doesn't
        if (!fs::exists(folderPath)) {
            fs::create_directories(folderPath);
            spdlog::info("Created engine folder");
        }
    }

    fs::path GetEngineFolder() {
        return GetUserHomeDirectory() / "Documents" /  "Wolfy Engine";
    }
}