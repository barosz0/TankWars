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
	int liczba_przeszkod = 10;
	int liczba_przeciwnikow = 1;

	//tworzenie tablicy flag zajecia pola
	flagi_blokady_pola.resize(rozmiar_mapy);
	for (int i = 0; i < rozmiar_mapy; i++)
	{
		flagi_blokady_pola[i].resize(rozmiar_mapy);
	}



	//tworzenie przeszkod
	
	int los_x = rand() % rozmiar_mapy;
	int los_y = rand() % rozmiar_mapy;
	
	for (int i = 0; i < liczba_przeszkod; i++) {

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

	for (int i = 0; i < liczba_przeciwnikow; i++) {

		while (flagi_blokady_pola[los_x][los_y] != 0) {
			los_x = rand() % rozmiar_mapy;
			los_y = rand() % rozmiar_mapy;
		}

		flagi_blokady_pola[los_x][los_y] = 2;

		przeciwnicy.push_back(new Enemy(*enemy_tank,wspolzedne(los_x*2,los_y*2)));
	}

	for (int i = 0; i < przeciwnicy.size(); i++)
	{
		przeciwnicy[i]->set_pozycja_gracza_pointer(&pozycja_gracza);
		przeciwnicy[i]->set_flagi_blokady_pola(&flagi_blokady_pola);
		przeciwnicy[i]->set_particle_manager(particle_manager);
	}

	for (int i = 0; i < rozmiar_mapy; i++)
	{
		for (int j = 0; j < rozmiar_mapy; j++)
		{
			std::cout << flagi_blokady_pola[i][j] << " ";
		}
		std::cout << "\n";
	}
	

	//gracz
	shoot_cooldown = 0;
	ilosc_ammo = 50;
	ilosc_hp = 6;
	player_dead_animation_progres = 0;
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

	float zmiana_wysokosci_scian = -0.3f;

	glm::mat4 pom_MS= glm::translate(M, glm::vec3(0.0f, zmiana_wysokosci_scian, -1.0f));
	pom_MS = glm::rotate(pom_MS, PI/2, glm::vec3(1.0f, 0.0f, 0.0f));



	for (int i = 0; i < rozmiar_mapy; i++)
	{
		pom_M = glm::translate(pom_MS, glm::vec3(2.0f*i, 0.0f, 0.0f));
		glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(pom_M));
		sciana_obj->draw(sp);
	}


	pom_MS = glm::translate(M, glm::vec3(0.0f, zmiana_wysokosci_scian, -1.0f));
	pom_MS = glm::rotate(pom_MS, PI / 2, glm::vec3(-1.0f, 0.0f, 0.0f));

	for (int i = 0; i < rozmiar_mapy; i++)
	{
		pom_M = glm::translate(pom_MS, glm::vec3(2.0f * i, -rozmiar_mapy  * 2, 0.0f));
		glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(pom_M));
		sciana_obj->draw(sp);
	}


	pom_MS = glm::translate(M, glm::vec3(-1.0f, zmiana_wysokosci_scian, 0.0f));
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

	pom_MS = glm::translate(M, glm::vec3(-1.0f, zmiana_wysokosci_scian, 0.0f));
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

void Gra::update(float czas, float speed_kam,float speed_wierza, float speed_kadlub, bool shoot) // do dodania mapa z flagami predkosci albo obsluga klawiczy w Gra
{
	//effect czasteczkowy
	particle_manager->update(czas);


	if (ilosc_hp <= 0)
	{
		player_dead_animation_progres += czas*0.2;
		return;
	}


	if (shoot && shoot_cooldown < 0 && ilosc_ammo>0) {

		glm::vec3 kierunek_lufy = glm::vec3(sin(player_tank->get_pozycja_kadlub() + player_tank->get_pozycja_wieza()), 0.0f,
			cos(player_tank->get_pozycja_kadlub() + player_tank->get_pozycja_wieza()));

		glm::vec3 czubek_lufy = kierunek_lufy * 0.7f;

		particle_manager->start_effect("shoot_effect", glm::vec3(pozycja_gracza.x, -0.2f, pozycja_gracza.y) + czubek_lufy,
			-(player_tank->get_pozycja_wieza() + player_tank->get_pozycja_kadlub()));
		player_oddaj_strzal();
		shoot_cooldown = 1;
		ilosc_ammo--;
		
	}

	if(shoot_cooldown>=0)
		shoot_cooldown -= czas;

	if (speed_kam < 0)
		speed_kadlub*= (-1);


	player_tank->obroc_wierze(czas * speed_wierza * (2 / 3.0));
	player_tank->obroc_kadlub(czas * speed_kadlub*(2/3.0));


	rusz_gracza(czas * speed_kam*1.5);
	//rusz_gracza(czas * speed_kam*5); //szybszy ruch


	if (speed_kam != 0 || speed_kadlub!=0)
		player_tank->update(czas,1);
	else
		player_tank->update(czas, 0);
	
	int *damage = new int(0);

	for (int i = 0; i < przeciwnicy.size(); i++)
	{
		przeciwnicy[i]->update(czas,damage);
	}
	ilosc_hp -= *damage;

	//smierc gracza
	if (ilosc_hp <= 0)
	{
		particle_manager->start_effect("dead", glm::vec3(pozycja_gracza.x, 0.0f, pozycja_gracza.y), 0);
	}




}

