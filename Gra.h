#pragma once
#include "obj3d.h"
#include "Tank.h"

#include "constants.h"
#include <GLFW/glfw3.h>
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

	ShaderProgram* mainShader;
	glm::mat4 M_main;

	wspolzedne pozycja_gracza;

	Tank* player_tank; // do zmiany na obiekt "player"

	void create_game();

public:
	
	Gra();
	Gra(obj3d *z);
	void draw(ShaderProgram* sp, glm::mat4 M); 
	void update(float t);
	void drawScene(GLFWwindow* window, float obrot_kamery);

	//get set

	void set_mainShader(ShaderProgram* sp);
	void set_M_main(glm::mat4 M);
	void set_player_tank(Tank* t);

	glm::mat4 get_M_main();
};

