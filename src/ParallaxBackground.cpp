#include "ParallaxBackground.hpp"

namespace ogl {
    ParallaxBackground::ParallaxBackground(GLuint width, GLuint height) :
        m_sprite{{0, 0}, {width, height}} {
    }

    Sprite ParallaxBackground::get_sprite() const {
        return m_sprite;
    }
} // namespace ogl
