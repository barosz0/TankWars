#pragma once
#include "Tank.h"
#include "Obstacle.h"
#include <vector>

class Enemy
{
	Tank* tank_model;
	wspolzedne pozycja;
	std::vector<std::vector<int>> *flagi_blokady_pola;

public:
	Enemy();

	void draw(ShaderProgram* sp, glm::mat4 M);
	void update(float czas); // tu mo¿e byc zwracana flaga akcji

	void set_tank_model(Tank *t);
	void set_pozycja(wspolzedne p);
	void set_flagi_blokady_pola(std::vector<std::vector<int>> *fbp);

	wspolzedne get_pozycja();


};

