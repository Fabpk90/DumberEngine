#version 330 core

layout(location = 0) in vec3 vs_position;


out vec2 uv;
//out vec3 normal;
//out vec3 position;

void main()
{
    gl_Position = vec4(vs_position,1.0);
    uv = (vs_position.xy+vec2(1,1))/2;
}
