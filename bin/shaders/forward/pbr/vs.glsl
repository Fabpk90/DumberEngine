#version 330 core

layout(location = 0) in vec3 vs_position;
layout(location = 1) in vec3 vs_normal;
layout(location = 2) in vec2 vs_uv;

uniform mat4 m;
uniform mat4 v;
uniform mat4 p;

out vec2 uv;
out vec3 worldPos;

void main()
{
    worldPos = vec3(m * vec4(vs_position, 1.0));
    uv = vs_uv;

    gl_Position = p * v * vec4(worldPos, 1.0);
}
