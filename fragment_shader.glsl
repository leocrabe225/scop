#version 460 core

in vec2 TexCoord;
in vec4 triangleVector;

out vec4 FragColor;

uniform sampler2D ourTexture;

void main() {
    FragColor = texture(ourTexture, TexCoord);
}