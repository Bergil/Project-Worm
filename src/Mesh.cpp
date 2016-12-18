#include "Mesh.hpp"

Mesh Mesh::Sphere(const glm::vec3& center,
				  float radius,
				  size_t precision)
{
	Mesh C;
	float pi = 3.14159;
	glm::vec3 u = glm::vec3(1.f, 0.f, 0.f),
	          v = glm::vec3(0.f, 0.f, 1.f),
			  w = glm::vec3(0.f, 1.f, 0.f);
		
	float incrRot = pi/precision;
	float subIncrRot = 2*pi/precision;
	
	for(size_t i = 1; i < precision; ++i)
	{
		glm::vec3 subCenter = std::cos(incrRot*i)*w;
		float subRadius = std::sin(incrRot*i);
		for(size_t j = 0; j < precision; ++j)
		{
			glm::vec3 tmp = subRadius*(std::cos(subIncrRot*j)*u + std::sin(subIncrRot*j)*v) + subCenter;
			C.vertices.push_back(Vertex (tmp*radius, glm::normalize(tmp - center)));
		}
	}
	
	C.vertices.push_back(Vertex(center + w*radius, w));
	C.vertices.push_back(Vertex(center - w*radius, -w));
	
	for(size_t i = 0; i < precision - 2; ++i)
	{
		for(size_t j = 0; j < precision; ++j)
		{
			C.triangles.push_back(Triangle(i*precision + j, i*precision + ((j + 1) % precision),(i + 1)*precision + j));
								   
			C.triangles.push_back(Triangle(i*precision + ((j + 1) % precision), (i + 1)*precision + ((j + 1) % precision),(i + 1)*precision + j)); 
								   
		}
	}
	
	for(size_t i = 0; i < precision ; ++i)
	{
		C.triangles.push_back(Triangle(precision*(precision - 1), (i + 1) % precision, i));
							
		C.triangles.push_back(Triangle(precision*(precision - 1) + 1, precision*(precision - 2) + i, precision*(precision - 2) + ((i + 1) % precision)));
		
	}
	
	return C;
}