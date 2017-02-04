#pragma once
#include <Mesh.hpp>
#include <GL/gl3w.h>
#include <glm/gtc/matrix_transform.hpp> 

class MeshView{
	private :
		const Mesh* mesh;
		
	public : 
		MeshView(const Mesh& m, glm::mat4 v = glm::mat4(1.0)/*identité*/): 
			mesh(&m), 
			matriceModel(v){
		}
		void draw(const sf::Shader &s) const;
		void draw(const sf::Shader &s, const glm::mat4 &mat)const;
		glm::vec4 color;
		glm::mat4 matriceModel;
		
	
		
};