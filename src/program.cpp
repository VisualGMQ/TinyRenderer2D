#include "tinyrenderer2d/program.hpp"

namespace tinyrenderer2d {

Program::Program(Shader& vertex_shader, Shader& frag_shader) {
    program_ = glCreateProgram(); 
    glAttachShader(program_, vertex_shader.GetShaderBuffer());
    glAttachShader(program_, frag_shader.GetShaderBuffer());
    glLinkProgram(program_);
    int success;
    glGetProgramiv(program_, GL_LINK_STATUS, &success);
    if (!success) {
        char buf[1024] = {0};
        glGetProgramInfoLog(program_, sizeof(buf)-1, nullptr, buf);
        std::cout << "program link error:" << std::endl;
        std::cout << buf << std::endl;
        throw std::runtime_error("program linkded failed");
    }
}

void Program::UniformMat4f(const string& name, const glm::mat4& value) {
    GLuint loc = findUniformLocation(name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

void Program::UniformVec4f(const string& name, const glm::vec4& value) {
    GLuint loc = findUniformLocation(name);
    glUniform4f(loc, value.x, value.y, value.z, value.w);
}

void Program::UniformVec4i(const string& name, const glm::dvec4& value) {
    GLuint loc = findUniformLocation(name);
    glUniform4i(loc, value.x, value.y, value.z, value.w);
}

void Program::Uniform1i(const string& name, int value) {
    GLuint loc = findUniformLocation(name);
    glUniform1i(loc, value);
}

void Program::Uniform3f(const string& name, float value1, float value2, float value3) {
    GLuint loc = findUniformLocation(name);
    glUniform3f(loc, value1, value2, value3);
}

GLint Program::findUniformLocation(const string& name) {
    GLint loc = glGetUniformLocation(program_, name.c_str());
    if (loc == -1) {
        std::cerr << name + " uniform variable not found" << std::endl;
    }
    return loc;
}

Program::~Program() {
    glDeleteProgram(program_);
}

};
