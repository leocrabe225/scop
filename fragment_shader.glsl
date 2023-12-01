#version 430 core

in vec3 triangleVector;
out vec4 FragColor;
uniform vec4 ourColor;

void main() {
    FragColor = vec4(triangleVector.xyz, 1.0f);
}