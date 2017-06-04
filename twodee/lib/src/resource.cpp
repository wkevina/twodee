//
// Created by Kevin Ward on 5/7/17.
//

#include <twodee/common.h>
#include "twodee/resource.h"

#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sstream>


using namespace std;

string slurp(ifstream& in) {
    stringstream sstr;
    sstr << in.rdbuf();
    return sstr.str();
}

twodee::Resource::Resource(const string & base_path)
        : _base_path(base_path)
{

}

string twodee::Resource::read_text_file(const string file_name)
{
    if (_text_cache.find(file_name) != _text_cache.end()) {
        return _text_cache[file_name];
    }

    string cwd(getcwd(nullptr, 0));

    cout << "cwd: " << cwd << endl;

    ifstream file(_base_path + "/" + file_name);

    if (!file.is_open()) {
        throw FileNotFoundError("Cannot open text file");
    }

    string out = slurp(file);

    _text_cache[file_name] = out;

    return out;
}

twodee::Shader twodee::Resource::load_shader(const string & vertex_shader_path, const string & fragment_shader_path)
{
    string vert_src, frag_src;

    try {
        vert_src = read_text_file(vertex_shader_path);
    } catch (FileNotFoundError & e) {
        throw ShaderFileLoadError("Unable to read vertex shader file " + vertex_shader_path);
    }

    try {
        frag_src = read_text_file(fragment_shader_path);
    } catch (FileNotFoundError & e) {
        throw ShaderFileLoadError("Unable to read fragment shader file " + fragment_shader_path);
    }

    return Shader(vert_src, frag_src);
}

//vector<unsigned char> twodee::Resource::read_binary_file(const string file_name)
//{
//    if (_binary_cache.find(file_name) != _binary_cache.end()) {
//        return _binary_cache[file_name];
//    }
//
//    ifstream file(file_name, ios::binary);
//
//    if (!file.is_open()) {
//        throw FileNotFoundError("Cannot open binary file " + file_name);
//    }
//
//    string out;
//
//    while (getline(file, out)) { };
//
//    _binary_cache[file_name] = out;
//
//    return out;
//    return vector<unsigned char>();
//}
