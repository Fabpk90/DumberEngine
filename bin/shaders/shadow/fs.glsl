#version 400

void main (void)
{
    gl_FragColor = vec4(gl_FragCoord.z);
}