#version 400

uniform float elapsed;
uniform mat4 mvp;
uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
uniform mat4 lightSpaceMatrix;
uniform vec3 camPos;

layout(location=0) in vec3 vs_position_in;
layout(location=1) in vec3 vs_normal_in;
layout(location=2) in vec2 vs_uv_in;
layout(location=3) in float vs_type_in;

//Variables en sortie
out vec3 normal;
out vec4 color;
out vec2 uv;
out vec3 wPos;
out vec3 camPosition;

out vec3 fragPos;

out vec4 fragPosInLightSpace;


flat out float type;

#define CUBE_HERBE 1.0
#define CUBE_TERRE 2.0
#define CUBE_EAU 5.0

float waterNoise(vec4 v)
{
	vec2 dir = vec2(v.x, v.y);

	float d = dot(vec2(1, 1), dir);
	float n = (1+sin(d + elapsed)) / 4;

	d = dot(vec2(1, .5), dir);
	n += (1+sin(d + elapsed)) / 2;

	d = dot(vec2(.5, 1), dir);
	n += (1+ sin(d + elapsed)) / 4;

	return n / 2.75;
}

void main()
{
	vec4 vecIn = vec4(vs_position_in,1.0);
	vec4 vecInW = m * vecIn;

	fragPos = vecInW.xyz;

	//world wave
	//vecInW.y += sin(vecInW.z + elapsed);

	//inception fx
	//vecInW.y += pow(sqrt(pow(camPos.x - vecInW.x, 2) + pow(camPos.y - vecInW.y, 2)), 1.1);

	//planet fx
	//vecInW.y -= pow(sqrt(pow(camPos.x - vecInW.x, 2) + pow(camPos.y - vecInW.y, 2)), 1.1);

	normal = (inverse(transpose(m)) * vec4(vs_normal_in,1.0)).xyz;

	uv = vs_uv_in;

	//Couleur par défaut blanc
	color = vec4(1.0,1.0,1.0,1.0);

	wPos = vecInW.xyz;

	//Couleur fonction du type
	if(vs_type_in == CUBE_HERBE)
	color = vec4(154 / 255,255 / 255,87/255,1);
	else if(vs_type_in == CUBE_TERRE)
	color = vec4(0.2,0.1,0,1);
	else if(vs_type_in == CUBE_EAU)
	{
		color = vec4(0.0,0.0,1.0,0.5);
		vecInW.y -= waterNoise(vecInW);
	}

	type = int(vs_type_in);

	fragPosInLightSpace = lightSpaceMatrix * vecInW;
	camPosition = camPos;

	gl_Position = p * v * vecInW;
}