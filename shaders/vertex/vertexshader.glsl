#version 430 core

uniform mat4 perspective;
uniform mat4 camera;
uniform mat4 model;

in vec3 vertexPosition;
in vec3 vertexNormale;
in vec2 vertexTexcoord;
out vec3 normale;
out vec3 position;
void main(){
	gl_Position = perspective*camera*model*vec4(vertexPosition, 1.0);
	normale = vertexNormale;
	position = vertexPosition;
	
}