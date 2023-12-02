#version 430 core

layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 triangleVector1;

uniform mat4 proj;
out vec4 triangleVector;

out float mygl_VertexID2;

void main()
{
    gl_Position = proj * vec4(aPos, 1.0);
    //mygl_VertexID2 = float(gl_VertexID);
    if (gl_VertexID % 5 == 0) {
        triangleVector = vec4(96.0f / 255.0f, 68.0f/ 255.0f, 57.0f / 255.0f, 1.0f);
    }
    else if (gl_VertexID % 5 == 1) {
        triangleVector = vec4(158.0f / 255.0f,154.0f / 255.0f,117.0f / 255.0f, 1.0f);
    }
    else if (gl_VertexID % 5 == 2) {
        triangleVector = vec4(28.0f / 255.0f,34.0f / 255.0f,46.0f / 255.0f, 1.0f);
    }
    else if (gl_VertexID % 5 == 3) {
        triangleVector = vec4(65.0f / 255.0f,83.0f / 255.0f,59.0f / 255.0f, 1.0f);
    }
    else if (gl_VertexID % 5 == 4) {
        triangleVector = vec4(85.0f / 255.0f,72.0f / 255.0f,64.0f / 255.0f, 1.0f);
    }
}