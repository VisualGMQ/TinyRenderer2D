#version 330 core

out vec4 outColor;

uniform ivec4 fragColor256;

void main() {
    outColor = vec4(fragColor256.r/255.0, fragColor256.g/255.0, fragColor256.b/255.0, fragColor256.a/255.0);
}
