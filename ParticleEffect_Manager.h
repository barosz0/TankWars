#pragma once

#include "ParticleEffect_Creator.h"
#include <map>

class ParticleEffect_Manager
{
	std::map<std::string, ParticleEffect_Creator*> creators;
	std::vector<ParticleGroup> efekty;

public:
	
	ParticleEffect_Manager();

	void draw(ShaderProgram *sp, glm::mat4 M);
	void update(float czas);
	void clear();

	bool start_effect(std::string name, glm::vec3 pozycja, float angle);

	bool add_effect(std::string name, ParticleEffect_Creator* c);
	ParticleEffect_Creator* create_effect(std::string name);

	ParticleEffect_Creator* access_effect(std::string name);

};

