#version 330 core

in vec2 uv;

uniform sampler2D TexColor;
uniform sampler2D TexDepth;

layout(std140) uniform globalPPParameters
{
	float screen_width;
	float screen_height;
	vec2 near_far;
};

out vec4 color_out;

const float offset = 1.0 / 300.0;

float LinearizeDepth(float z)
{
	float n = near_far.x; // camera z near
  	float f = near_far.y; // camera z far
  	return (2.0 * n) / (f + n - z * (f - n));
}

void main (void)
{
	vec4 val = texture2D(TexColor, uv);

	//Gamma correction
	val.r = pow(val.r,1.0/2.2);
	val.g = pow(val.g,1.0/2.2);
	val.b = pow(val.b,1.0/2.2);

	color_out = val;
}