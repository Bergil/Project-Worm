#pragma once
#include "MeshView.hpp"

class Worm{
	
	public :
		std::vector<MeshView> body;
		glm::vec3 headPosition;
		
		Worm(const Mesh &m){
			headPosition = glm::vec3(0.0, 0.0, 10.0);
			body.emplace_back(m, glm::scale(glm::translate(glm::mat4(1.0f), headPosition), glm::vec3(0.1)));
			body[0].color = glm::vec4(0.0, 1.0, 0.0, 1.0);
		}
		void calculPosition();
		void addBodyPart();
	
	private :
		//std::vector<MeshView> body;
			
	
};