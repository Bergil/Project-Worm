#include <Vertex.hpp>
#include <Triangle.hpp>
#include <vector>

class Mesh{
	private :
		std::vector<Vertex> vertices;
		std::vector<Triangle> triangles;
		
	public :

		const std::vector<Vertex> &getVertices(){return vertices;}
		const std::vector<Triangle> &getTriangles(){return triangles;}
		static Mesh Sphere(const glm::vec3& center, float radius, size_t precision);
};