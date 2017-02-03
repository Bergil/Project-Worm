#include <GL/gl3w.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include <Mesh.hpp>

//Class Vertex avec position, Normal, etc
//Class Mesh ac ensemble Vertex et ensemble de triangles (3 indice de vertex)
//GLDrawArrayElement avec autre buffer qui contient tt les buffers.


glm::vec3 SphereToCart(float dist, float theta, float phi){
	float sinP = sin(phi);
	float cosT = cos(theta);
	return dist*glm::vec3(sinP*cosT, sinP*sin(theta), cos(phi));
}


int main()
{
	sf::ContextSettings parameters;
	parameters.antialiasingLevel = 8;
    parameters.majorVersion = 4;
    parameters.minorVersion = 3;
	parameters.depthBits = 24;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake 3D",sf::Style::Default, parameters);
	if (gl3wInit()) {
                fprintf(stderr, "failed to initialize OpenGL\n");
                return -1;
    }
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	//Mesh C = Mesh::Sphere(glm::vec3(0.0,0.0,0.0), 10.0f, 50);
	Mesh C = Mesh::Cube(10.0f);
	
		// This will identify our vertex buffer
	GLuint vertexbuffer;
	GLuint trianglebuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	glGenBuffers(1, &trianglebuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, trianglebuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, C.getVertices().size()*sizeof(Vertex), &C.getVertices()[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, C.getTriangles().size()*sizeof(Triangle), &C.getTriangles()[0], GL_STATIC_DRAW);
	sf::Clock clock;
	sf::Shader shader;
	glm::mat4 matriceCam = glm::lookAt(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 matricePerspective = glm::perspective(3.14159f/4, static_cast<float>(window.getSize().x)/window.getSize().y, 0.1f, 100.0f);
	shader.loadFromFile("../shaders/vertex/vertexshader.glsl", "../shaders/fragment/fragmentshader.glsl");
	float distance = 40.0;
	float angleX = 0.0;
	float angleY = 0.0;
	glm::vec3 camera;
	
    // on fait tourner le programme jusqu'à ce que la fenêtre soit fermée
    while (window.isOpen())
    {
        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        sf::Event event;
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
        while (window.pollEvent(event))
        {
            // évènement "fermeture demandée" : on ferme la fenêtre
            if (event.type == sf::Event::Closed)
                window.close();
        }
		glClearColor(0.0,0.0,0.0,1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		sf::Shader::bind(&shader);
		auto location = glGetUniformLocation(shader.getNativeHandle() ,  "perspective");
		if (location < 0){
			std::cerr<< "Error"<<std::endl;
			return -1;
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			angleX += time; //same step for every frame
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			angleX -= time;
		
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			angleY += time;
		
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			angleY -= time;
		
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
			angleX = 0.0;
			angleY = 0.0;
		}
		
		camera = SphereToCart(distance, angleY, angleX);

		matriceCam = glm::lookAt(camera, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		glUniformMatrix4fv(glGetUniformLocation(shader.getNativeHandle() ,  "perspective"), 1, false, glm::value_ptr(matricePerspective));
		glUniformMatrix4fv(glGetUniformLocation(shader.getNativeHandle() ,  "camera"), 1, false, glm::value_ptr(matriceCam));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer( // Describe struct vertex
		   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		   3,                  // size
		   GL_FLOAT,           // type
		   GL_FALSE,           // normalized?
		   sizeof(Vertex),                  // stride
		   (void*)0            // array buffer offset
		);
		glVertexAttribPointer(
		   1,                 
		   3,                  // size
		   GL_FLOAT,           // type
		   GL_TRUE,           // normalized?
		   sizeof(Vertex),                  // stride
		   (void*)offsetof(Vertex, normale)           // array buffer offset
		);
		glVertexAttribPointer(
		   2,                 
		   2,                  // size
		   GL_FLOAT,           // type
		   GL_FALSE,           // normalized?
		   sizeof(Vertex),                  // stride
		   (void*)offsetof(Vertex, texcoord)             // array buffer offset
		);
		// Draw the triangle !
		//glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
		glDrawElements(GL_TRIANGLES, C.getTriangles().size()*3,  GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_POINTS, 0, C.getVertices().size());
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		window.display();
    }

    return 0;
}


