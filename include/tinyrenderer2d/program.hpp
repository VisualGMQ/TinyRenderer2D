#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <string>

#include "shader.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace tinyrenderer2d {

using std::string;

class Program final {
 public:
    Program(Shader& vertex_shader, Shader& frag_shader);
    GLuint GetProgram() const {
        return program_;
    } 

    void UniformMat4f(const string& name, const glm::mat4& value);
    void UniformVec4f(const string& name, const glm::vec4& value);
    void UniformVec4i(const string& name, const glm::dvec4& value);
    void Uniform1i(const string& name, int value);
    void Uniform3f(const string& name, float value1, float value2, float value3);

    ~Program();

 private:
    GLuint program_;

    GLint findUniformLocation(const string& name);
};

}; // NAMESPACE tinyrender2d

#endif
