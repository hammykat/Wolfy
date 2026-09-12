//
// Created by berke on 9/12/2026.
//

#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>
#include "SDL3/SDL_render.h"

#include "Headers/Renderer/Renderer.hpp"

namespace {
    constexpr SDL_InitFlags sdlFlags = SDL_INIT_VIDEO | SDL_INIT_AUDIO;

    SDL_Window* window;
    SDL_Renderer* renderer;

    constexpr int WINDOW_FLAGS = SDL_WINDOW_RESIZABLE /* | SDL_WINDOW_MAXIMIZED */;

    // Note: these values won't matter if SDL_WINDOW_MAXIMIZED is enabled.
    constexpr int START_SCREEN_WIDTH = 960;
    constexpr int START_SCREEN_HEIGHT = 640;
}

namespace Renderer {
    bool Initialize() {
        if (!SDL_Init(sdlFlags)) {
            spdlog::critical("Could not initialize SDL");
            return true;
        }

        if (!SDL_CreateWindowAndRenderer("Wolfy Engine", START_SCREEN_WIDTH, START_SCREEN_HEIGHT, WINDOW_FLAGS, &window, &renderer)) {
            spdlog::critical("Could not create window or renderer");
            return true;
        }

        return false;
    }

    void StartFrame() {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
    }

    void Update(const std::vector<Wall>& walls, const std::vector<Entity>& entities, Camera& cam) {
        // todo WOLFYTODO Raycast here
    }

    void EndFrame() {
        SDL_RenderPresent(renderer);
    }

    bool Destroy() {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return true;
    }

    SDL_Window* GetWindow() { return window; }

    void OnWindowResize() {
        int w, h;
        SDL_GetWindowSizeInPixels(window, &w, &h);

    }
}

