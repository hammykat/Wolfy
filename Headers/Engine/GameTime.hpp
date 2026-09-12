//
// Created by berke on 4/5/2026.
//

#ifndef WOLFY_ENGINE_GAMETIME_H
#define WOLFY_ENGINE_GAMETIME_H

namespace GameTime {
    extern float deltaTime;
    extern double timeInSeconds; // Seconds passed since game start
    extern double frame; // Frames passed since game start
    extern float smoothedFPS;

    void Update();
    float GetFPS();
}

#endif //WOLFYENGINE_GAMETIME_H