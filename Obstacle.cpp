#include "Obstacle.h"

Obstacle::Obstacle(obj3d* o, wspolzedne p)
{
	obj = o;
	pozycja = p;
}

void Obstacle::draw(ShaderProgram* sp, glm::mat4 M)
{
	glm::mat4 pom_M = glm::translate(M, glm::vec3(pozycja.x, 0.0f, pozycja.y));

	pom_M = glm::scale(pom_M, glm::vec3(0.5, 0.5, 0.5)); //zmniejszenie kostki
	pom_M = glm::translate(pom_M, glm::vec3(0.0f, 1.0f, 0.0f)); //przesuniecie na podloze

	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(pom_M));
	obj->draw(sp);
}

bool Obstacle::czy_kolizja(wspolzedne tank_pozycja)
{
	float d = sqrt((tank_pozycja.x - pozycja.x)*(tank_pozycja.x - pozycja.x) + (tank_pozycja.y - pozycja.y)*(tank_pozycja.y - pozycja.y));

	if (d < rozmiar) return true;
	else return false;
}

wspolzedne Obstacle::rozwiaz_kolizje(wspolzedne t, wspolzedne r, int n)
{
	if (n <= 0) return t;
	wspolzedne pom = { (t.x + r.x) / 2,(t.y + r.y) / 2 };
	if (czy_kolizja(pom))
		return rozwiaz_kolizje(t, pom, n - 1);
	else
		return rozwiaz_kolizje(pom, r, n - 1);
}
