//
// Created by Kevin Ward on 5/6/17.
//

#include "twodee/shader.h"
#include <iostream>
#include <fstream>
#include <twodee/common.h>
#include <vector>


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

GLuint compile_shader(const string & source, const GLenum type)
{
    GLuint shader_handle = glCreateShader(type);

    const char *vs_cs = source.c_str();
    glShaderSource(shader_handle, 1, &vs_cs, nullptr);

    glCompileShader(shader_handle);

    int success = 0;
    glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE) {
        string reason = read_shader_error(shader_handle);
        glDeleteShader(shader_handle);

        throw Error(reason);
    }

    return shader_handle;
}

Shader::Shader(const string vs, const string fs) :
        vertex_source_(vs), fragment_source_(fs)
{
    const auto vso = compile_shader(vs, GL_VERTEX_SHADER);
    const auto fso = compile_shader(fs, GL_FRAGMENT_SHADER);

    const auto p = glCreateProgram();

    glAttachShader(p, vso);
    glAttachShader(p, fso);

    glLinkProgram(p);

    // check link errors

    int success;
    glGetProgramiv(p, GL_LINK_STATUS, &success);

    if (success == GL_FALSE) {
        string reason = read_program_error(p);
        glDeleteProgram(p);

        throw Error(reason);
    }

    _program = p;

    glDeleteShader(vso);
    glDeleteShader(fso);
}

Shader::Shader(Shader && other) :
        vertex_source_(std::move(other.vertex_source_)),
        fragment_source_(std::move(other.fragment_source_)),
        _program(other._program)
{
    other._program = 0;
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
    if (_program) {
        deactivate();
        glDeleteProgram(_program);
        _program = 0;
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

    while (getline(vs_file, vertex_source)) {};
    while (getline(vs_file, fragment_source)) {};

    cout << vertex_source;
    cout << fragment_source;

    return Shader(vertex_source, fragment_source);
}

void Shader::activate()
{
    glUseProgram(_program);
    _activated = true;
}

void Shader::deactivate()
{
    if (_activated) {
        glUseProgram(0);
        _activated = false;
    }
}

void Shader::validate()
{
    glValidateProgram(_program);

    // check validation errors
    int success;
    glGetProgramiv(_program, GL_VALIDATE_STATUS, &success);

    if (success == GL_FALSE) {
        string reason = read_program_error(_program);
        glDeleteProgram(_program);

        throw Error(reason);
    }
}

}
