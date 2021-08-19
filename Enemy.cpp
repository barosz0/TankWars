#include "Enemy.h"
Enemy::Enemy()
{

}

void Enemy::draw(ShaderProgram* sp, glm::mat4 M)
{
	glm::translate(M, glm::vec3(pozycja.x, 0.0f, pozycja.y));
	tank_model->draw(sp, M);
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