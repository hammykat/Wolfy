//
// Created by berke on 9/12/2026.
//

#ifndef WOLFY_PLAYER_HPP
#define WOLFY_PLAYER_HPP

#include "../Math/Vector/Vector2.hpp"
#include "SDL3/SDL_scancode.h"


struct Camera { // Putting this outside the Player struct for Renderer to be able to see
    float fov = 90.0f;
    float fovRadians = fov * Constants::DegToRad;
    uint16_t rayCount = 960; // Should be equal to screen width for maximum resolution
    float renderDistance = 256.0f;
    float wallHeight = 64.0f;
};

// Since there can only be one player, there is no reason to make it a struct. But this approach is better for future-safety
// and incase we want to add multiplayer later
// For now it is good
struct Player {
    Vector2 position{0.0f, 0.0f};
    float rotation = 0.0f;
    float currentSpeed = 0.0f; // Useful when adding acceleration/deacceleration like Doom

    Camera camera;

    struct Movement {
        float startSpeed = 2.0f; // The speed the player will be the frame a movement key is pressed
        float maxWalkSpeed = 5.0f; // the speed the player will reach after the acceleration is completed while walking
        float walkAccTime = 0.2f; // The time in seconds it takes for the current speed to reach maxWalkingSpeed while walking

        float startRunSpeed = 4.0f; // Same thing but for running
        float maxRunSpeed = 8.0f;
        float runAccTime = 0.3f;

        float rotationSpeed = 3.0f; // The rotation speed of the camera
    } Movement;

    struct KeyBinds {
        SDL_Scancode forwards = SDL_SCANCODE_W;
        SDL_Scancode backwards = SDL_SCANCODE_S;
        SDL_Scancode left = SDL_SCANCODE_A;
        SDL_Scancode right = SDL_SCANCODE_D;

        SDL_Scancode rotateRight = SDL_SCANCODE_RIGHT;
        SDL_Scancode rotateLeft = SDL_SCANCODE_LEFT;

        bool allowMouseRotation = true;
        bool allowKeyboardRotation = true;
    } KeyBinds;

    void Start();
    void Update();
    void Destroy();
};

#endif //WOLFY_PLAYER_HPP