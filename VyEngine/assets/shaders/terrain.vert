#version 330 core

in vec3 aPos;

uniform mat4 MVP;

out vec4 Color;

void main()
{
    gl_Position = MVP * vec4(aPos, 1.0);

    Color = vec4(aPos.y / 200.0);
}