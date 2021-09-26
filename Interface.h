#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "shaderprogram.h"
#include <vector>
#include <iostream>

class Interface
{
	GLuint numbers;
	GLuint ammo;
	GLuint hearts;
	GLuint crosshair;

	std::vector<std::pair<int, int>> numbers_offset; //offset size
	int rozmiar_numbers;

	ShaderProgram *interface_shader;

	void _draw_hearts(int hp, float x, float y);
	void _draw_ammo(int ilosc, float x, float y);
	void _draw_crosshair(float x, float y);
public:

	Interface();

	void draw_interface(int hp,int ammo_ilosc);

	void set_tex_numbers(GLuint t, std::vector<std::pair<int, int>> n_o, int r_n);
	void set_tex_ammo(GLuint t);
	void set_tex_hearts(GLuint t);
	void set_tex_crosshair(GLuint t);
	void set_shader(ShaderProgram *s);


};

