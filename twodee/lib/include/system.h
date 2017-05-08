//
// Created by Kevin Ward on 5/6/17.
//

#ifndef TWODEE_SYSTEM_H
#define TWODEE_SYSTEM_H

#include <GLFW/glfw3.h>

namespace twodee {

/*
 * Object that bootstraps the application's libraries and contexts/managers
 */
class System {

private:
    GLFWwindow *window_;

public:
    System();
    ~System();
    void init();
    GLFWwindow *window();

};
};

#endif //TWODEE_SYSTEM_H
