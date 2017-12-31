#version 400 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec4 inColour;
layout (location = 2) in vec2 inUVs;

void main()
{
	gl_Position = vec4(inPos, 1.0f);
}