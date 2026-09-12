//
// Created by berke on 9/12/2026.
//

#include <filesystem>
#include <string_view>

#include "Headers/Objects/Engine.hpp"
#include "Headers/Engine/ProjectManager.hpp"

namespace fs = std::filesystem;

int main(int argc, char** argv) {
    fs::path projectFile;

    for (int i = 1; i < argc; ++i) if (std::string_view(argv[i]) == "--project" && i + 1 < argc) projectFile = argv[++i];

    if (projectFile.empty()) {
        spdlog::critical("No --project argument was provided");
        return 1;
    }

    if (!ProjectManager::LoadProjectMetaData(projectFile)) {
        spdlog::critical("Failed to load project: {}", projectFile.string());
        return 1;
    }

    if (!Engine::Initialize()) { spdlog::critical("Failed to initialize engine"); return 1; }
    spdlog::info("Updating walls");

    while (Engine::Running()) Engine::Process();

    Engine::Destroy();
    return 0;
}
