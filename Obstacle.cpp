#include "Obstacle.h"

Obstacle::Obstacle(obj3d* o, wspolzedne p)
{
	obj = o;
	pozycja = p;
}

void Obstacle::draw(ShaderProgram* sp, glm::mat4 M)
{
	glm::mat4 pom_M = glm::translate(M, glm::vec3(pozycja.x, 0.0f, pozycja.y));
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(pom_M));
	obj->draw(sp);
}

