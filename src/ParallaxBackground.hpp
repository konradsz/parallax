#pragma once

#include "Sprite.hpp"

namespace ogl {
    class ParallaxBackground {
    public:
        ParallaxBackground(GLuint width, GLuint height);
        ~ParallaxBackground() = default;

        Sprite get_sprite() const;

    private:
        Sprite m_sprite;
    };
} // namespace ogl
