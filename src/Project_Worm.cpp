#include <GL/gl3w.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include <Mesh.hpp>
#include <MeshView.hpp>

//Class Vertex avec position, Normal, etc
//Class Mesh ac ensemble Vertex et ensemble de triangles (3 indice de vertex)
//GLDrawArrayElement avec autre buffer qui contient tt les buffers.

template<typename T>
T clamp(T value, T max, T min){
	if (value > max)
		value = max;
	else if (value < min)
		value = min;
	return value;
}

glm::vec3 SphereToCart(float dist, float theta, float phi){
	float camX = dist * -sinf(phi*(3.14159f/180)) * cosf((theta)*(3.14159f/180));
	float camY = dist * -sinf((theta)*(3.14159f/180));
	float camZ = -dist * cosf((phi)*(3.14159f/180)) * cosf((theta)*(3.14159f/180));
	
	return glm::vec3(camX, camY, camZ);
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
	
	//Mesh C = Mesh::Cube(10.0f);
	Mesh C = Mesh::Sphere(glm::vec3(0.0,0.0,0.0), 10.0f, 50);
	C.init();
	C.upload();
	std::vector<MeshView>vecMeshView;
	vecMeshView.emplace_back(C);
	vecMeshView.emplace_back(C, glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(10.0, 0.0, 0.0)), glm::vec3(1.0)));
	
	sf::Clock clock;
	sf::Shader shader;
	glm::mat4 matriceCam = glm::lookAt(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 matricePerspective = glm::perspective(3.14159f/4, static_cast<float>(window.getSize().x)/window.getSize().y, 0.1f, 100.0f);
	shader.loadFromFile("../shaders/vertex/vertexshader.glsl", "../shaders/fragment/fragmentshader.glsl");
	float distance = 40.0;
	float angleX = 0.0;
	float angleY = 0.0;
	float minY = -90.0;
	float maxY = 90.0;
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
            if (event.type == sf::Event::Closed){
                window.close();
				return 0;
			}
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
			angleX -= time*100; //same step for every frame
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			angleX += time*100;
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			angleY -= time*100;
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			angleY += time*100;
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
			angleX = 0.0;
			angleY = 0.0;
		}
		angleY = clamp(angleY, maxY, minY);
		camera = SphereToCart(distance, angleY, angleX);

		matriceCam = glm::lookAt(camera, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		glUniformMatrix4fv(glGetUniformLocation(shader.getNativeHandle() ,  "perspective"), 1, false, glm::value_ptr(matricePerspective));
		glUniformMatrix4fv(glGetUniformLocation(shader.getNativeHandle() ,  "camera"), 1, false, glm::value_ptr(matriceCam));
		
		// Draw the triangle !
		//C.draw();
		for(const auto &i : vecMeshView)
			i.draw(shader);
		window.display();
    }

    return 0;
}


