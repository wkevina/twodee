//
// Created by Kevin Ward on 5/6/17.
//

#ifndef TWODEE_SHADER_H
#define TWODEE_SHADER_H

#include <string>
#include "twodee/gl.h"

namespace twodee {

class Shader {
    std::string vertex_source_;
    std::string fragment_source_;

private:
    Shader(const Shader &other) = delete;
    Shader& operator=(const Shader& other) = delete;

    GLuint _program;
    bool _activated;

public:
    Shader(const std::string vs, const std::string fs);
    Shader(Shader && other);
    ~Shader();
    const std::string &vertex_source();
    const std::string &fragment_source();
    void activate();
    void deactivate();
    void validate();

    static Shader load_files(const std::string vs_path, const std::string fs_path);
};
};

#endif //TWODEE_SHADER_H
