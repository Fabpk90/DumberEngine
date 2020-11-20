#version 330 core

#define PI 3.1415926538

in vec3 worldPos;
in vec3 normal;
in vec2 uv;

out vec4 color;

uniform vec3 cameraPos;

uniform vec3 albedo;
uniform float metallic;
uniform float roughness;
uniform float ao;

uniform vec3 lightPos;
uniform vec3 lightColor;

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1 - F0) * pow(1 - cosTheta, 5);
}

float distributionGGX(vec3 normal, vec3 halfVector, float roughness)
{
    //roughness in the equation
    float a = roughness * roughness; //looks better that way according to Disney and Epic
    float a2 = a * a;

    float NdotH = max(dot(normal, halfVector), 0.0);
    float NdotH2 = NdotH * NdotH;

    float denom = (NdotH2 * (a2 - 1) + 1);
    denom = PI * (denom * denom);

    return a2 / denom;
}

void main() {

    vec3 N = normalize(normal);
    vec3 view = normalize(cameraPos - worldPos);

    vec3 Lo = vec3(0);
    for(int i = 0; i < 1; i++)
    {
        vec3 lightDir = normalize(lightPos - worldPos);
        vec3 halfVector = normalize(view + lightDir);

        float distance = length(lightPos - worldPos);
        float attenuation = 1.0 / (distance * distance); //inv quadratic attenuation
        vec3 radiance = lightColor * attenuation;

        //avg for dieletric mat
        vec3 F0 = vec3(0.04);
        F0 = mix(F0, albedo, metallic); //how much metallic the material is

        vec3 F = fresnelSchlick(max(dot(halfVector, view), 0.0), F0);
    }

    Lo /= 1;

    color = vec4(1, 0, 0, 1);

}
