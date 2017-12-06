#version 400 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec4 inColour;
layout (location = 2) in vec2 inUVs;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

out vec4 vertexColour;

void main()
{
	gl_Position = projection * view * transform * vec4(inPos, 1.0f);
	vertexColour = inColour;
}