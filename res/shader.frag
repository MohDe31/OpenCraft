#version 460 core
out vec4 FragColor;

// in vec3 fColor;
in vec2 fTexCoords;

uniform sampler2D uTexture;
// uniform sampler2D uTexture2;

void main()
{
    FragColor = texture(uTexture, fTexCoords);
} 