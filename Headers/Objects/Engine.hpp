//
// Created by berke on 9/12/2026.
//

#ifndef WOLFY_ENGINE_HPP
#define WOLFY_ENGINE_HPP

// This namespace is just helpers that call other functions. This file should not do any actual code.
// (Aside from initializing the engine logger because I don't know where else to put it

#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>

#include "Headers/LevelManager.hpp"
#include "Headers/Engine/GameTime.hpp"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include "Headers/Engine/ProjectManager.hpp"
#include "Headers/Engine/InputManager.hpp"
#include "Headers/Renderer/Renderer.hpp"

inline bool InitEngineLogger() {
    SDL_Log("Engine Logging");
    const fs::path logPath = ProjectManager::GetEngineFolder() / "Logs"/ "engine_log.txt";

    try {
        fs::create_directories(logPath.parent_path());

        const auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

        consoleSink->set_level(spdlog::level::trace);

        const auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logPath.string(),true);

        fileSink->set_level(spdlog::level::trace);

        std::vector<spdlog::sink_ptr> sinks{ consoleSink, fileSink};

        const auto logger = std::make_shared<spdlog::logger>(
            "Engine",
            sinks.begin(),
            sinks.end()
        );

        logger->set_level(spdlog::level::trace);

        spdlog::set_default_logger(logger);
        spdlog::set_level(spdlog::level::trace);
        spdlog::flush_on(spdlog::level::trace);

        spdlog::info("Engine logger initialized");

        return true;
    }
    catch (const spdlog::spdlog_ex& exception) {
        SDL_Log("Failed to initialize engine logger: %s", exception.what());

        return false;
    }
}

namespace Engine {
    inline bool Initialize() {
        spdlog::info("Starting Engine Initilization");
        // Creates C:/Documents/Wolfy Engine if it is not already created (should work for Linux & Mac as well but not sure)
        ProjectManager::GetEngineFolder();
        InitEngineLogger();


        if (!Renderer::Initialize()) { spdlog::critical("Failed to initialize renderer"); return false;}
        InputManager::Initialize(Renderer::GetWindow());

        spdlog::info("Engine initialized successfully");
        return true;
    }

    inline void BeginFrame() {
        InputManager::BeginFrame();
        GameTime::Update();
    }

    void Update();

    // Just a small helper that calls other functions
    inline void Process() {
        BeginFrame();
        Update();
    }

    inline void Destroy() {
        Renderer::Destroy();
    }

    inline bool Running() {
        return !InputManager::QuitRequested() || InputManager::GetKeyDown(SDL_SCANCODE_ESCAPE);
    }
}

#endif //WOLFY_ENGINE_HPP