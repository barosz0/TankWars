#pragma once
#include "obj3d.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


struct wspolzedne {
	float x = 0;
	float y = 0;

	wspolzedne()
	{}

	wspolzedne(float xp, float yp)
	{
		x = xp;
		y = yp;
	}
};

class Obstacle
{
	obj3d* obj;
	wspolzedne pozycja;
	float rozmiar = 0.8;

public:

	Obstacle(obj3d* o, wspolzedne p);

	void draw(ShaderProgram* sp, glm::mat4 M);
	bool czy_kolizja(wspolzedne tank);
	wspolzedne rozwiaz_kolizje(wspolzedne t, wspolzedne r, int n); //w tym momencie nie uzywana


};