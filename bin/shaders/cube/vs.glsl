#version 330 core

layout(location = 0) in vec3 vs_position;
layout(location = 1) in vec3 vs_normal;
layout(location = 2) in vec2 vs_uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 uv;

void main()
{
    gl_Position = projection * view * (model) * vec4(vs_position, 1.0);

    uv = vs_uv;
}
