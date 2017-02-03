#version 430 core

in vec3 normale;
in vec3 position;
out vec4 colorOut;

void main(){

	//colorOut = vec4(position, 1.0);
	colorOut.rgb = vec3(1, 0, 0) * clamp(dot(normale, vec3(1.0,0.0,0.0)), 0.2, 1.0);
	colorOut.a = 1.0;
	
}