#version 330 core
out vec4 FragColor;

uniform float ourColor;

void main()
{
    FragColor = vec4(ourColor, ourColor, ourColor, 1.0);
} 