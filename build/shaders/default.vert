#version 330

layout (location = 0) in vec3 locPos;
layout (location = 1) in vec3 locNormal;
layout (location = 2) in vec2 locUV;

uniform mat4 m4Transform;

out vec3 sNormal;
out vec2 sUV;

void main()
{
    gl_Position = m4Transform * vec4( locPos, 1.0f );
    sNormal = locNormal;
    sUV = locUV;
}