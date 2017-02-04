#include <GL/gl3w.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp> 
#include <glm/gtx/quaternion.hpp>
#include "MeshView.hpp"
#include "Worm.hpp"

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
	float rayonMonde = 10.0;
	Mesh C = Mesh::Sphere(glm::vec3(0.0,0.0,0.0), rayonMonde, 50);
	C.init();
	C.upload();
	Worm worm = Worm(C);
	std::vector<MeshView>vecMeshView;
	vecMeshView.emplace_back(C);
	vecMeshView.emplace_back(C, glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(rayonMonde + 0.05, 0, 0)), glm::vec3(0.05)));
	vecMeshView[0].color = glm::vec4(0.0, 0.0, 1.0, 1.0);
	glm::vec3 lightDir(1.0, 1.0, 0.0);
	sf::Clock clock;
	sf::Shader shader;
	glm::mat4 matriceCam = glm::lookAt(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 matricePerspective = glm::perspective(3.14159f/4, static_cast<float>(window.getSize().x)/window.getSize().y, 0.1f, 100.0f);
	shader.loadFromFile("../shaders/vertex/vertexshader.glsl", "../shaders/fragment/fragmentshader.glsl");
	float distanceCam = 40.0;
	glm::vec3 camera(0.0, 0.0, distanceCam);
	glm::mat4 worldRot;
	float speed = 1.0;
	float steering_speed = 2.0;
	
    // on fait tourner le programme jusqu'à ce que la fenêtre soit fermée
    while (window.isOpen())
    {
        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        sf::Event event;
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
        while (window.pollEvent(event))
        {
            // événement "fermeture demandée" : on ferme la fenêtre
            if (event.type == sf::Event::Closed) {
                window.close();
				return 0;
			}
        }
		glClearColor(0.0,0.0,0.0,1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		sf::Shader::bind(&shader);
		auto location = glGetUniformLocation(shader.getNativeHandle() ,  "perspective");
		if (location < 0) {
			std::cerr << "Error" << std::endl;
			return -1;
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			worldRot = glm::rotate(worldRot, steering_speed * -time, glm::vec3(glm::inverse(worldRot) * glm::vec4(0.0, 0.0, 1.0, 1.0)));
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			worldRot = glm::rotate(worldRot, steering_speed * time, glm::vec3(glm::inverse(worldRot) * glm::vec4(0.0, 0.0, 1.0, 1.0)));
		
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			worldRot = glm::rotate(worldRot, speed * time, glm::vec3(glm::inverse(worldRot) * glm::vec4(1.0, 0.0, 0.0, 1.0)));

		matriceCam = glm::lookAt(camera, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		
		glUniformMatrix4fv(glGetUniformLocation(shader.getNativeHandle() ,  "perspective"), 1, false, glm::value_ptr(matricePerspective));
		glUniformMatrix4fv(glGetUniformLocation(shader.getNativeHandle() ,  "camera"), 1, false, glm::value_ptr(matriceCam));
		
		// Draw the triangle !
		//C.draw();
		glUniform3fv(glGetUniformLocation(shader.getNativeHandle() ,  "lightDir"), 1, glm::value_ptr(lightDir));
		for (const auto &i : vecMeshView)
			i.draw(shader, rotate);
		
		//Apply Rotation to Light
		glUniform3fv(glGetUniformLocation(shader.getNativeHandle() ,  "lightDir"), 1, glm::value_ptr(worldRot * glm::vec4(lightDir, 1.0)));
		for(const auto &i : worm.body)
			i.draw(shader);
		window.display();
    }

    return 0;
}


