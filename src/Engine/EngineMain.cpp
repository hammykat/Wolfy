//
// Created by berke on 9/12/2026.
//

#include "Headers/Objects/Engine.hpp"

int main() {
    Engine::Initialize();

    while (Engine::Running()) Engine::Process();

    Engine::Destroy();
    return 0;
}
