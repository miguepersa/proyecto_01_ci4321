#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 camMatrix;
uniform float lightMovement;

void main()
{
	vec4 pos = vec4(lightMovement, 0.0f, lightMovement, 0.0f);
	gl_Position = (camMatrix * model * vec4(aPos, 1.0f)) + pos;
}