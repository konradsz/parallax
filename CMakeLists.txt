cmake_minimum_required(VERSION 3.6)

project(engine)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -pedantic")

file(GLOB_RECURSE src_files ${PROJECT_SOURCE_DIR}/src/*)
add_executable(engine ${src_files})

find_package(OpenGL REQUIRED)
if (OpenGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIRS})
    target_link_libraries(engine ${OPENGL_LIBRARIES})
endif()

find_package(PkgConfig REQUIRED)
if (PkgConfig_FOUND)
    pkg_search_module(GLFW REQUIRED glfw3)
    if (GLFW_FOUND)
        include_directories(${GLFW_INCLUDE_DIRS})
        target_link_libraries(engine ${GLFW_LIBRARIES})
    endif()
endif()

find_package(GLUT REQUIRED)
if (GLUT_FOUND)
    include_directories(${GLUT_INCLUDE_DIRS})
    target_link_libraries(engine ${GLUT_LIBRARY})
endif()

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    target_link_libraries(engine ${GLEW_LIBRARIES})
endif()
