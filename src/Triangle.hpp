#pragma once
#include <glm/glm.hpp>
#include <array>

class Triangle{
	private :
		std::array<unsigned int,3> indiceVertice;
		
	public :
		Triangle(size_t v1, size_t v2, size_t v3){
			indiceVertice[0] = v1;
			indiceVertice[1] = v2;
			indiceVertice[2] = v3;
		}
};