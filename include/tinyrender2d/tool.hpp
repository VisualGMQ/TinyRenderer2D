#ifndef TOOL_HPP
#define TOOL_HPP

#include <string>
#include <fstream>
#include <streambuf>
#include <exception>

using std::string;

static string ReadShaderFile(string filename) {
    std::ifstream ifile(filename);
    if (ifile.fail()) {
        throw std::runtime_error("shader " + filename + " not exists");
    }
    string content((std::istreambuf_iterator<char>(ifile)), std::istreambuf_iterator<char>());
    ifile.close();
    return content;
}

namespace tinyrender2d {

enum FlipType {
    FLIP_NONE = 0x00,
    FLIP_VERTICAL = 0x01,
    FLIP_HORIZONTAL = 0x02,
    FLIP_BOTH = FLIP_VERTICAL|FLIP_HORIZONTAL
};

};

#endif
