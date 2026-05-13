#version 330 core

// Input position
layout (location = 0) in vec3 aPos;

// Input color
layout (location = 1) in vec3 aColor;

// Output color
out vec3 ourColor;

// MVP matrix (Model-View-Projection)
uniform mat4 MVP;

// Main function
void main() {
    gl_Position = MVP * vec4(aPos, 1.0);
    ourColor = aColor;
}