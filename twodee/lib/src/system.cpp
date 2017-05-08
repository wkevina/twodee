//
// Created by Kevin Ward on 5/6/17.
//

#include "System.h"
#include <iostream>
#include <cstdlib>


GLFWwindow *twodee::System::init() {
    // Initialize glfw
    glfwInit();


    // Configure context creation
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Platform specific configuration
#if __APPLE__

#include "TargetConditionals.h"

#if TARGET_OS_MAC
    // Required on macOS or else window/context creation will fail
//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
#endif

    GLFWwindow *window = glfwCreateWindow(640, 480, "twodee demo", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    this->mp_window = window;

    return window;
}
