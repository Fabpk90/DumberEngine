#version 330 core

layout (location = 0) out vec4 gAlbedoSpec;
layout (location = 1) out vec3 gNormal;


in vec2 uv;
in vec3 normal;
in vec3 position;

uniform sampler2D t_albedo;
uniform sampler2D t_specular;
uniform sampler2D t_normal;

void main()
{
    gNormal = max(normal, texture(t_normal, uv).rgb);

    gAlbedoSpec.rgb = texture(t_albedo, uv).rgb;
    gAlbedoSpec.a = texture(t_specular, uv).r;
}