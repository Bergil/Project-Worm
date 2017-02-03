in vec3 normale;
in vec3 position;
out vec4 colorOut;

void main(){

	colorOut = vec4(position, 1.0);
	//colorOut = vec4(1, 0, 0, 1) * min(dot(normale, vec3(1.0,0.0,0.0)), 0.5);
	
}