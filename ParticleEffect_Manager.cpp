#include "ParticleEffect_Manager.h"
ParticleEffect_Manager::ParticleEffect_Manager()
{

}

void ParticleEffect_Manager::draw(ShaderProgram* sp, glm::mat4 M)
{
	for (int i = 0; i < efekty.size(); i++)
	{
		efekty[i].draw(sp, M);
	}
}

void ParticleEffect_Manager::update(float czas)
{

	for (int i = 0; i < efekty.size(); i++)
	{

		efekty[i].update(czas);
	}

	if (efekty.size() > 1000)
		clear();

}

void ParticleEffect_Manager::clear()
{
	for (int i = efekty.size() - 1; i >= 0; i++)
	{
		if (efekty[i].is_active() == false)
		{
			efekty[i] = efekty.back();
			efekty.pop_back();
		}
	}
}

bool ParticleEffect_Manager::start_effect(std::string name, glm::vec3 pozycja, float angle)
{
	if (creators[name] == 0)
		return false;

	efekty.push_back(creators[name]->create(pozycja, angle));

	return true;
}

bool ParticleEffect_Manager::add_effect(std::string name, ParticleEffect_Creator* c)
{
	if (creators[name] != 0)
		return false;

	std::cout << name << " - dodano\n";
	
	creators[name] = c;

	return true;
}

ParticleEffect_Creator* ParticleEffect_Manager::create_effect(std::string name)
{
	if (creators[name] != 0)
		return NULL;

	creators[name] = new ParticleEffect_Creator();

	return creators[name];
}

ParticleEffect_Creator* ParticleEffect_Manager::access_effect(std::string name)
{
	if (creators[name] != 0)
		return creators[name];
	else
		return NULL;
}