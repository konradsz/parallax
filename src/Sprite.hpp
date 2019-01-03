#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace ogl {
    class Sprite {
    public:
        Sprite(const glm::vec2& position, const glm::vec2& size, GLfloat rotation = 0.0f);
        ~Sprite() = default;

        glm::mat4 get_model_matrix() const;

    private:
        void recalculate_model_matrix();

    private:
        glm::vec2 m_position;
        glm::vec2 m_size;
        GLfloat m_rotation;

        glm::mat4 m_model_matrix;
    };
} // namespace ogl
