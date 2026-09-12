//
// Created by berke on 9/12/2026.
//
#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>

#include "Headers/Engine/GameTime.hpp"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include "Headers/Engine/ProjectManager.hpp"
#include "Headers/Engine/InputManager.hpp"

bool InitEngineLogger() {
    const fs::path logPath = ProjectManager::GetEngineFolder() / "Logs"/ "engine_log.txt";

    try {
        fs::create_directories(logPath.parent_path());

        const auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

        consoleSink->set_level(spdlog::level::trace);

        const auto fileSink =
            std::make_shared<spdlog::sinks::basic_file_sink_mt>(
                logPath.string(),
                true
            );

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

int main() {
    ProjectManager::CreateEngineFolder(); // Creates C:/Documents/Wolfy Engine if it is not already created (should handle Linux  & Mac as well)
    InitEngineLogger();

    constexpr SDL_InitFlags sdlFlags = SDL_INIT_VIDEO | SDL_INIT_AUDIO;
    if (!SDL_Init(sdlFlags)) {
        spdlog::critical("Could not initalize SDL");
        return EXIT_FAILURE;
    }

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    //todo WOLFYTODO make these settings
    constexpr int SCREEN_WIDTH = 960;
    constexpr int SCREEN_HEIGHT = 640;
    constexpr int WINDOW_FLAGS =  SDL_WINDOW_RESIZABLE;

    if (!SDL_CreateWindowAndRenderer("Wolfy Engine", SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_FLAGS, &window, &renderer)) {
        spdlog::critical("Could not create window or renderer");
        return EXIT_FAILURE;
    }

    InputManager::Initialize(window);

    bool running = true;
    while (running) {
        InputManager::BeginFrame();
        GameTime::Update();

        running = !InputManager::QuitRequested() || InputManager::GetKeyDown(SDL_SCANCODE_ESCAPE);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_FRect rect = { 200, 300, 50, 80 };
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}
