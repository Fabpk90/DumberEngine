#version 400
in vec4 fragPos;

uniform vec3 lightPos;
uniform float farPlane;

void main (void)
{
    float lightDistance = length(fragPos.xyz - lightPos);

    //[0,1]
    lightDistance = lightDistance / farPlane;

    gl_FragDepth = lightDistance;
}