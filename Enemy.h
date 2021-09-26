#pragma once
#include "Tank.h"
#include "Obstacle.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <queue>
#include "ParticleEffect_Manager.h"


class Enemy
{
	Tank tank_model;
	wspolzedne pozycja;
	wspolzedne *pozycja_gracza;
	std::vector<std::vector<int>> *flagi_blokady_pola;

	//ruch
	bool flag_czy_ruch = false;
	bool flag_czy_obrot = false;
	wspolzedne* gdzie_ruch = nullptr;

	//strzal
	float shoot_cooldown;
	bool flag_czy_widac_gracza;

	int hp_enemy;
	float dead_animation_progress;

	ParticleEffect_Manager* particle_manager;

	
	void szukaj_drogi();
	int ktory_nastepny(std::vector<std::pair<int, int>>k, std::vector<std::vector<int>> odl); // dla funkcji szukaj drogi
	
	bool oddaj_strzal();

	void _update_ruch_tank(float czas);
	void _update_obrot_wierzy(float czas);

public:
	Enemy();
	Enemy(Tank t, wspolzedne p);

	void draw(ShaderProgram* sp, glm::mat4 M);
	void update(float czasc, int* damage); // tu mo¿e byc zwracana flaga akcji

	void trafiony(int dam);
	bool czy_zyje();

	void set_tank_model(Tank t);
	void set_pozycja(wspolzedne p);
	void set_flagi_blokady_pola(std::vector<std::vector<int>> *fbp);

	void set_pozycja_gracza_pointer(wspolzedne* wp);
	void set_particle_manager(ParticleEffect_Manager* pm);

	wspolzedne get_pozycja();


};

