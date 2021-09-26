#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shaderprogram.h"

#include <iostream>

struct Particle
{
	glm::vec3 position;
	glm::vec3 speed;
	glm::vec3 color;
	float life_time;
	float max_life_time;


	bool active = true;

};

class ParticleGroup
{
	bool Group_active;

	Particle* list_p; // potencjalna zmiana na vector
	long int liczba_czasteczek;
	float rozmiar_czasteczki;


	glm::vec3 scale_vec;

	GLuint texture;
	int rozmiar_tex_x;
	int rozmiar_tex_y;

	float Vertices[16];
	float texCoords[8];
	bool alpha_channel;

	glm::vec2 tex_offset(int id);
	void tabs_fill();
public:

	ParticleGroup();
	bool update(float czas);
	void draw(ShaderProgram* sp, glm::mat4 M);

	bool is_active();

	void set_list_particles(Particle* lp);
	void set_liczba_czasteczek(int lc);
	void set_rozmiar_czasteczek(float rc);
	void set_texture(GLuint t, int rx, int ry);
	void set_alpha_channel(bool c);
	void set_scale(glm::vec3 v);

	void show_yourself();

	int get_liczba_czasteczek();

};

