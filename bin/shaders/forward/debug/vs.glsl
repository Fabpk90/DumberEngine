#version 330 core

layout(location = 0) in vec3 vs_position;

uniform mat4 v;
uniform mat4 p;

uniform vec3 color;

out vec3 col;

void main()
{
    gl_Position = p * v * vec4(vs_position, 1.0);

    col = color;
}
