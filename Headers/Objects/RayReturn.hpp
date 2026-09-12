//
// Created by berke on 9/12/2026.
//

#ifndef WOLFY_RAY_HPP
#define WOLFY_RAY_HPP

#include <vector>

#include "Wall.hpp"
#include "../Math/Vector/Vector2.hpp"

// A ray is just a 2d line (vec2 start and end) so there is no reason to have a ray struct
struct RayWall {
    ID id;
    uint32_t frontTexture, backTexture;
    float height; // Vertical distance of the wall
};


struct RayReturn {
    // A ray should return a vector of every single wall it hit, and a vector of the intersection point
    // The index of the intersection point must be the same as the index of the corresponding wall in their respective vectors

    uint16_t column; // Not sure if this is necessary. it is indication which column of the screen this ray return is responsible for
                     // It might be needed if we want to have reflections or portals that will make the rays move
    std::vector<RayWall> walls;
};

#endif //WOLFY_RAY_HPP