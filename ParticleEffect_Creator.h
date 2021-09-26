#pragma once
#include <iostream>

#include "constants.h"
#include "ParticleGroup.h"
#include <random>

float default_axi_generator_ParticleEffect_Creator(std::default_random_engine &generator);
float default_time_generator_ParticleEffect_Creator(std::default_random_engine &generator);

class ParticleEffect_Creator
{
	ParticleGroup modelowa;
	std::default_random_engine generator;
	glm::vec3 color;



	float (*x_axi_generator)(std::default_random_engine &generator);
	float (*y_axi_generator)(std::default_random_engine &generator);
	float (*z_axi_generator)(std::default_random_engine &generator);
	float (*time_generator)(std::default_random_engine &generator);

	
	glm::vec3 rotateVec3Y(glm::vec3 v, float angle);


public:
	ParticleEffect_Creator();
	
	ParticleGroup create(glm::vec3 pozycja_startowa, float angle);

	ParticleGroup* modelowa_pointer();
	void set_modelowa(ParticleGroup m);

	void set_x_axi_generator(float f(std::default_random_engine &generator));
	void set_y_axi_generator(float f(std::default_random_engine &generator));
	void set_z_axi_generator(float f(std::default_random_engine &generator));
	void set_time_generator(float f(std::default_random_engine &generator));




};

