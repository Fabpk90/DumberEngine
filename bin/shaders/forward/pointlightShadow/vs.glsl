#version 400

layout(location=0) in vec3 vs_position_in;

uniform mat4 model;

void main()
{
	gl_Position = model * vec4(vs_position_in, 1.0f);
}