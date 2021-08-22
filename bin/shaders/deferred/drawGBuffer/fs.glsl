#version 330 core

uniform sampler2D t_albedoSpec;

in vec2 uv;

out vec4 color;

void main()
{
    color = texture2D(t_albedoSpec, uv);
}
