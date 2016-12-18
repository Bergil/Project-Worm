uniform mat4 perspective;
uniform mat4 camera;

in vec3 vertexPosition;
in vec3 vertexNormale;
in vec2 vertexTexcoord;
out vec3 normale;
void main(){
	vec4 tmpPosition = vec4(vertexPosition, 1);
	gl_Position = perspective*camera*tmpPosition;
	normale = vertexNormale;
	
}