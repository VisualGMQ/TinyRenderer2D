#ifndef VMATH_HPP
#define VMATH_HPP

#include <cstdint>

#include "glm/glm.hpp"

namespace tinyrenderer2d {

using Point = glm::vec2;
using Color = glm::vec4;

struct ColorfulPoint {
    Point point;
    Color color;
};

struct Rect {
    int x;
    int y;
    int w;
    int h;
};

struct Size {
    int w;
    int h;
};

}; // NAMESPACE tinyrender2d

#endif
