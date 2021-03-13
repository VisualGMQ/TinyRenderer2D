#version 330 core

in vec4 fragColor256;
out vec4 outColor;

void main() {
    outColor = vec4(fragColor256.r/255.0, fragColor256.g/255.0, fragColor256.b/255.0, fragColor256.a/255.0);
}
