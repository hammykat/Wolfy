//
// Created by berke on 9/12/2026.
//

#include "Headers/Objects/Engine.hpp"

namespace Engine {
    void Update() {
        //Level& level = LevelManager::CurrentLevel();

        // level.player.Update();
        //todo WOLFYTODO everything non-rendering wise (racyasting should be done inside the renderer)

        //Renderer::Process(level.walls, level.entities, level.player.camera);

        // Temporary to get the engine to compile
        std::vector<Wall> walls;
        std::vector<Entity> entities;
        Camera cam;
        cam.rayCount = 960;
        Renderer::Process(walls, entities, cam);
    }
}
