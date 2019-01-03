#include "Renderer.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace ogl {
    GLint uniform_model_location;
    GLint uniform_layer_0_location;
    GLint uniform_layer_1_location;
    GLint uniform_layer_2_location;
    GLint uniform_layer_3_location;
    GLint uniform_layer_4_location;
    GLint uniform_layer_5_location;
    GLint uniform_layer_6_location;
    GLint uniform_offset_location;

    Renderer::Renderer(float frustum_width, float frustum_height) :
        m_shader{"../assets/shader.vert", "../assets/shader.frag"} {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glm::mat4 projection_matrix =
            glm::ortho(0.0f, frustum_width, frustum_height, 0.0f, -1.0f, 1.0f);

        GLint uniform_projection_location = m_shader.get_uniform_location("projection");
        glProgramUniformMatrix4fv(m_shader.id(), uniform_projection_location, 1, GL_FALSE,
                                  glm::value_ptr(projection_matrix));

        uniform_model_location = m_shader.get_uniform_location("model");
        uniform_layer_0_location = m_shader.get_uniform_location("layer_0");
        uniform_layer_1_location = m_shader.get_uniform_location("layer_1");
        uniform_layer_2_location = m_shader.get_uniform_location("layer_2");
        uniform_layer_3_location = m_shader.get_uniform_location("layer_3");
        uniform_layer_4_location = m_shader.get_uniform_location("layer_4");
        uniform_layer_5_location = m_shader.get_uniform_location("layer_5");
        uniform_layer_6_location = m_shader.get_uniform_location("layer_6");
        uniform_offset_location = m_shader.get_uniform_location("offset");

        GLfloat vertices[] = {// Pos      // Tex
                              0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                              0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                              1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f};

        GLuint vertex_buffer;
        glGenBuffers(1, &vertex_buffer);

        glGenVertexArrays(1, &m_quad_vertex_array);
        glBindVertexArray(m_quad_vertex_array);

        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat),
                              reinterpret_cast<GLvoid*>(0));
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &vertex_buffer);

        load_texture("../assets/textures/layer_0.png", "layer_0");
        load_texture("../assets/textures/layer_1.png", "layer_1");
        load_texture("../assets/textures/layer_2.png", "layer_2");
        load_texture("../assets/textures/layer_3.png", "layer_3");
        load_texture("../assets/textures/layer_4.png", "layer_4");
        load_texture("../assets/textures/layer_5.png", "layer_5");
        load_texture("../assets/textures/layer_6.png", "layer_6");

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_textures["layer_0"]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_textures["layer_1"]);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, m_textures["layer_2"]);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, m_textures["layer_3"]);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, m_textures["layer_4"]);
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_2D, m_textures["layer_5"]);
        glActiveTexture(GL_TEXTURE6);
        glBindTexture(GL_TEXTURE_2D, m_textures["layer_6"]);

        m_shader.use();
        glUniform1i(uniform_layer_0_location, 0);
        glUniform1i(uniform_layer_1_location, 1);
        glUniform1i(uniform_layer_2_location, 2);
        glUniform1i(uniform_layer_3_location, 3);
        glUniform1i(uniform_layer_4_location, 4);
        glUniform1i(uniform_layer_5_location, 5);
        glUniform1i(uniform_layer_6_location, 6);
    }

    Renderer::~Renderer() {
        glDeleteVertexArrays(1, &m_quad_vertex_array);
    }

    void Renderer::load_texture(const std::string& file_path, const std::string& name) {
        GLuint texture = 0;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width;
        int height;
        int no_of_channels;
        unsigned char* data = stbi_load(file_path.c_str(), &width, &height, &no_of_channels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                         data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cerr << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);

        m_textures[name] = texture;
    }

    void Renderer::draw_sprite(const Sprite& sprite) {
        m_shader.use();

        glProgramUniformMatrix4fv(m_shader.id(), uniform_model_location, 1, GL_FALSE,
                                  glm::value_ptr(sprite.get_model_matrix()));

        float time = glfwGetTime();
        const auto offset = [time](float speed) { return speed * time; };
        glUniform1f(uniform_offset_location, offset(0.3f));

        glBindVertexArray(m_quad_vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindVertexArray(0);
    }
} // namespace ogl
