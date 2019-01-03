#define GLEW_STATIC
#include <GL/glew.h>

#include "Shader.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

Shader::Shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path) {
    const auto vertex_shader_code = read_from_file(vertex_shader_path);
    const auto fragment_shader_code = read_from_file(fragment_shader_path);

    const auto vertex_shader = compile(GL_VERTEX_SHADER, vertex_shader_code);
    const auto fragment_shader = compile(GL_FRAGMENT_SHADER, fragment_shader_code);

    m_id = link(vertex_shader, fragment_shader);
}

void Shader::use() const {
    glUseProgram(m_id);
}

GLuint Shader::id() const {
    return m_id;
}

GLint Shader::get_uniform_location(const char* uniform_name) const {
    return glGetUniformLocation(m_id, uniform_name);
}

std::string Shader::read_from_file(const std::string& file_path) const {
    std::string shader_code;
    std::ifstream file{file_path, std::ifstream::in};

    if (!file.good()) {
        std::cerr << "Cannot read shader from file: " << file_path << std::endl;
        std::terminate();
    }

    file.seekg(0, std::ios::end);
    shader_code.resize(static_cast<unsigned int>(file.tellg()));
    file.seekg(0, std::ios::beg);

    shader_code.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    file.close();

    return shader_code;
}

GLuint Shader::compile(GLenum type, const std::string& source) const {
    GLint compile_result = 0;

    GLuint shader = glCreateShader(type);
    const char* source_cstr = source.c_str();
    const int source_size = source.size();

    glShaderSource(shader, 1, &source_cstr, &source_size);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

    if (compile_result == GL_FALSE) {
        GLint max_length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);
        std::vector<GLchar> error_log(max_length);
        glGetShaderInfoLog(shader, max_length, nullptr, &error_log[0]);
        std::cerr << "Compiling " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                  << " shader failed!\n"
                  << &error_log[0] << std::endl;

        glDeleteShader(shader);

        return -1;
    }

    return shader;
}

GLuint Shader::link(GLuint vertex_shader, GLuint fragment_shader) const {
    GLint link_result = 0;

    GLuint id = glCreateProgram();
    glAttachShader(id, vertex_shader);
    glAttachShader(id, fragment_shader);

    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &link_result);

    if (link_result == GL_FALSE) {
        GLint max_length = 0;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &max_length);
        std::vector<char> error_log(max_length);
        glGetProgramInfoLog(id, max_length, nullptr, &error_log[0]);
        std::cerr << "Linking shader program failed!\n" << &error_log[0] << std::endl;

        glDeleteProgram(id);
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }

    glDetachShader(id, vertex_shader);
    glDetachShader(id, fragment_shader);

    return id;
}
