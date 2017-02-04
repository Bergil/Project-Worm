#pragma once
#include <glm/glm.hpp>

class Vertex{
		
	public:
		glm::vec3 position;
		glm::vec3 normale;
		glm::vec2 texcoord;
		
		Vertex(){}
		Vertex(glm::vec3 p, glm::vec3 n) : position(p), normale(n){}
		Vertex(glm::vec3 p, glm::vec3 n, glm::vec2 t) : position(p), normale(n), texcoord(t){}
		Vertex(const Vertex &v);
		
		glm::vec3 getPosition();
		glm::vec3 getNormale();
		glm::vec2 getTexcoord();
		void changePosition(glm::vec3 p);
		void changeNormale(glm::vec3 n);
		void changeTexcoord(glm::vec2 t);
	
};