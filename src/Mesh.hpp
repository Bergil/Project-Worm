#include <Vertex.hpp>
#include <Triangle.hpp>
#include <vector>
#include <GL/gl3w.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

class Mesh{
	
	public :
		struct GPUBuffer{
			GLuint vertexbuffer;
			GLuint trianglebuffer;
			GLuint VertexArrayID;
		};
				
		void init(); //initialize OpenGL buffers
		void upload(); //upload Mesh on GPU
		void draw();
		
		const std::vector<Vertex> &getVertices(){return vertices;}
		const std::vector<Triangle> &getTriangles(){return triangles;}
		static Mesh Sphere(const glm::vec3& center, float radius, size_t precision);
		static Mesh Cube(float width);
		
	private :
		std::vector<Vertex> vertices;
		std::vector<Triangle> triangles;
		GPUBuffer buffer;
		
};