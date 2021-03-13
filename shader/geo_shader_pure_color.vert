#version 330 core

layout (location = 0) in vec2 inPos;

uniform mat4 proj;

void main() {
    gl_Position = proj*vec4(inPos, 0, 1);
}
