//
// Created by Kevin Ward on 5/6/17.
//

#include "shader.h"
#include <iostream>
#include <fstream>
#include <common.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

namespace twodee {

string read_shader_error(GLuint shader)
{
    GLint msg_length = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &msg_length);

    string msg(msg_length, '\0');

    glGetShaderInfoLog(shader, msg_length, nullptr, &msg[0]);

    return msg;
}

string read_program_error(GLuint program)
{
    GLint msg_length = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &msg_length);

    string msg(msg_length, '\0');

    glGetProgramInfoLog(program, msg_length, nullptr, &msg[0]);

    return msg;
}

GLuint compile_shader(const string & source)
{
    GLuint shader_handle = glCreateShader(GL_VERTEX_SHADER);

    {
        const char *vs_cs = source.c_str();
        glShaderSource(shader_handle, 1, &vs_cs, nullptr);
    }

    glCompileShader(shader_handle);

    int success = 0;
    glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE) {
        string reason = read_shader_error(shader_handle);
        glDeleteShader(shader_handle);

        throw Error(reason);
    }

    return 0;
}

Shader::Shader(const string vs, const string fs) :
        vertex_source_(vs), fragment_source_(fs)
{
    const auto vso = compile_shader(vs);
    const auto fso = compile_shader(fs);

    const auto p = glCreateProgram();

    glAttachShader(p, vso);
    glAttachShader(p, fso);
    glLinkProgram(p);

    int success;
    glGetProgramiv(p, GL_LINK_STATUS, &success);

    if (success == GL_FALSE) {
        string reason = read_program_error(p);
        glDeleteProgram(p);

        throw Error(reason);
    }

    program_ = p;

    glDeleteShader(vso);
    glDeleteShader(fso);
}


Shader::Shader(Shader && other) :
        vertex_source_(std::move(other.vertex_source_)),
        fragment_source_(std::move(other.fragment_source_)),
        program_(other.program_)
{
    other.program_ = 0;
}


const std::string & Shader::vertex_source()
{
    return vertex_source_;
}

const std::string & Shader::fragment_source()
{
    return fragment_source_;
}

Shader::~Shader()
{
    if (program_) {
        glDeleteProgram(program_);
        program_ = 0;
    }
}

Shader Shader::load_files(const std::string vs_path, const std::string fs_path)
{
    ifstream vs_file(vs_path);

    if (!vs_file.is_open()) {
        throw Error("Cannot open vertex shader file at path " + vs_path);
    }

    ifstream fs_file(fs_path);

    if (!fs_file.is_open()) {
        throw Error("Cannot open fragment shader file at path " + fs_path);
    }

    string vertex_source;
    string fragment_source;

    while (getline(vs_file, vertex_source)) { };
    while (getline(vs_file, fragment_source)) { };

    cout << vertex_source;
    cout << fragment_source;

    return Shader(vertex_source, fragment_source);
}

}