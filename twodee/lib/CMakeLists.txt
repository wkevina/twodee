project(lib LANGUAGES CXX)

add_library(twodee src/twodee_renderer.cpp src/system.cpp include/twodee/system.h include/twodee/twodee.h src/renderer.cpp include/twodee/renderer.h src/shader.cpp include/twodee/shader.h src/resource.cpp include/twodee/resource.h include/twodee/particle_effects.h src/particle_effects.cpp)

target_link_libraries(twodee
        glfw
        GLEW::GLEW
        ${OPENGL_gl_LIBRARY})

target_include_directories(twodee
        PUBLIC
        include
        ${GLEW_INCLUDE_DIRS}
        ${VENDOR_INCLUDE_DIRECTORIES}
        ${OPENGL_INCLUDE_DIR})
