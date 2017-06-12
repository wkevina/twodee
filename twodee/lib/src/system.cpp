//
// Created by Kevin Ward on 5/6/17.
//

#include "twodee/system.h"
#include "twodee/common.h"
#include "twodee/gl.h"

#include <iostream>

namespace twodee {

System::System() : window_(nullptr) { };

void System::init()
{
    // Initialize glfw
    glfwInit();

    // Configure context creation
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // Platform specific configuration
    #if __APPLE__

        #include "TargetConditionals.h"

        #if TARGET_OS_MAC
    // Required on macOS or else window/context creation will fail
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif
    #endif

    auto window = glfwCreateWindow(640, 480, "twodee demo", nullptr, nullptr);

    if (window == nullptr) {
        throw Error("Failed to create window");
    }

    window_ = window;

    glfwSetWindowAspectRatio(window_, 4, 3);

    int width, height;
    glfwGetFramebufferSize(window_, &width, &height);

    glViewport(0, 0, width, height);

    GLenum err = glewInit();
    if (GLEW_OK != err)
      {
	/* Problem: glewInit failed, something is seriously wrong. */
	throw Error("Failed to initialize GLEW");

      }
    std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
}

GLFWwindow *System::window()
{
    return window_;
}

System::~System()
{
    if (window_) {
        glfwDestroyWindow(window_);
        window_ = nullptr;
    }

    glfwTerminate();
}

}
