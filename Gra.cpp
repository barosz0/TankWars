#include "Gra.h"

Gra::Gra()
{
	rozmiar_mapy = 10;
	create_game();

}

Gra::Gra(obj3d *z)
{
	podloze_obj = z;
	rozmiar_mapy = 10;
	create_game();

}


void Gra::create_game()
{
	//podloze = new int* [rozmiar_mapy];
	//for (int i = 0; i < rozmiar_mapy; i++)
	//{
	//	podloze[i] = new int[rozmiar_mapy];
	//}
}

void Gra::draw(ShaderProgram* sp, glm::mat4 M)
{

	glm::mat4 pom_M = M;
	for(int j=0;j<rozmiar_mapy;j++)
		for (int i = 0; i < rozmiar_mapy; i++)
		{
			pom_M= glm::translate(M, glm::vec3(2.0f*j, 0.0f, 0.0f));
			pom_M = glm::translate(pom_M, glm::vec3(0.0f, 0.0f, 2.0f*i));
			glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(pom_M));
			podloze_obj->draw(sp);
		}


}

void Gra::update(float t)
{
	
}

