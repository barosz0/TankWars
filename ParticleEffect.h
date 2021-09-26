#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <random>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "shaderprogram.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

#include <algorithm>
#include <cstdlib>

#include "constants.h"
struct Particle
{
	glm::vec3 position;
	glm::vec3 speed;
	glm::vec3 color;
	float life_time;
	float max_life_time;


	bool active = true;

};

class ParticleEffect
{
	Particle *list_p;
	int liczba_czasteczek;
	float rozmiar_czasteczki;

	float rotation;

	GLuint texture;
	int rozmiar_tex_x;
	int rozmiar_tex_y;

	
	float Vertices[16];
	float texCoords[8];
	//tymczasowe
	float color[16] =
	{
		0.7f,0.2f,0.5f,1.0f,
		1.0f,1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,1.0f
	};
	//tymczasowe


	glm::vec2 tex_offset(int id);
	glm::vec3 rotateVec3Y(glm::vec3 v, float angle);
public:
	ParticleEffect();
	void create_effect(glm::vec3 pozycja_startowa,int l_c, float rot);
	void update(float czas);
	void draw(ShaderProgram* sp,glm::mat4 M);

	void test_draw(ShaderProgram* sp, glm::mat4 M, float* vertices, int vertexCount); // do usuniecia

	void sort_particle();

	void set_texture(GLuint t, int x, int y);
};

