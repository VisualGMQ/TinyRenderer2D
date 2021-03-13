#version 330 core

layout (location = 0) in vec2 inPos;
layout (location = 1) in vec4 inColor;

out vec4 fragColor256;

uniform mat4 proj;

void main() {
    fragColor256 = inColor;
    gl_Position = proj*vec4(inPos, 0, 1);
}
