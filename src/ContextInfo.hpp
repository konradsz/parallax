#pragma once

#include <iostream>
#include <vector>
#include <string>

namespace ogl {
    struct ContextInfo {
        GLint major_version;
        GLint minor_version;
        std::string shading_language_version;

        std::string vendor;
        std::string renderer;
        std::vector<std::string> supported_extensions;
        std::vector<std::string> supported_GLSL_versions;

        void print(bool print_glsl_versions = false, bool print_extensions = false) const {
            std::cout << "OpenGL version: " << major_version << "." << minor_version << "\n";
            std::cout << "GLSL version: " << shading_language_version << "\n";
            std::cout << "Vendor: " << vendor << "\n";
            std::cout << "Renderer: " << renderer << "\n";

            if (print_glsl_versions) {
                std::cout << "Supported GLSL Versions: " << "\n";
                for (const auto& version : supported_GLSL_versions) {
                    std::cout << "GLSL " << version << "\n";
                }
            }

            if (print_extensions) {
                std::cout << "Supported extensions: " << "\n";
                for (const auto& extension : supported_extensions) {
                    std::cout << "Extension: " << extension << "\n";
                }
            }
        }
    };
} // namespace ogl
