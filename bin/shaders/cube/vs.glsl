#version 330 core

layout(location = 0) in vec3 vs_position;
layout(location = 1) in vec3 vs_normal;
layout(location = 2) in vec2 vs_uv;

uniform mat4 m;
uniform mat4 v;
uniform mat4 p;

out vec2 uv;

void main()
{
    gl_Position = p * v * m * vec4(vs_position, 1.0);

    uv = vs_uv;
}
