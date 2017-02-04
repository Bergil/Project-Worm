#version 430 core
uniform vec4 color;
uniform vec3 lightDir;

in vec3 normale;
in vec3 position;
out vec4 colorOut;

void main(){

	colorOut.rgb = position;
	//colorOut.rgb = color.rgb * clamp(dot(normale, lightDir), 0.2, 1.0);
	colorOut.a = color.a;
	
}