void Gra::drawScene(GLFWwindow* window, float obrot_kamery, float aspectRatioL)
{
	//float aspectRatio = 1; //do sprawdzenia czy potrzebne
	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 V = glm::lookAt(
		glm::vec3(0, 0, -2.5),
		glm::vec3(0, 0, 0),
		glm::vec3(0.0f, 1.0f, 0.0f));

	V = glm::rotate(V, obrot_kamery, glm::vec3(0.0f, -1.0f, 0.0f));
	glm::mat4 P = glm::perspective(50.0f * PI / 180.0f, aspectRatioL, 0.01f, 50.0f);

	mainShader->use();

	glUniformMatrix4fv(mainShader->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(mainShader->u("V"), 1, false, glm::value_ptr(V));

	//glm::mat4 M = M_main;

	glm::mat4 M = glm::mat4(1.0f);
	M = glm::translate(M, glm::vec3(0.0f, 0.0f, -pozycja_gracza.y));
	M = glm::translate(M, glm::vec3(-pozycja_gracza.x, 0.0f, 0.0f));


	M = glm::translate(M, glm::vec3(0.0f, -0.8f, 0.0f));

	draw_map(mainShader, M);
	draw_enemy(mainShader, M);

	glm::mat4 TM = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.5)); // macierz czo³gu
	TM = glm::translate(TM, glm::vec3(0.0f, -2.4f, 0.0f));
	TM = glm::translate(TM, glm::vec3(0.0f, -player_dead_animation_progres, 0.0f));

	player_tank->draw(mainShader, TM);

	particleShader->use();

	glUniformMatrix4fv(particleShader->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(particleShader->u("V"), 1, false, glm::value_ptr(V));


	glm::mat4 PM = glm::mat4(1.0f);

	PM = glm::translate(PM, glm::vec3(-pozycja_gracza.x, 0.0f, -pozycja_gracza.y));

	particle_manager->draw(particleShader, PM);
	UI->draw_interface(ilosc_hp, ilosc_ammo);

	glfwSwapBuffers(window); //Przerzuæ tylny bufor na przedni
}

void Gra::rusz_gracza(float dystans)
{

	float pomX = pozycja_gracza.x, pomY = pozycja_gracza.y;
	pomX += sin(player_tank->get_pozycja_kadlub()) * dystans;
	pomY += cos(player_tank->get_pozycja_kadlub()) * dystans;
	
	if (pomX < -0.5)pomX = -0.5;
	if (pomY < -0.5)pomY = -0.5;

	if (pomX > rozmiar_mapy * 2-1.6)pomX = rozmiar_mapy * 2-1.6;
	if (pomY > rozmiar_mapy * 2-1.6)pomY = rozmiar_mapy * 2-1.6;

	bool kolizja = false;
	wspolzedne pomW(pomX,pomY);

	for (int i = 0; i < przeszkody.size(); i++)
	{
		if (kolizja = przeszkody[i]->czy_kolizja(pomW))
			return;
	}

	pozycja_gracza = pomW;
	
}

void Gra::player_oddaj_strzal()
{
	//dziala... chyba dziala...

	float kierunek_lufy = player_tank->get_pozycja_kadlub() + player_tank->get_pozycja_wieza();//+PI/2;
	float a = tan(kierunek_lufy);
	float b = pozycja_gracza.x - a * pozycja_gracza.y;

	std::vector<Enemy*> trafienie;

	for (int i = 0; i < przeciwnicy.size(); i++)
	{
		float odl = abs(a * przeciwnicy[i]->get_pozycja().y - przeciwnicy[i]->get_pozycja().x + b) / sqrt(a * a + 1);
		std::cout << odl << std::endl;
		if (odl < 1) 
		{

			float xc = sin(player_tank->get_pozycja_kadlub() + player_tank->get_pozycja_wieza());
			float yc = cos(player_tank->get_pozycja_kadlub() + player_tank->get_pozycja_wieza());

			std::cout << "TEST\n";
			std::cout << pozycja_gracza.x << " " << pozycja_gracza.y << "\n";
			std::cout << przeciwnicy[i]->get_pozycja().x << " " << przeciwnicy[i]->get_pozycja().y << "\n";

			std::cout << "x = " << xc << " y = " << yc <<"\n";

			if (xc > 0 && pozycja_gracza.x > przeciwnicy[i]->get_pozycja().x) {
				std::cout << "1 to ja\n";
				continue;
			}

			if (xc < 0 && pozycja_gracza.x < przeciwnicy[i]->get_pozycja().x) {
				std::cout << "2 to ja\n";
				continue;
			}

			if (yc > 0 && pozycja_gracza.y > przeciwnicy[i]->get_pozycja().y) {
				std::cout << "3 to ja\n";
				continue;
			}

			if (yc < 0 && pozycja_gracza.y < przeciwnicy[i]->get_pozycja().y) {
				std::cout << "4 to ja\n";
				continue;
			}

			trafienie.push_back(przeciwnicy[i]);
			//std::cout << "trafienie" << std::endl;
			//przeciwnicy[i]->trafiony(1);

		}
			
	}

	float min = -1;
	int v = -1;

	for (int i = 0; i < trafienie.size(); i++)
	{
		float odl = pow(pozycja_gracza.x - trafienie[i]->get_pozycja().x, 2) + pow(pozycja_gracza.y - trafienie[i]->get_pozycja().y, 2);
		if (min = -1|| odl < min)
		{
			v = i;
			min = odl;
		}
	}

	if (v >= 0)
		trafienie[v]->trafiony(1);

}


void Gra::set_mainShader(ShaderProgram* sp)
{
	mainShader = sp;
}

void Gra::set_particleShader(ShaderProgram* sp)
{
	particleShader = sp;
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

void Gra::set_particle_manager(ParticleEffect_Manager* pm)
{
	particle_manager = pm;
}

void Gra::set_interface(Interface* i) 
{
	UI = i;
}