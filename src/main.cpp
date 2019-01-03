#include "ContextGLFW.hpp"

int main() {
    const GLuint WINDOW_WIDTH = 1280;
    const GLuint WINDOW_HEIGHT = 720;
    ogl::ContextGLFW context(WINDOW_WIDTH, WINDOW_HEIGHT);
    context.print_info();

    context.loop();

    return 0;
}
