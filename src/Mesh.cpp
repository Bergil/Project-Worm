#include "Mesh.hpp"

Mesh Mesh::Sphere(const glm::vec3& center,
				  float radius,
				  size_t precision)
{
	Mesh C;
	float pi = 3.141592653;
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
			C.vertices.push_back(Vertex(tmp*radius, glm::normalize(tmp - center)));
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


 Mesh Mesh::Cube(float width){
	float t = width/2;
	std::array<glm::vec3,8> P{glm::vec3{-t, -t, t}, 
							glm::vec3{t, -t, t}, 
							glm::vec3{-t, t, t}, 
							glm::vec3{t, t, t}, 
							glm::vec3{-t, -t, -t}, 
							glm::vec3{t, -t, -t}, 
							glm::vec3{-t, t, -t}, 
							glm::vec3{t, t, -t}};
	Mesh C;
	glm::vec3 x = glm::vec3(1.f, 0.f, 0.f),
	          y = glm::vec3(0.f, 0.f, 1.f),
			  z = glm::vec3(0.f, 1.f, 0.f);
	//triangle 1 face z
	C.vertices.push_back(Vertex(P[0], z));
	C.vertices.push_back(Vertex(P[1], z));
	C.vertices.push_back(Vertex(P[2], z));
	
	//triangle 2 face z
	C.vertices.push_back(Vertex(P[1], z));
	C.vertices.push_back(Vertex(P[3], z));
	C.vertices.push_back(Vertex(P[2], z));
	
		//triangle 1 face -z
	C.vertices.push_back(Vertex(P[5], -z));
	C.vertices.push_back(Vertex(P[4], -z));
	C.vertices.push_back(Vertex(P[6], -z));
	
		//triangle 2 face -z
	C.vertices.push_back(Vertex(P[5], -z));
	C.vertices.push_back(Vertex(P[6], -z));
	C.vertices.push_back(Vertex(P[7], -z));
	
		//triangle 1 face x
	C.vertices.push_back(Vertex(P[3], x));
	C.vertices.push_back(Vertex(P[1], x));
	C.vertices.push_back(Vertex(P[7], x));
	
		//triangle 2 face x
	C.vertices.push_back(Vertex(P[1], x));
	C.vertices.push_back(Vertex(P[5], x));
	C.vertices.push_back(Vertex(P[7], x));
	
		//triangle 1 face -x
	C.vertices.push_back(Vertex(P[4], -x));
	C.vertices.push_back(Vertex(P[0], -x));
	C.vertices.push_back(Vertex(P[6], -x));
	
		//triangle 2 face -x
	C.vertices.push_back(Vertex(P[6], -x));
	C.vertices.push_back(Vertex(P[0], -x));
	C.vertices.push_back(Vertex(P[2], -x));
	
	//triangle 1 face y
	C.vertices.push_back(Vertex(P[6], y));
	C.vertices.push_back(Vertex(P[2], y));
	C.vertices.push_back(Vertex(P[3], y));	
	
		//triangle 2 face y
	C.vertices.push_back(Vertex(P[6], y));
	C.vertices.push_back(Vertex(P[3], y));
	C.vertices.push_back(Vertex(P[7], y));
	
		//triangle 1 face -y
	C.vertices.push_back(Vertex(P[0], -y));
	C.vertices.push_back(Vertex(P[4], -y));
	C.vertices.push_back(Vertex(P[1], -y));
	
		//triangle 2 face -y
	C.vertices.push_back(Vertex(P[1], -y));
	C.vertices.push_back(Vertex(P[4], -y));
	C.vertices.push_back(Vertex(P[5], -y));
	
	for (int i = 0; i < 12; ++i){
		C.triangles.push_back(Triangle(i*3, i*3+1, i*3+2));
	}
	
	return C;
}