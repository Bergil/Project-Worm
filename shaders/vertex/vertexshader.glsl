uniform mat4 perspective;
uniform mat4 camera;

in vec3 vertexPosition;
in vec3 vertexNormale;
in vec2 vertexTexcoord;
out vec3 normale;
void main(){
	gl_Position = perspective*camera*vec4(vertexPosition, 1.0);
	normale = vertexNormale;
	
}