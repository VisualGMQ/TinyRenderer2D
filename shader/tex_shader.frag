#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D Texture;
uniform vec3 TextureColor256;

void main() {
    vec4 texture_color = vec4(TextureColor256.r/255.0, TextureColor256.g/255.0, TextureColor256.b/255.0, 1.0);
    FragColor = texture_color*texture(Texture, TexCoord);
} 
