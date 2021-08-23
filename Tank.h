#pragma once
#include <GL/glew.h>
#include "obj3d.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "constants.h"


#include <tgmath.h>

class Tank
{
	obj3d* turret;
	obj3d* hull; //warto zamienic na wskazniki
	obj3d* tracks;

	float pozycja_wieza; // obrot wiezy
	float pozycja_kadlub; // obrot kadluba

	float progres_animacji_kdlub;
	float progres_animacji_tracks;


public:



	Tank();
	Tank(obj3d *turret_obj, obj3d *hull_obj, obj3d *tracks_obj);

	void draw(ShaderProgram* sp,glm::mat4 M);
	void update(float czas, bool czy_anim_tracks);

	float get_pozycja_wieza();
	void set_pozycja_wieza(float p);
	void obroc_wierze(float p);

	float get_pozycja_kadlub();
	void set_pozycja_kadlub(float p);
	void obroc_kadlub(float p);


};
