#pragma once

#include <string>

#include <GL/glew.h>

class Shader {
public:
    Shader() = default;
    Shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path);

    void use() const;
    GLuint id() const;
    GLint get_uniform_location(const char* uniform_name) const;

private:
    std::string read_from_file(const std::string& file_name) const;
    GLuint compile(GLenum type, const std::string& source) const;
    GLuint link(GLuint vertex_shader, GLuint fragment_shader) const;

private:
    GLuint m_id;
};
