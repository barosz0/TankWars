#include "Enemy.h"
Enemy::Enemy()
{

}

Enemy::Enemy(Tank *t, wspolzedne p)
{
	tank_model = t;
	pozycja = p;
}

void Enemy::draw(ShaderProgram* sp, glm::mat4 M)
{
	glm::mat4 pom_M = glm::translate(M, glm::vec3(pozycja.x, 0.0f, pozycja.y));

	pom_M = glm::scale(pom_M, glm::vec3(0.5, 0.5, 0.5));

	pom_M = glm::translate(pom_M, glm::vec3(0.0f, -0.8f, 0.0f));

	tank_model->draw(sp, pom_M);
}

void Enemy::update(float czas)
{
	tank_model->update(czas, 0);
}

void Enemy::set_tank_model(Tank* t)
{
	tank_model = t;
}

void Enemy::set_pozycja(wspolzedne p)
{
	pozycja = p;
}

void Enemy::set_flagi_blokady_pola(std::vector<std::vector<int>>* fbp)
{
	flagi_blokady_pola = fbp;
}

wspolzedne Enemy::get_pozycja()
{
	return pozycja;
}