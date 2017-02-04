#include "MeshView.hpp"
#include <glm/gtc/type_ptr.hpp>

void MeshView::draw(const sf::Shader &s) const{
	glUniformMatrix4fv(glGetUniformLocation(s.getNativeHandle() ,  "model"), 1, false, glm::value_ptr(matriceModel));
	mesh->draw();
	
}