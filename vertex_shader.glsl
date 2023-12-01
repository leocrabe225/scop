#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 triangleVector1;

uniform mat4 proj;
out vec3 triangleVector;

void main()
{
    gl_Position = proj * vec4(aPos, 1.0);
    triangleVector = vec3(triangleVector1);
}