#version 400

uniform sampler2D shadowTex;
uniform sampler2D worldTex;

uniform float elasped;
uniform vec3 lightDir;
uniform vec3 skyColor;
uniform vec3 sunColor;
uniform float elapsed;

//Variables en entree
in vec3 normal;
in vec4 color;
in vec2 uv;
in vec3 wPos;
in vec3 camPosition;

in vec4 fragPosInLightSpace;

flat in float type;

out vec4 color_out;

//Globales
const float ambientLevel = 0.4;

#define CUBE_EAU 5.0

float waterNoise(vec3 v)
{
	vec2 dir = vec2(v.x, v.z);

	float d = dot(vec2(1, 1), dir);
	float n = (1+sin(d + elapsed)) / 4;

	d = dot(vec2(1, .5), dir);
	n += (1+sin(d + elapsed)) / 2;

	d = dot(vec2(-.5, 1), dir);
	n += (1+ sin(d + elapsed)) / 4;

	return n / 2.75;
}

float ComputeShadow(vec4 fragPosLightSpace)
{
	// perspective divide
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5; // [0, 1]

	float currentDepth = projCoords.z;
	float closestDepth = texture(shadowTex, projCoords.xy).r;

	//out of range, black pixel
	if(projCoords.z > 1.0)
		return 0.0;

	float bias = max(0.05 * (1.0 - dot(normalize(normal), normalize(lightDir))), 0.005);


	//pcf
	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(shadowTex, 0);
	for(int x = -1; x <= 1; ++x)
	{
		for(int y = -1; y <= 1; ++y)
		{
			float pcfDepth = texture(shadowTex, projCoords.xy + vec2(x, y) * texelSize).r;
			shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
		}
	}
	shadow /= 9.0;

	return shadow;
}

void main()
{
	vec4 texColor = texture(worldTex, uv);

	vec3 toLight = normalize(lightDir);
	vec3 view = normalize(camPosition - wPos);
	vec4 c = texColor * color;

	vec3 N = normal;
	N = normalize(N);

	if(type == CUBE_EAU)
	{
		vec3 A = wPos;
		A.y += waterNoise(wPos) - 1;

		vec3 B = wPos + vec3(0.1f, 0, 0);
		B.y += waterNoise(B) - 1;

		vec3 C = wPos + vec3(0, 0.1f, 0);
		C.y += waterNoise(C) - 1;

		N = cross( normalize(B-A), normalize(C-A));

		float fresnel = max(0, dot(N, view));
		c.a = 1-fresnel;

		c.rgb = mix(c.rgb, skyColor.rgb, pow((1 - fresnel), 50));
	}

	float diffuse = max(0.005f, dot(toLight, N));
	float shadow = ComputeShadow(fragPosInLightSpace);
	//Spec
	if(type == CUBE_EAU){
		vec3 halfVec = normalize(toLight + view);
		float spec = abs(dot(N, halfVec));
		vec3 specular = pow(spec, 300) * skyColor;

		c.rgb *= (skyColor * (1 - shadow) * (diffuse + specular) )* texColor.rgb;
	}

	//Ambient
	c.rgb *= vec3(1 - shadow) * diffuse;

	color_out = sqrt(c);
}