#pragma once
#include "obj3d.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct wspolzedne {
	float x=0;
	float y=0;
};

class Gra
{
	int rozmiar_mapy;
	//int** podloze;
	obj3d* podloze_obj;

	wspolzedne pozycja_gracza;


	void create_game();

public:
	
	Gra();
	Gra(obj3d *z);
	void draw(ShaderProgram* sp, glm::mat4 M); 
	void update(float t);
};

