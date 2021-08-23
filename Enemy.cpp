#include "Enemy.h"
Enemy::Enemy()
{

}

Enemy::Enemy(Tank t, wspolzedne p)
{
	tank_model = t;
	pozycja = p;
	//tank_model.set_pozycja_wieza(-1000);
}

void Enemy::draw(ShaderProgram* sp, glm::mat4 M)
{
	glm::mat4 pom_M = glm::translate(M, glm::vec3(pozycja.x, 0.0f, pozycja.y));

	pom_M = glm::scale(pom_M, glm::vec3(0.5, 0.5, 0.5));

	pom_M = glm::translate(pom_M, glm::vec3(0.0f, -0.8f, 0.0f));

	tank_model.draw(sp, pom_M);
}

void Enemy::update(float czas)
{
	//obracanie wierzy
	//jest ma³y problem kiedy wartosc obrotu wierzy wejdzie na plus
	//warto naprawic jednak w tym momencie stanie sie to dopiero po okolo 150 obrotach w odpowiednia strone
	//zmiana znakow psuje wyznaczanie kierunku

	float a = (pozycja.y - pozycja_gracza->y) / (pozycja.x - pozycja_gracza->x);
	float d = atan(a)+PI/2;


	float kierunek_patrzenia = fmod(abs(tank_model.get_pozycja_wieza() + tank_model.get_pozycja_kadlub()),2*PI);
	
	//if (kierunek_patrzenia < 0)kierunek_patrzenia *= -1;
	if (pozycja.x < pozycja_gracza->x) d +=PI;

	float odl = abs(d - kierunek_patrzenia);
	float odl_przez_0 = 2 * PI - abs(d - kierunek_patrzenia);

	if(abs(kierunek_patrzenia-d)>0.01) // unikamy niepotrzebnego ruchu lewo prawo kiedy gracz jest ju¿ namierzony
		if (odl_przez_0 < odl)
		{
			if (kierunek_patrzenia > d)
			{
				tank_model.obroc_wierze(-czas * (PI / 2));
			}
			else
			{
				tank_model.obroc_wierze(czas * (PI / 2));
			}
		}
		else
		{
			if (kierunek_patrzenia < d)
			{
				tank_model.obroc_wierze(-czas * (PI / 2));
			}
			else
			{
				tank_model.obroc_wierze(czas * (PI / 2));
			}
		}




	//std::cout << kierunek_patrzenia << " | " << d << std::endl;

	//std::cout << "(" << pozycja.x << "," << pozycja.y << ") | (" << pozycja_gracza->x << "," << pozycja_gracza->y << ")\n";

	tank_model.update(czas, 0);
}

void Enemy::set_tank_model(Tank t)
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

void Enemy::set_pozycja_gracza_pointer(wspolzedne* wp)
{
	pozycja_gracza = wp;
}

wspolzedne Enemy::get_pozycja()
{
	return pozycja;
}