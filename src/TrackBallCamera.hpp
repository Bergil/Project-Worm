#include <SFML/Window.hpp>

class TrackBallCamera
{
	protected:
		double distance = 40; //distance entre boule centrale et camera
		double sensivity = 100; // de combien rotate la boule
		sf::ContextSettings parameters;
	
	public:
		TrackBallCamera();
		void look();

};