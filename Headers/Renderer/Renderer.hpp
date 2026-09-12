//
// Created by berke on 9/12/2026.
//

#ifndef WOLFY_RENDERER_HPP
#define WOLFY_RENDERER_HPP
#include <vector>

#include "Headers/Objects/Wall.hpp"
#include "Headers/Objects/Entities.hpp"
#include "Headers/Objects/Player.hpp"
#include "SDL3/SDL_video.h"

namespace Renderer {
    bool Initialize(); // Initialize is called one before the engine starts

    void StartFrame(); // Start is called at the beginning of each frame
    void Update(const std::vector<Wall>& walls, const std::vector<Entity>& entities, const Camera& cam);
    void EndFrame(); // End is called at the end of a frame

    bool Destroy(); // Destor is called after the engine closes

    // A small helper that just calls other cuntions
    inline void Process(const std::vector<Wall>& walls, const std::vector<Entity>& entities, Camera& cam) {
        StartFrame();
        Update(walls, entities, cam);
        EndFrame();
    }

    SDL_Window* GetWindow();

    void OnWindowResize();
}

#endif //WOLFY_RENDERER_HPP