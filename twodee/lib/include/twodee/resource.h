//
// Created by Kevin Ward on 5/7/17.
//

#ifndef TWODEE_RESOURCE_H
#define TWODEE_RESOURCE_H

#include <unordered_map>
#include <string>
#include <vector>
#include <stdexcept>
#include <twodee/shader.h>


namespace twodee {

using namespace std;

/**
 * @brief Loader for objects that are created using data from files.
 *
 * Resources are created with a string argument, the base file path.
 * This should be the path to a directory containing the files to laod
 * resources from.
 *
 * Supported resource types are:
 *   + shaders
 */
class Resource {

private:
    unordered_map<string, string> _text_cache;
    string _base_path;

public:
    Resource(const std::string & base_path);

    string read_text_file(const string file_name);

    Shader load_shader(const string & vertex_shader_path, const string & fragment_shader_path);

    class FileNotFoundError : public runtime_error {
        using runtime_error::runtime_error;
    };

    class ShaderFileLoadError : public runtime_error {
        using runtime_error::runtime_error;
    };
};

};

#endif //TWODEE_RESOURCE_H
