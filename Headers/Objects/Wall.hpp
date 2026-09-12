//
// Created by berke on 9/12/2026.
//

#ifndef WOLFY_WALL_HPP
#define WOLFY_WALL_HPP

#include <algorithm>
#include <string>

#include "ObjectTypes.h"
#include "../Math/Vector/Vector2.hpp"
#include "../Math/Vector/Vector2Math.hpp"
#include "../Math/Vector/Vector4.hpp"

struct Wall {
    ID id;
    Vector2 start, end;
    std::string textureFileName;

    // Read only — do not change
    Vector2 dir, normal, vector;
    float length{};

    Wall(const Vector2& start, const Vector2& end, const Vector4 color, std::string textureFileName = {})
    : start(start), end(end), textureFileName(std::move(textureFileName)) {

        RefreshDerived();
    }

    // Recomputes dir/normal/vector/lengthSq/length from the current
    // start/end. The constructor calls this itself; call it again after
    // directly mutating start or end so those fields don't go stale - this
    // is the only place that math lives, so it can't drift between the
    // two call sites.
    void RefreshDerived() {
        vector = end - start;
        length = Vector2Math::Length(vector);

        if (length > 0.00001f) {
            dir = vector / length;
            normal = {-dir.y, dir.x};
        }
        else {
            dir = {0.0f, 0.0f};
            normal = {0.0f, 0.0f};
        }
    }
};

#endif //WOLFY_WALL_HPP