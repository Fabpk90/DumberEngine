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
	float xstep = 1.0 / screen_width;
	float ystep = 1.0 / screen_height;
	float ratio = screen_width / screen_height;

	vec4 color = texture2D( TexColor , uv );

	vec2 offsets[9] = vec2[](
		vec2(-offset,  offset), // top-left
		vec2( 0.0f,    offset), // top-center
		vec2( offset,  offset), // top-right
		vec2(-offset,  0.0f),   // center-left
		vec2( 0.0f,    0.0f),   // center-center
		vec2( offset,  0.0f),   // center-right
		vec2(-offset, -offset), // bottom-left
		vec2( 0.0f,   -offset), // bottom-center
		vec2( offset, -offset)  // bottom-right
	);

	//sobel filter

	vec4 val = vec4(0);
	for(int i = 0; i < 9; ++i)
	{
		val += texture(TexColor, uv + offsets[i]);
	}

	val /= 9;

	//Gamma correction
	val.r = pow(val.r,1.0/2.2);
	val.g = pow(val.g,1.0/2.2);
	val.b = pow(val.b,1.0/2.2);

	color_out = val;
}