#include "Gra.h"

Gra::Gra()
{
	rozmiar_mapy = 10;
	//create_game();

}

Gra::Gra(obj3d *z)
{

	podloze_obj = z;
	rozmiar_mapy = 10;
	//create_game();

}


void Gra::create_game()
{
	//tworzenie tablicy flag zajecia pola
	flagi_blokady_pola.resize(rozmiar_mapy);
	for (int i = 0; i < rozmiar_mapy; i++)
	{
		flagi_blokady_pola[i].resize(rozmiar_mapy);
	}



	//tworzenie przeszkod
	int los_x = rand() % rozmiar_mapy;
	int los_y = rand() % rozmiar_mapy;

	for (int i = 0; i < 10; i++) {

		while (flagi_blokady_pola[los_x][los_y] != 0) {
			los_x = rand() % rozmiar_mapy;
			los_y = rand() % rozmiar_mapy;
		}
		
		flagi_blokady_pola[los_x][los_y] = 1;

		przeszkody.push_back(new Obstacle(modele_przeskod->operator[](rand() % modele_przeskod->size()),wspolzedne(los_x*2,los_y*2)));
	}

	//tworzenie przeciwnikow
	los_x = rand() % rozmiar_mapy;
	los_y = rand() % rozmiar_mapy;

	for (int i = 0; i < 3; i++) {

		while (flagi_blokady_pola[los_x][los_y] != 0) {
			los_x = rand() % rozmiar_mapy;
			los_y = rand() % rozmiar_mapy;
		}

		flagi_blokady_pola[los_x][los_y] = 2;

		przeciwnicy.push_back(new Enemy(enemy_tank,wspolzedne(los_x,los_y)));
	}
}

void Gra::draw_map(ShaderProgram* sp, glm::mat4 M) // rysowanie podloza i scian
{
	//rysowanie podlogi
	glm::mat4 pom_M = M;
	for(int j=0;j<rozmiar_mapy;j++)
		for (int i = 0; i < rozmiar_mapy; i++)
		{
			pom_M= glm::translate(M, glm::vec3(2.0f*j, 0.0f, 0.0f));
			pom_M = glm::translate(pom_M, glm::vec3(0.0f, 0.0f, 2.0f*i));
			glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(pom_M));
			podloze_obj->draw(sp);
		}

	//rysowanie scian
	glm::mat4 pom_MS= glm::translate(M, glm::vec3(0.0f, 0.0f, -1.0f));
	pom_MS = glm::rotate(pom_MS, PI/2, glm::vec3(1.0f, 0.0f, 0.0f));



	for (int i = 0; i < rozmiar_mapy; i++)
	{
		pom_M = glm::translate(pom_MS, glm::vec3(2.0f*i, 0.0f, 0.0f));
		glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(pom_M));
		sciana_obj->draw(sp);
	}


	pom_MS = glm::translate(M, glm::vec3(0.0f, 0.0f, -1.0f));
	pom_MS = glm::rotate(pom_MS, PI / 2, glm::vec3(-1.0f, 0.0f, 0.0f));

	for (int i = 0; i < rozmiar_mapy; i++)
	{
		pom_M = glm::translate(pom_MS, glm::vec3(2.0f * i, -rozmiar_mapy  * 2, 0.0f));
		glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(pom_M));
		sciana_obj->draw(sp);
	}


	pom_MS = glm::translate(M, glm::vec3(-1.0f, 0.0f, 0.0f));
	pom_MS = glm::rotate(pom_MS, PI / 2, glm::vec3(0.0f, 0.0f, -1.0f));
	pom_MS = glm::rotate(pom_MS, PI / 2, glm::vec3(0.0f, 1.0f, 0.0f));
	//glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(pom_MS));
	//sciana_obj->draw(sp);

	
		for (int i = 0; i < rozmiar_mapy; i++)
		{
			pom_M = glm::translate(pom_MS, glm::vec3(-2.0f * i, 0.0f, 0.0f));
			glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(pom_M));
			sciana_obj->draw(sp);
		}

		pom_MS = glm::translate(M, glm::vec3(-1.0f, 0.0f, 0.0f));
		pom_MS = glm::rotate(pom_MS, PI / 2, glm::vec3(0.0f, 0.0f, 1.0f));
		pom_MS = glm::rotate(pom_MS, PI / 2, glm::vec3(0.0f, 1.0f, 0.0f));

		for (int i = 0; i < rozmiar_mapy; i++)
		{
			pom_M = glm::translate(pom_MS, glm::vec3(-2.0f * i, -rozmiar_mapy*2, 0.0f));
			glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(pom_M));
			sciana_obj->draw(sp);
		}

		
		
		//rysowanie przeszkod

		

		for (int i = 0; i < przeszkody.size(); i++)
		{
			przeszkody[i]->draw(sp,M);
		}
}

