#pragma once

#include <map>
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Shader.hpp"
#include "Sprite.hpp"

namespace ogl {
    class Renderer {
    public:
        Renderer(float frustum_width, float frustum_height);
        ~Renderer();

        void load_texture(const std::string& file_path, const std::string& name);
        void draw_sprite(const Sprite& sprite);
        void clean_up();

    private:
        std::map<std::string, GLuint> m_textures;
        Shader m_shader;
        GLuint m_quad_vertex_array;
    };
} // namespace ogl
