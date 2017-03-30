#version 330 core

// Input vertex data, different for all executions of this shader.
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main(){

	gl_Position =  MVP * vec4(position,1.0);
}

