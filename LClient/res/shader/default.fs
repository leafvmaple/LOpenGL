#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D slTexture01;
uniform sampler2D slTexture02;

void main()
{
    FragColor = mix(texture(slTexture01, TexCoord), texture(slTexture02, TexCoord), 0.2);
}