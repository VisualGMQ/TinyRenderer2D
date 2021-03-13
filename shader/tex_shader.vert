#version 330 core
layout (location = 0) in vec4 aPos;

uniform mat4 proj;
uniform mat4 model;

out vec2 TexCoord;

void main()
{
    gl_Position = proj*model*vec4(aPos.xy, 0, 1.0);
    TexCoord = aPos.zw;
}
