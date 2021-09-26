#include "ParticleEffect_Creator.h"
ParticleEffect_Creator::ParticleEffect_Creator():
	color(glm::vec3(1.0f,1.0f,1.0f)),
	modelowa()
{
	x_axi_generator = &default_axi_generator_ParticleEffect_Creator;
	y_axi_generator = &default_axi_generator_ParticleEffect_Creator;
	z_axi_generator = &default_axi_generator_ParticleEffect_Creator;
	time_generator = &default_time_generator_ParticleEffect_Creator;

}

ParticleGroup ParticleEffect_Creator::create(glm::vec3 pozycja_startowa, float angle)
{
	ParticleGroup ret= modelowa;
	Particle* list_p = new Particle[ret.get_liczba_czasteczek()];

	for (int i = 0; i < ret.get_liczba_czasteczek(); i++)
	{
		list_p[i].position = pozycja_startowa;

		list_p[i].speed = glm::vec3(x_axi_generator(generator), y_axi_generator(generator), z_axi_generator(generator));

		list_p[i].speed = rotateVec3Y(list_p[i].speed, angle);

		list_p[i].color = color;

		list_p[i].life_time = time_generator(generator);

		list_p[i].max_life_time = list_p[i].life_time;
	}

	ret.set_list_particles(list_p);

	return ret;
}

glm::vec3 ParticleEffect_Creator::rotateVec3Y(glm::vec3 v, float angle)
{
	glm::mat3 rot = glm::mat3(1.0f);

	rot[0][0] = cos(angle);
	rot[2][2] = cos(angle);
	rot[0][2] = sin(angle);
	rot[2][0] = -sin(angle);


	return rot * v;
}

ParticleGroup* ParticleEffect_Creator::modelowa_pointer()
{
	return &modelowa;
}

float default_axi_generator_ParticleEffect_Creator(std::default_random_engine &generator)
{
	std::normal_distribution<float> distribution(0.0, 1.0);

	return distribution(generator);
}

float default_time_generator_ParticleEffect_Creator(std::default_random_engine &generator)
{
	std::normal_distribution<float> distribution(3.0, 1.0);

	return abs(distribution(generator));
}

void ParticleEffect_Creator::set_x_axi_generator(float f(std::default_random_engine &generator))
{
	x_axi_generator = f;
}

void ParticleEffect_Creator::set_y_axi_generator(float f(std::default_random_engine &generator))
{
	y_axi_generator = f;
}

void ParticleEffect_Creator::set_z_axi_generator(float f(std::default_random_engine &generator))
{
	z_axi_generator = f;
}

void ParticleEffect_Creator::set_time_generator(float f(std::default_random_engine &generator))
{
	time_generator = f;
}

void ParticleEffect_Creator::set_modelowa(ParticleGroup m)
{
	modelowa = m;
}