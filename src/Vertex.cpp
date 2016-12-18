#include "Vertex.hpp"

Vertex::Vertex(const Vertex &v){
	position = v.position;
	normale = v.normale;
	
}

glm::vec3 Vertex::getPosition(){
	return position;
}

glm::vec3 Vertex::getNormale(){
	return normale;
}

glm::vec2 Vertex::getTexcoord(){
	return texcoord;
}

void Vertex::changePosition(glm::vec3 p){
	position = p;
}

void Vertex::changeNormale(glm::vec3 n){
	normale= n;
}

void Vertex::changeTexcoord(glm::vec2 t){
	texcoord= t;
}