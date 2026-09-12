//
// Created by berke on 9/12/2026.
//

#ifndef WOLFY_ENTITY_H
#define WOLFY_ENTITY_H

#include <string>
#include <array>
#include "Headers/Math/Vector/Vector2.hpp"

// If single, the entity will always display the same texture
// If four, the entity will change its sprite every 90 degrees based on the camera angle and entity rotation
// If four, the entity will change its sprite every 45 degrees based on the camera angle and entity rotation
enum class SideCount {
    SINGLE,
    FOUR_SIDED,
    EIGHT_SIDED
};

// Making this a class since the engine will follow an OOP approach and there will be other classes that derive from entity
class Entity {
public:
    // No need for getters and setter, they are just unnecessary bloat without providing any meaningful functionality
    Vector2 position;
    float rotation{};

    std::array<std::string,8> textureFileNames;
    SideCount side = SideCount::SINGLE;
};



#endif //WOLFY_ENTITY_H