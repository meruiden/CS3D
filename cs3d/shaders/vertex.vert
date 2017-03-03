#version 330 core

// Input vertex data, different for all executions of this shader.
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;


// Output data ; will be interpolated for each fragment.
out vec2 UV;
out vec3 normalModelSpace;
out vec3 FragPos;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 model;



void main(){

	gl_Position =  MVP * vec4(position,1.0);
	
	FragPos = (model * vec4(position, 1.0)).xyz;
    normalModelSpace = (model * vec4(normal, 0.0)).xyz;
	UV = texCoords;
}

