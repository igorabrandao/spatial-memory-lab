#version 330 core

// Input color
in vec3 ourColor;

// Output color
out vec4 FragColor;

// Main function
void main() {
    // Set the output color
    FragColor = vec4(ourColor, 1.0);
}