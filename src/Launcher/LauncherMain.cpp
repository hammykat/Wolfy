//
// Created by berke on 5/3/2026.
//

#include <SDL3/SDL_main.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <chrono>

#include "../../Headers/Engine/ProjectManager.hpp"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace fs = std::filesystem;
using json = nlohmann::json;

// I don't know where else to put these
void InitLog(const fs::path& projectsPath) {
    const fs::path logPath = projectsPath.parent_path() / "Logs" / "launcher_log.txt";

    try {
        fs::create_directories(logPath.parent_path());

        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        consoleSink->set_level(spdlog::level::trace);

        // Rotating file sink instead of a truncating one: each launch starts a fresh
        // launcher_log.txt (rotate_on_open = true) but the last few runs are kept as
        // launcher_log.1.txt, launcher_log.2.txt, etc., so a crash can still be diagnosed
        // after the fact instead of being wiped by the very next launch.
        // constexpr size_t maxLogFileSize = 5 * 1024 * 1024; // 5 MB
        // constexpr size_t maxLogFileCount = 3;
        // auto fileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        //     logPath.string(), maxLogFileSize, maxLogFileCount, /*rotate_on_open=*/true);

        // BASIC SINK FILE BECAUSE WE DONT NEED ROTATING RIGHT NOW
        auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logPath.string(),true);

        std::vector<spdlog::sink_ptr> sinks{consoleSink, fileSink};
        auto logger = std::make_shared<spdlog::logger>("Launcher", sinks.begin(), sinks.end());

        spdlog::set_default_logger(logger);

        spdlog::flush_on(spdlog::level::warn);
    }
    catch (const spdlog::spdlog_ex &ex) {
        std::cerr << ex.what() << std::endl;
    }
}
bool CreateDirectories(const fs::path& projectsPath) {
    try {
        fs::create_directories(projectsPath);
        spdlog::info("Projects folder ready at: {}", projectsPath.string());
    }
    catch (std::exception &e) {
        spdlog::critical("Failed to create projects directory {}", e.what());
        return false;
    }
    return true;
}

int main(int argc, char** argv) {
    const fs::path projectsPath = ProjectManager::GetDefaultProjectsFolder();

    if (!CreateDirectories(projectsPath)) {
        spdlog::critical("Could not create directories in LauncherMain.cpp");
        return 1;
    }
    InitLog(projectsPath);
    spdlog::info("Engine started");

    //todo WOLFYTODO add a launcher for creating and selecting projects

    // Creates and/or opens the project at C:/Documents/Wolfy Engine/Projects/ or the Linux equivelant
    ProjectManager::CreateProjectDirectory("DevProject");

    return 0;
}
