//
// Created by berke on 9/12/2026.
//

#include "Headers/Objects/Player.hpp"

#include <cmath>

#include "Headers/Engine/InputManager.hpp"

void Player::Start() {
    // placeholder
}

void Player::Update() {
    if (InputManager::GetKeyDown(KeyBinds.forwards)) {}
    if (InputManager::GetKeyDown(KeyBinds.backwards)) {}
    if (InputManager::GetKeyDown(KeyBinds.left)) {}
    if (InputManager::GetKeyDown(KeyBinds.right)) {}

    if (KeyBinds.allowKeyboardRotation)  [[likely]] {
        if (InputManager::GetKeyDown(KeyBinds.left)) {}
        if (InputManager::GetKeyDown(KeyBinds.right)) {}
    }

    if (KeyBinds.allowMouseRotation) [[likely]] {
        const float md = InputManager::GetMouseDelta().x;
    }

    const float rotationInRadians = rotation * Constants::DegToRad;

    const float xOffset = currentSpeed * std::cos(rotationInRadians);
    const float yOffset = currentSpeed * std::sin(rotationInRadians);

    position += (Vector2){xOffset, yOffset};
}

void Player::Destroy() {
    // placeholder
}
