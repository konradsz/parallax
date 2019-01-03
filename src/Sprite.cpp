#include "Sprite.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace ogl {
    Sprite::Sprite(const glm::vec2& position, const glm::vec2& size, GLfloat rotation) :
        m_position{position}, m_size{size}, m_rotation{rotation} {
        recalculate_model_matrix();
    }

    glm::mat4 Sprite::get_model_matrix() const {
        return m_model_matrix;
    }

    void Sprite::recalculate_model_matrix() {
        m_model_matrix = glm::mat4{1.0f};

        // translation
        m_model_matrix = glm::translate(m_model_matrix, glm::vec3(m_position, 0.0f));

        // rotation
        m_model_matrix =
            glm::translate(m_model_matrix, glm::vec3(0.5f * m_size.x, 0.5f * m_size.y, 0.0f));
        m_model_matrix = glm::rotate(m_model_matrix, m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
        m_model_matrix =
            glm::translate(m_model_matrix, glm::vec3(-0.5f * m_size.x, -0.5f * m_size.y, 0.0f));

        // scale
        m_model_matrix = glm::scale(m_model_matrix, glm::vec3(m_size, 1.0f));
    }
} // namespace ogl
