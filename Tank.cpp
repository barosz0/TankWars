#include "Tank.h"
Tank::Tank()
{

}

Tank::Tank(obj3d *turret_obj, obj3d *hull_obj, obj3d *tracks_obj)
{
	turret = turret_obj;
	hull = hull_obj;
	tracks = tracks_obj;
	pozycja_wieza = -PI*300;
	pozycja_kadlub = -PI * 300;
}



void Tank::draw(ShaderProgram* sp,glm::mat4 M)
{
	float tempo_animacji_poziom = 20;
	float tempo_animacji_pion = 30;
	float tempo_animacji_kadlub = 60;

	M = glm::rotate(M, -PI/2, glm::vec3(0.0f, 1.0f, 0.0f)); // wyprostowanie czolgu wzglendem kamery
	M = glm::rotate(M, pozycja_kadlub, glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 HM = glm::translate(M, glm::vec3(0.0f, cos(progres_animacji_kdlub * tempo_animacji_kadlub) / 400, 0.0f));
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(HM));

	hull->draw(sp);

	glm::mat4 TM = glm::translate(M, glm::vec3(sin(progres_animacji_tracks * tempo_animacji_poziom)/100, cos(progres_animacji_tracks * tempo_animacji_pion)/300, 0.0f)); //animacja tracks
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(TM));
	tracks->draw(sp);

	M = glm::rotate(M, pozycja_wieza, glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::translate(M, glm::vec3(-0.2f, 0.0f, 0.0f)); // lekka poprawa osi obrotu
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

	turret->draw(sp);
}

void Tank::update(float czas,bool czy_anim_tracks)
{
	progres_animacji_kdlub += czas;
	if(czy_anim_tracks) progres_animacji_tracks += czas;
	//progres_animacji = fmod(progres_animacji,0.2);
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