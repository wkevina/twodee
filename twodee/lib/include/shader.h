//
// Created by Kevin Ward on 5/6/17.
//

#ifndef TWODEE_SHADER_H
#define TWODEE_SHADER_H

#include <string>
#include <GLFW/glfw3.h>

namespace twodee {

class Shader {
    std::string vertex_source_;
    std::string fragment_source_;

private:
    GLuint program_;

public:
    Shader(const std::string &&vs, const std::string &&fs);
    const std::string &vertex_source();
    const std::string &fragment_source();
};
};

#endif //TWODEE_SHADER_H
