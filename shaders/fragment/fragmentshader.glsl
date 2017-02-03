in vec3 normale;
out vec4 colorOut;

void main(){
	//colorOut = vec4(1, 0, 0, 1);
	colorOut = vec4(1, 0, 0, 1) * dot(normale, vec3(1.0,0.0,0.0));
	
}