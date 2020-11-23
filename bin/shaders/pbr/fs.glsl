#version 330 core

#define PI 3.1415926538

in vec3 worldPos;
in vec3 normal;
in vec2 uv;

out vec4 color;

uniform vec3 cameraPos;

uniform sampler2D t_albedo;
uniform sampler2D t_metallic;
uniform sampler2D t_roughness;
uniform sampler2D t_ao;

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

float geometrySchlickGGX(float NdotV, float roughness)
{
    float a = roughness + 1;
    float k = (a*a) / 8.0;

    return NdotV / (NdotV * (1.0 - k) + k);
}

float geometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);

    float ggx1 = geometrySchlickGGX(NdotV, roughness);
    float ggx2 = geometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

void main() {

    float roughness = texture(t_roughness, uv).r;
    float metallic = texture(t_metallic, uv).r;
    vec3 albedo = texture(t_albedo, uv).rgb;
    float ao = texture(t_ao, uv).r;

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
        float NDF = distributionGGX(N, halfVector, roughness);
        float G = geometrySmith(N, view, lightDir, roughness);

        vec3 numerator = NDF * F * G;
        float denominator = 4.0f * max(dot(N, view), 0.0) * max(dot(N, lightDir), 0.0);

        vec3 specular = numerator / max(denominator, 0.0001);

        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS; //amount of refracted light

        kD *= 1.0 - metallic;

        float NdotL = max(dot(N, lightDir), 0.0); // n*wi
        Lo += (kD * albedo / PI + specular) * radiance * NdotL;
    }

    vec3 ambient = vec3(0.03) * albedo * ao;
    vec3 pixelColor = ambient + Lo;

    //hdr
    pixelColor = pixelColor / (pixelColor + vec3(1.0));
    pixelColor = pow(pixelColor, vec3(1.0/2.2));

    color = vec4(pixelColor, 1.0);

}
