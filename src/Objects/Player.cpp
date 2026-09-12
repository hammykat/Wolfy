//
// Created by berke on 9/12/2026.
//

#include "Headers/Objects/Player.hpp"
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

    }
}

void Player::Destroy() {
    // placeholder
}
