project(lib LANGUAGES CXX)

add_library(twodee_renderer src/twodee_renderer.cpp src/system.cpp include/system.h include/twodee.h src/renderer.cpp include/renderer.h src/shader.cpp include/shader.h src/resource.cpp include/resource.h include/particle_effects.h src/particle_effects.cpp)

target_link_libraries(twodee_renderer
        glm
        glfw
        GLEW::GLEW
        ${OPENGL_gl_LIBRARY})

target_include_directories(twodee_renderer
        PUBLIC
        include
        ${GLEW_INCLUDE_DIRS})
