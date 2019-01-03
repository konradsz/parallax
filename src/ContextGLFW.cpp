#include "ContextGLFW.hpp"

#include <iostream>
#include <string>

#include "Renderer.hpp"
#include "ParallaxBackground.hpp"

namespace {
    void key_callback(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mode*/) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }

    void window_size_callback(GLFWwindow* window, int /*width*/, int /*height*/) {
        int width = 0;
        int height = 0;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
    }
} // namespace

namespace ogl {
    ContextGLFW::ContextGLFW(GLuint window_width, GLuint window_height) :
        m_window_width(window_width), m_window_height(window_height) {
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            std::terminate();
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindowHint(GLFW_REFRESH_RATE, 60);

        m_window = glfwCreateWindow(m_window_width, m_window_height, "engine", nullptr, nullptr);
        if (!m_window) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            std::terminate();
        }
        glfwMakeContextCurrent(m_window);
        glfwSetWindowTitle(m_window, "engine");

        glfwSetKeyCallback(m_window, key_callback);
        glfwSetWindowSizeCallback(m_window, window_size_callback);

        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK) {
            std::cerr << "Failed to initialize GLEW" << std::endl;
            glfwTerminate();
            std::terminate();
        }
        glGetError(); // initializing GLEW causes GL_INVALID_ENUM error flag to be set
                      // glGetError() is called to clear that flag

        int width = 0;
        int height = 0;
        glfwGetFramebufferSize(m_window, &width, &height);
        glViewport(0, 0, width, height);

        get_context_info();
    }

    ContextGLFW::~ContextGLFW() {
        glfwTerminate();
    }

    void ContextGLFW::loop() const {
        Renderer renderer(m_window_width, m_window_height);
        ParallaxBackground background(m_window_width, m_window_height);

        double last_time = glfwGetTime();
        unsigned int fps_counter = 0;

        while (!glfwWindowShouldClose(m_window)) {
            ++fps_counter;
            double current_time = glfwGetTime();

            if (current_time - last_time >= 1.0f) {
                last_time = current_time;
                const std::string window_title = "engine FPS: " + std::to_string(fps_counter);
                glfwSetWindowTitle(m_window, window_title.c_str());
                fps_counter = 0;
            }

            glfwPollEvents();

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // renderer.draw_sprite({0.0f, 0.0f}, {100.0f, 100.0f}, 45.0f);
            //renderer.draw_sprite({0.0f, 0.0f}, {1280.0f, 720.0f}, 0.0f);
            renderer.draw_sprite(background.get_sprite());

            glfwSwapBuffers(m_window);
        }
    }

    void ContextGLFW::print_info(bool print_glsl_versions, bool print_extensions) const {
        m_context_info.print(print_glsl_versions, print_extensions);
    }

    void ContextGLFW::get_context_info() {
        glGetIntegerv(GL_MAJOR_VERSION, &m_context_info.major_version);
        glGetIntegerv(GL_MINOR_VERSION, &m_context_info.minor_version);

        m_context_info.vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
        m_context_info.renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
        m_context_info.shading_language_version =
            reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));

        GLint number_of_extensions = 0;
        glGetIntegerv(GL_NUM_EXTENSIONS, &number_of_extensions);
        for (int i = 0; i < number_of_extensions; ++i) {
            m_context_info.supported_extensions.push_back(
                reinterpret_cast<const char*>(glGetStringi(GL_EXTENSIONS, i)));
        }

        GLint number_of_supported_glsl_versions = 0;
        glGetIntegerv(GL_NUM_SHADING_LANGUAGE_VERSIONS, &number_of_supported_glsl_versions);
        for (int i = 0; i < number_of_supported_glsl_versions; ++i) {
            m_context_info.supported_GLSL_versions.push_back(
                reinterpret_cast<const char*>(glGetStringi(GL_SHADING_LANGUAGE_VERSION, i)));
        }
    }
} // namespace ogl
