//
// Created by berke on 9/12/2026.
//

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <spdlog/spdlog.h>
#include <SDL3/SDL_render.h>

#include "Headers/Renderer/Renderer.hpp"

#include <ranges>

#include "Headers/Engine/ProjectManager.hpp"

using TextureID = uint32_t;

// Initialization things
namespace {
    SDL_Window* window;
    SDL_Renderer* renderer;

    int screenWidth, screenHeight;

    constexpr SDL_InitFlags sdlFlags = SDL_INIT_VIDEO | SDL_INIT_AUDIO;
    constexpr int WINDOW_FLAGS = SDL_WINDOW_RESIZABLE /* | SDL_WINDOW_MAXIMIZED */;

    // Note: these values won't matter if SDL_WINDOW_MAXIMIZED is enabled.
    constexpr int START_SCREEN_WIDTH = 960;
    constexpr int START_SCREEN_HEIGHT = 640;

    std::unordered_map<std::string, TextureID> fileNameToId;
    std::unordered_map<TextureID, SDL_Texture*> idToTexture;

    bool CreateTexturesLookupTable() {
        const fs::path assetsPath = ProjectManager::GetAssetsPath();

        if (assetsPath.empty() || !fs::is_directory(assetsPath)) {
            spdlog::critical("Invalid project assets directory: '{}'", assetsPath.string());
            return false;
        }

        uint32_t nextTextureId = 0;

        // Loop through all files and subdirectories
        for (const auto& entry : fs::recursive_directory_iterator(assetsPath)) {

            // Skip directories and only process regular files
            if (entry.is_regular_file()) {
                fs::path filePath = entry.path();
                std::string extension = filePath.extension().string();

                // Convert extension to lowercase to safely catch .PNG, .png, etc.
                std::ranges::transform(extension, extension.begin(), ::tolower);

                if (extension == ".png" || extension == ".jpg" || extension == ".jpeg") {
                    // Get the path relative to the assets folder (e.g. "characters/player.png")
                    // generic_string() ensures forward slashes ('/') are used even on Windows.
                    std::string relativeName = fs::relative(filePath, assetsPath).generic_string();

                    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath.string().c_str());

                    if (texture == nullptr) {
                        spdlog::critical("Failed to load texture: {} SDL_Image Error: ", filePath.string(), SDL_GetError());
                        return false;
                    }

                    uint32_t currentId = nextTextureId++;

                    fileNameToId[relativeName] = currentId;
                    idToTexture[currentId] = texture;

                    spdlog::info("Loaded {} with id {}", relativeName, currentId);
                }
            }
        }

        return true;
    }

    void CleanupTextures() {
        for (const auto &texture: idToTexture | std::views::values) if (texture != nullptr) SDL_DestroyTexture(texture);
        idToTexture.clear();
        fileNameToId.clear();
    }
}

// Runtime functions
namespace {
    TextureID GetTextureIDByFileName(const std::string& name) { return fileNameToId[name]; }

    // Returns the texture with the file name inside the current project's Assets directory (subdirectories included)
    // Not the most optimal since it requires passing strings each frame
    // Note: do not include the file extension
    SDL_Texture* GetTextureByFileName(const std::string& fileName) { return idToTexture[fileNameToId[fileName]];}

    // Same thing but with the ID
    // Faster because it is just passing an integer
    // Requires to cache the IDs first
    SDL_Texture* GetTextureByID(const TextureID id) { return idToTexture[id]; }
}

namespace Renderer {
    bool Initialize() {
        if (!SDL_Init(sdlFlags)) {
            spdlog::critical("Could not initialize SDL");
            return false;
        }

        if (!SDL_CreateWindowAndRenderer("Wolfy Engine", START_SCREEN_WIDTH, START_SCREEN_HEIGHT, WINDOW_FLAGS, &window, &renderer)) {
            spdlog::critical("Could not create window or renderer");
            return false;
        }

        if (!CreateTexturesLookupTable()) {
            spdlog::critical("Could not create texture lookup table");
            return false;
        }

        return true;
    }

    void StartFrame() {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
    }

    void Update(const std::vector<Wall>& walls, const std::vector<Entity>& entities, Camera& cam) {
        for (int i = 0; i < cam.rayCount; i++) {
            // todo WOLFYTODO Raycast and draw to screen here
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_Texture* texture = GetTextureByFileName("test");

        SDL_RenderTexture(renderer, texture, NULL, NULL);

    }

    void EndFrame() {
        SDL_RenderPresent(renderer);
    }

    bool Destroy() {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        CleanupTextures();
        SDL_Quit();
        return true;
    }

    SDL_Window* GetWindow() { return window; }

    // Gets called by the InputManager whenever the window is resized
    void OnWindowResize() { SDL_GetWindowSizeInPixels(window, &screenWidth, &screenHeight);}
}

