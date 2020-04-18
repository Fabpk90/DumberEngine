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

const float offset = 1.0 / 200.0;

const mat3 kernelX
= mat3
(1.0f, 0.0f, -1.0f,
2.0f, 0.0f, -2.0f,
1.0f, 0.0f, -1.0f);

const mat3 kernelY
= mat3
(1.0f, 2.0f, 1.0f,
0.0f, 0.0f, 0.0f,
-1.0f, -2.0f, -1.0f);

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
	float depth = texture2D( TexDepth , uv ).r;
	
	//Permet de scaler la profondeur
	depth = LinearizeDepth(depth);

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

	vec3 sampleTex[9];
	for(int i = 0; i < 9; ++i)
	{
		sampleTex[i] = vec3(texture(TexColor, uv + offsets[i]));
	}

	float gx = dot(kernelX[0], sampleTex[0]) + dot(kernelX[1], sampleTex[1]) + dot(kernelX[2], sampleTex[2]);
	float gy = dot(kernelY[0], sampleTex[0]) + dot(kernelY[1], sampleTex[1]) + dot(kernelY[2], sampleTex[2]);

	float g = sqrt(gx * gx + gy * gy);

	//Gamma correction
	color.r = pow(color.r,1.0/2.2);
	color.g = pow(color.g,1.0/2.2);
	color.b = pow(color.b,1.0/2.2);

	vec3 edgeColor = vec3(0.0, 0.0, 1.0);

	color_out = color * (g * vec4(edgeColor, 1.0f));
}