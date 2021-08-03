#include "Tank.h"

Tank::Tank(obj3d turret_obj, obj3d hull_obj, obj3d tracks_obj)
{
	turret = turret_obj;
	hull = hull_obj;
	tracks = tracks_obj;
	pozycja_wieza = 0;
	pozycja_kadlub = 0;
}

void Tank::draw(ShaderProgram* sp,glm::mat4 M)
{
	M = glm::rotate(M, -PI/2, glm::vec3(0.0f, 1.0f, 0.0f)); // wyprostowanie czolgu wzglendem kamery


	M = glm::rotate(M, pozycja_kadlub, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

	hull.draw(sp);
	tracks.draw(sp);

	M = glm::rotate(M, pozycja_wieza, glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::translate(M, glm::vec3(-0.2f, 0.0f, 0.0f)); // lekka poprawa osi obrotu
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

	turret.draw(sp);
}

void Tank::set_pozycja_wieza(float p)
{
	pozycja_wieza = p;
}

float Tank::get_pozycja_wieza()
{
	return pozycja_wieza;
}

void Tank::obroc_wierze(float p)
{
	pozycja_wieza += p;
}

void Tank::set_pozycja_kadlub(float p)
{
	pozycja_kadlub = p;
}

float Tank::get_pozycja_kadlub()
{
	return pozycja_kadlub;
}

void Tank::obroc_kadlub(float p)
{
	pozycja_kadlub += p;
}