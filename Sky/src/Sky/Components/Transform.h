#pragma once

#include <glm/glm.hpp>

namespace Sky {
    struct Transform {
        glm::vec3 Position;
        glm::vec3 Rotation;
        glm::vec3 Scale;

        Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
            : Position(position), Rotation(rotation), Scale(scale) {
        }
    };

}