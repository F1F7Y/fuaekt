#version 330

in vec3 sNormal;
in vec2 sUV;

out vec4 outColor;

uniform sampler2D CurrentTexture;


void main()
{
	vec3 v3Sun = vec3(0.6f, 0.4f, 0.9f);
	float diffuse = max( dot( sNormal, v3Sun ), 0.2f );
	vec3 v3Result = diffuse * vec3( texture(CurrentTexture, sUV) );

	outColor = vec4( v3Result, 1.0f );
}