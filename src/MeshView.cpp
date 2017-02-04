#include "MeshView.hpp"
#include <glm/gtc/type_ptr.hpp>

void MeshView::draw(const sf::Shader &s) const{
	glUniformMatrix4fv(glGetUniformLocation(s.getNativeHandle() ,  "model"), 1, false, glm::value_ptr(matriceModel));
	glUniform4fv(glGetUniformLocation(s.getNativeHandle() ,  "color"), 1, glm::value_ptr(color));
	mesh->draw();
	
}

void MeshView::draw(const sf::Shader &s, const glm::mat4 &mat) const{
	glUniformMatrix4fv(glGetUniformLocation(s.getNativeHandle() ,  "model"), 1, false, glm::value_ptr(matriceModel*mat));
	glUniform4fv(glGetUniformLocation(s.getNativeHandle() ,  "color"), 1, glm::value_ptr(color));
	mesh->draw();
	
}