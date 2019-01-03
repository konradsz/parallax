#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ContextInfo.hpp"

namespace ogl {
    class Engine;

    class ContextGLFW {
    public:
        ContextGLFW(GLuint window_width, GLuint window_height);
        ~ContextGLFW();

        void loop() const;
        void print_info(bool print_glsl_versions = false, bool print_extensions = false) const;

    private:
        void get_context_info();

    private:
        GLFWwindow* m_window;
        GLuint m_window_width;
        GLuint m_window_height;

        ContextInfo m_context_info;
    };
} // namespace ogl
