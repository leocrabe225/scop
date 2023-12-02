#version 430 core

in vec4 triangleVector;
out vec4 FragColor;
uniform vec4 ourColor;

//in float mygl_VertexID2;

void main() {
    // int mygl_VertexID = int(mygl_VertexID2);
    // int modulo = 4;
    //FragColor = vec4(triangleVector.xyz, 1.0f);
    //FragColor = vec4(float(gl_VertexID % 256) / 255.0f, float(gl_VertexID % 256) / 255.0f, float(gl_VertexID % 256) / 255.0f, 1.0f);
    //FragColor = vec4(float(mygl_VertexID % modulo) * (256 / modulo) / 255.0f, float(mygl_VertexID % modulo) * (256 / modulo)  / 255.0f, float(mygl_VertexID % modulo) * (256 / modulo) / 255.0f, 1.0f);
    // if (mygl_VertexID % 5 == 0) {
    //     FragColor = vec4(96.0f / 255.0f, 68.0f/ 255.0f, 57.0f / 255.0f, 1.0f);
    // }
    // else if (mygl_VertexID % 5 == 1) {
    //     FragColor = vec4(158.0f / 255.0f,154.0f / 255.0f,117.0f / 255.0f, 1.0f);
    // }
    // else if (mygl_VertexID % 5 == 2) {
    //     FragColor = vec4(28.0f / 255.0f,34.0f / 255.0f,46.0f / 255.0f, 1.0f);
    // }
    // else if (mygl_VertexID % 5 == 3) {
    //     FragColor = vec4(65.0f / 255.0f,83.0f / 255.0f,59.0f / 255.0f, 1.0f);
    // }
    // else if (mygl_VertexID % 5 == 4) {
    //     FragColor = vec4(85.0f / 255.0f,72.0f / 255.0f,64.0f / 255.0f, 1.0f);
    // }
    FragColor = triangleVector;
}