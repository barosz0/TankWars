#pragma once
#include "Tank.h"
#include "Obstacle.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <queue>


class Enemy
{
	Tank tank_model;
	wspolzedne pozycja;
	wspolzedne *pozycja_gracza;
	std::vector<std::vector<int>> *flagi_blokady_pola;

	bool flag_czy_ruch = false;
	wspolzedne* gdzie_ruch = nullptr;


	void szukaj_drogi();
	int ktory_nastepny(std::vector<std::pair<int, int>>k, std::vector<std::vector<int>> odl); // dla funkcji szukaj drogi

public:
	Enemy();
	Enemy(Tank t, wspolzedne p);

	void draw(ShaderProgram* sp, glm::mat4 M);
	void update(float czas); // tu mo¿e byc zwracana flaga akcji



	void set_tank_model(Tank t);
	void set_pozycja(wspolzedne p);
	void set_flagi_blokady_pola(std::vector<std::vector<int>> *fbp);

	void set_pozycja_gracza_pointer(wspolzedne* wp);

	wspolzedne get_pozycja();


};

