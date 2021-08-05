#include "Gra.h"

Gra::Gra()
{
	rozmiar_mapy = 10;
	M_main = glm::mat4(1.0f);
	create_game();

}

Gra::Gra(obj3d *z)
{
	podloze_obj = z;
	rozmiar_mapy = 10;
	M_main = glm::mat4(1.0f);
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

void Gra::drawScene(GLFWwindow* window, float obrot_kamery)
{
	float aspectRatio = 1; //do sprawdzenia czy potrzebne


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 V = glm::lookAt(
		glm::vec3(0, 0, -2.5),
		glm::vec3(0, 0, 0),
		glm::vec3(0.0f, 1.0f, 0.0f));

	V = glm::rotate(V, obrot_kamery, glm::vec3(0.0f, -1.0f, 0.0f));
	glm::mat4 P = glm::perspective(50.0f * PI / 180.0f, aspectRatio, 0.01f, 50.0f);

	mainShader->use();

	glUniformMatrix4fv(mainShader->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(mainShader->u("V"), 1, false, glm::value_ptr(V));

	glm::mat4 M = M_main;
	M = glm::translate(M, glm::vec3(0.0f, -0.8f, 0.0f));

	draw(mainShader, M); // do potencjalnego scalenia

	glm::mat4 TM = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.5)); // macierz czo³gu
	TM = glm::translate(TM, glm::vec3(0.0f, -2.4f, 0.0f));

	player_tank->draw(mainShader, TM);

	glfwSwapBuffers(window); //Przerzuæ tylny bufor na przedni
}

void Gra::set_mainShader(ShaderProgram* sp)
{
	mainShader = sp;
}

void Gra::set_M_main(glm::mat4 M)
{
	M_main = M;
}

void Gra::set_player_tank(Tank* t)
{
	player_tank = t;
}

glm::mat4 Gra::get_M_main()
{
	return M_main;
}