void Gra::draw_enemy(ShaderProgram* sp, glm::mat4 M)
{
	for (int i = 0; i < przeciwnicy.size(); i++)
	{
		przeciwnicy[i]->draw(sp, M);
	}
}

void Gra::update(float czas, float speed_kam,float speed_wierza, float speed_kadlub) // do dodania mapa z flagami predkosci albo obsluga klawiczy w Gra
{
	if (speed_kam < 0)
		speed_kadlub*= (-1);

	player_tank->obroc_wierze(czas * speed_wierza);  //do przeniesienia do update
	player_tank->obroc_kadlub(czas * speed_kadlub);  //do przeniesienia do update



	//rusz_gracza(czas * speed_kam);
	rusz_gracza(czas * speed_kam*5); //szybszy ruch


	if (speed_kam != 0 || speed_kadlub!=0)
		player_tank->update(czas,1);
	else
		player_tank->update(czas, 0);
	
	for (int i = 0; i < przeciwnicy.size(); i++)
	{
		przeciwnicy[i]->update(czas);
	}
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

	//glm::mat4 M = M_main;

	glm::mat4 M = glm::mat4(1.0f);
	M = glm::translate(M, glm::vec3(0.0f, 0.0f, -pozycja_gracza.y));
	M = glm::translate(M, glm::vec3(-pozycja_gracza.x, 0.0f, 0.0f));


	M = glm::translate(M, glm::vec3(0.0f, -0.8f, 0.0f));

	draw_map(mainShader, M); // do potencjalnego scalenia
	draw_enemy(mainShader, M);

	glm::mat4 TM = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.5)); // macierz czo³gu
	TM = glm::translate(TM, glm::vec3(0.0f, -2.4f, 0.0f));

	player_tank->draw(mainShader, TM);

	glfwSwapBuffers(window); //Przerzuæ tylny bufor na przedni
}

void Gra::rusz_gracza(float dystans)
{

	float pomX = pozycja_gracza.x, pomY = pozycja_gracza.y;
	pomX += sin(player_tank->get_pozycja_kadlub()) * dystans;
	pomY += cos(player_tank->get_pozycja_kadlub()) * dystans;
	
	if (pomX < -0.5)pomX = -0.5;
	if (pomY < -0.5)pomY = -0.5;

	if (pomX > rozmiar_mapy * 2-1.5)pomX = rozmiar_mapy * 2-1.5;
	if (pomY > rozmiar_mapy * 2-1.5)pomY = rozmiar_mapy * 2-1.5;

	bool kolizja = false;
	wspolzedne pomW(pomX,pomY);

	for (int i = 0; i < przeszkody.size(); i++)
	{
		if (kolizja = przeszkody[i]->czy_kolizja(pomW))
			return;
	}

	//wersja z funkcjia w obiekcie przeszkody
	/*do {
		kolizja = false;
		int i;
		for (i = 0; i < przeszkody.size(); i++)
		{
			if (kolizja = przeszkody[i]->czy_kolizja(pomW))
				return;
				//break;
		}
		if (kolizja)
		{
			pomW=przeszkody[i]->rozwiaz_kolizje(pozycja_gracza, pomW, 3);
		}

	} while (kolizja);
	*/
	pozycja_gracza = pomW;

	//pozycja_gracza.x = pomX;
	//pozycja_gracza.y = pomY;
	//std::cout << pozycja_gracza.x << " | " << pozycja_gracza.y << std::endl;
	
}

void Gra::set_mainShader(ShaderProgram* sp)
{
	mainShader = sp;
}


void Gra::set_player_tank(Tank* t)
{
	player_tank = t;
}

void Gra::set_enemy_tank(Tank* t)
{
	enemy_tank = t;
}


void Gra::set_sciana_obj(obj3d* o)
{
	sciana_obj = o;
}


void Gra::set_rozmiar_mapy(int r)
{
	rozmiar_mapy = r;
}

void Gra::set_modele_przeszkod(std::vector<obj3d*>* mp)
{
	modele_przeskod = mp;
}