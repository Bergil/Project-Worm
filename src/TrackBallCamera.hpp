#include <SFML/Window.hpp>

class TrackBallCamera
{
	protected:
		double distance; //distance entre boule centrale et camera
		double sensivity; // de combien rotate la boule

	
	public:
		TrackBallCamera();
		void look();
		~TrackBallCamera();

};