#version 330 core

in vec4 fragColor256;
out vec4 outColor;

void main() {
    outColor = fragColor256/255.0;
}
