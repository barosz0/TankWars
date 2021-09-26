#pragma once
#include "obj3d.h"
#include "Tank.h"
#include "Obstacle.h"
#include "Enemy.h"
#include "ParticleEffect_Manager.h"
#include "Interface.h"


#include "constants.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <cstdlib>
#include <iostream>



class Gra
{

	std::vector<obj3d*>* modele_przeskod;

	int rozmiar_mapy;


	std::vector<Obstacle*> przeszkody;
	std::vector<Enemy*> przeciwnicy;

	std::vector<std::vector<int>> flagi_blokady_pola; // 1 - przeszkod, 2 - przeciwnik
	obj3d* podloze_obj;
	obj3d* sciana_obj;

	ShaderProgram* mainShader;
	ShaderProgram* particleShader;


	Tank* enemy_tank; // do zmiany na vector modeli przeciwnikow (losowanie czolgu przeciwnikowi)

	Tank* player_tank; // do zmiany na obiekt "player"
	wspolzedne pozycja_gracza; // do zmiany na obiekt "player"
	float shoot_cooldown; // do zmiany na obiekt "player"
	int ilosc_hp;
	int ilosc_ammo;
	float player_dead_animation_progres;

	void player_oddaj_strzal();

	ParticleEffect_Manager* particle_manager;
	Interface *UI;

public:
	
	Gra();
	Gra(obj3d *z);
	void draw_map(ShaderProgram* sp, glm::mat4 M); 
	void draw_enemy(ShaderProgram* sp, glm::mat4 M);
	void update(float t, float speed_kam, float speed_wierza, float speed_kadlub, bool shoot);
	void drawScene(GLFWwindow* window, float obrot_kamery);

	void create_game();

	//get set

	void set_mainShader(ShaderProgram* sp);
	void set_particleShader(ShaderProgram* sp);
	void set_player_tank(Tank* t);
	void set_enemy_tank(Tank* t);
	void set_sciana_obj(obj3d* o);

	void set_particle_manager(ParticleEffect_Manager* pm);
	void set_interface(Interface* i);

	//set startowe
	
	void set_rozmiar_mapy(int r);
	void set_modele_przeszkod(std::vector<obj3d*>* mp);

	//void set_texture_smoke(GLuint t, int x, int y);

	void rusz_gracza(float s); // do zmiany na obiekt "player"

};

