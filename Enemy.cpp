#include "Enemy.h"
Enemy::Enemy()
{
	shoot_cooldown = 0;
	hp_enemy = 1;
	dead_animation_progress = 0;
	flag_czy_widac_gracza = false;
}

Enemy::Enemy(Tank t, wspolzedne p)
{
	shoot_cooldown = 0;
	hp_enemy = 1;
	dead_animation_progress = 0;
	flag_czy_widac_gracza = false;
	tank_model = t;
	pozycja = p;
}

void Enemy::draw(ShaderProgram* sp, glm::mat4 M)
{
	glm::mat4 pom_M = glm::translate(M, glm::vec3(pozycja.x, 0.0f, pozycja.y));

	pom_M = glm::translate(pom_M, glm::vec3(0.0f, -dead_animation_progress, 0.0f));

	pom_M = glm::scale(pom_M, glm::vec3(0.5, 0.5, 0.5));

	pom_M = glm::translate(pom_M, glm::vec3(0.0f, -0.8f, 0.0f));

	tank_model.draw(sp, pom_M);
}


int Enemy::ktory_nastepny(std::vector<std::pair<int, int>>k, std::vector<std::vector<int>> odl)
{
	if (k.size() == 0)
		return -1;

	int m = 0;

	for (int i = 1; i < k.size(); i++)
	{
		if (odl[k[m].first][k[m].second] > odl[k[i].first][k[i].second])
		{
			m = i;
		}
	}

	return m;
}

void Enemy::szukaj_drogi()
{
	std::vector<std::vector<int>> fb=*flagi_blokady_pola;
	std::vector<std::vector<int>> odle;
	
	odle.resize(fb.size());
	for (int i = 0; i < fb.size(); i++)
	{
		odle[i].resize(fb.size());
	}

	for(int i=0;i<odle.size();i++)
		for (int j = 0; j < odle.size(); j++)
		{
			odle[i][j] = 2147483646; // zakres int
		}


	
	std::vector<std::pair<int, int>> kolejny;
	
	
	
	int xs = pozycja.x / 2;
	int ys = pozycja.y / 2;

	int xd = round(pozycja_gracza->x / 2);
	int yd = round(pozycja_gracza->y / 2);
	

	//Problem jak gracz jest na polu z przeszkoda
	//Probujemy sasiednie pola
	if (fb[xd][yd] > 0)
	{	
		bool flag = false;
		if(xd<fb.size()-1)
			if (fb[xd + 1][yd] == 0) {
				xd++;
				flag = true;
			}
		if(!flag && xd>0)
			if (fb[xd - 1][yd] == 0) {
				xd--;
				flag = true;
			}
		if(!flag && yd>0)
			if (fb[xd][yd - 1] == 0) {
				yd--;
				flag = true;
			}
		if(!flag && yd < fb.size() - 1)
			if (fb[xd][yd + 1] == 0) {
				yd++;
				flag = true;
			}
		
		// nie fajne miejsce
		if (!flag)
			return;
	}


	kolejny.push_back(std::make_pair(xd, yd));
	fb[xd][yd] = 3;
	odle[xd][yd] = 0;

	while (kolejny.size() > 0)
	{
		
		int o = ktory_nastepny(kolejny, odle);
		if (o < 0)
			break;
		std::pair<int, int> obecny = kolejny[o];
		if(obecny.first<fb.size()-1)
		if (fb[obecny.first+1][obecny.second] == 0)
		{
			if (odle[obecny.first + 1][obecny.second] > odle[obecny.first][obecny.second] + 1)
			{
				odle[obecny.first + 1][obecny.second] = odle[obecny.first][obecny.second] + 1;
				kolejny.push_back(std::make_pair(obecny.first + 1, obecny.second));
			}
		}
		
		if (obecny.first >0)
		if (fb[obecny.first - 1][obecny.second] == 0)
		{
			if (odle[obecny.first - 1][obecny.second] > odle[obecny.first][obecny.second] + 1)
			{
				odle[obecny.first - 1][obecny.second] = odle[obecny.first][obecny.second] + 1;
				kolejny.push_back(std::make_pair(obecny.first - 1, obecny.second));
			}
		}

		if (obecny.second < fb.size()-1)
		if (fb[obecny.first][obecny.second+1] == 0)
		{
			if (odle[obecny.first][obecny.second+1] > odle[obecny.first][obecny.second] + 1)
			{
				odle[obecny.first][obecny.second+1] = odle[obecny.first][obecny.second] + 1;
				kolejny.push_back(std::make_pair(obecny.first, obecny.second+1));
			}
		}

		if (obecny.second >0)
		if (fb[obecny.first][obecny.second - 1] == 0)
		{
			if (odle[obecny.first][obecny.second - 1] > odle[obecny.first][obecny.second] + 1)
			{
				odle[obecny.first][obecny.second - 1] = odle[obecny.first][obecny.second] + 1;
				kolejny.push_back(std::make_pair(obecny.first, obecny.second - 1));
			}
		}
		
		kolejny[o] = kolejny.back();
		kolejny.pop_back();
	}

	if (odle[xs][ys] == 0)
	{
		flag_czy_ruch = false;
		flag_czy_obrot = false;
		gdzie_ruch = nullptr;
		return;
	}

	wspolzedne *pom = new wspolzedne(0, 0);

	int min = -1;
	if (xs < fb.size() - 1)
		if (min==-1||odle[xs+1][ys]<min) {
			min = odle[xs + 1][ys];
			pom->x = xs + 1;
			pom->y = ys;
		}
	if (xs> 0)
		if (odle[xs - 1][ys] < min || min==-1) {
			min = odle[xs - 1][ys];
			pom->x = xs - 1;
			pom->y = ys;
		}
	if (ys > 0)
		if (odle[xs][ys - 1]<min || min==-1) {
			min = odle[xs][ys - 1];
			pom->x = xs;
			pom->y = ys - 1;
		}
	if (ys < fb.size() - 1)
		if (odle[xs][ys + 1] <min || min == -1) {
			min = odle[xs][ys + 1];
			pom->x = xs;
			pom->y = ys + 1;
		}
	
	pom->x = pom->x * 2;
	pom->y = pom->y * 2;

	odle[xs][ys] = -1;


	if (min != -1) {
		flag_czy_ruch = true;
		flag_czy_obrot = true;
		gdzie_ruch = pom;
	}
}

void Enemy::update(float czas, int* damage)
{
	if (hp_enemy > 0)
	{
		if (shoot_cooldown > 0)
			shoot_cooldown -= czas;

		if (shoot_cooldown <= 0 && flag_czy_widac_gracza)
		{
			//warto tu dodac prawdopodobienstwo strzalu
			if (oddaj_strzal())
				*damage += 1;
		}

		_update_ruch_tank(czas);

		_update_obrot_wierzy(czas);

		tank_model.update(czas, flag_czy_ruch);
	}
	else
	{
		if(dead_animation_progress<10)
			dead_animation_progress += czas*0.5;
	}
}

void Enemy::trafiony(int dam)
{
	hp_enemy -= dam;
	if (hp_enemy <= 0)
	{
		if(dead_animation_progress==0)
			particle_manager->start_effect("dead", glm::vec3(pozycja.x, 0.0f, pozycja.y), 0);
	}
}


bool Enemy::oddaj_strzal()
{
	
	glm::vec3 kierunek_lufy = glm::vec3(sin(tank_model.get_pozycja_kadlub() + tank_model.get_pozycja_wieza()), 0.0f,
		cos(tank_model.get_pozycja_kadlub() + tank_model.get_pozycja_wieza()));

	glm::vec3 czubek_lufy = kierunek_lufy * 0.7f; // odleglosc lufy od osi obrotu

	particle_manager->start_effect("shoot_effect", glm::vec3(pozycja.x, -0.2f, pozycja.y) + czubek_lufy,
		-(tank_model.get_pozycja_kadlub() + tank_model.get_pozycja_wieza()));

	shoot_cooldown = 2;

	return true;
}

void Enemy::_update_ruch_tank(float czas)
{
	if (!flag_czy_ruch)
	{
		//szukaj_drogi();
	}

	//poruszanie siê w kierunku gracza
	if (flag_czy_obrot)
	{
		float a = (pozycja.y - gdzie_ruch->y) / (pozycja.x - gdzie_ruch->x);
		float d = atan(a) + PI / 2;


		float kierunek_patrzenia = fmod(abs(tank_model.get_pozycja_kadlub()), 2 * PI);

		//if (kierunek_patrzenia < 0)kierunek_patrzenia *= -1;
		if (pozycja.x < gdzie_ruch->x) d += PI;

		float odl = abs(d - kierunek_patrzenia);
		float odl_przez_0 = 2 * PI - abs(d - kierunek_patrzenia);

		if (abs(kierunek_patrzenia - d) > 0.02)
			if (odl_przez_0 < odl)
			{
				if (kierunek_patrzenia > d)
				{
					tank_model.obroc_kadlub(-czas * (PI / 2));
				}
				else
				{
					tank_model.obroc_kadlub(czas * (PI / 2));
				}
			}
			else
			{
				if (kierunek_patrzenia < d)
				{
					tank_model.obroc_kadlub(-czas * (PI / 2));
				}
				else
				{
					tank_model.obroc_kadlub(czas * (PI / 2));
				}
			}
		else
		{
			flag_czy_obrot = false;
		}
	}
	else if (flag_czy_ruch)
	{

		float przebyty_dystans = czas * PI / 2;

		if (pozycja.x == gdzie_ruch->x && pozycja.y == gdzie_ruch->y)
		{
			std::cout << "error ruch w nie odpowiednim kierunku\n";
		}
		else if (pozycja.x == gdzie_ruch->x) // ruch w y
		{
			float odl = gdzie_ruch->y - pozycja.y;
			if (przebyty_dystans > abs(odl))
			{
				pozycja = *gdzie_ruch;
				flag_czy_ruch = false;
			}
			else
			{
				if (odl > 0)
				{
					pozycja.y += przebyty_dystans;
				}
				else
				{
					pozycja.y -= przebyty_dystans;
				}
			}
		}
		else if (pozycja.y == gdzie_ruch->y) // ruch w x
		{
			float odl = gdzie_ruch->x - pozycja.x;
			if (przebyty_dystans > abs(odl))
			{
				pozycja = *gdzie_ruch;
				flag_czy_ruch = false;
			}
			else
			{
				if (odl > 0)
				{
					pozycja.x += przebyty_dystans;
				}
				else
				{
					pozycja.x -= przebyty_dystans;
				}
			}
		}

	}
}

void Enemy::_update_obrot_wierzy(float czas)
{

	//obracanie wierzy
	//jest "ma³y" problem kiedy wartosc obrotu wierzy wejdzie na plus
	//warto naprawic jednak w tym momencie stanie sie to dopiero po okolo 150 obrotach w odpowiednia strone
	//zmiana znakow psuje wyznaczanie kierunku

	float odleglosc_strzelania = 36; // odleglosc na jaka przeciwnicy maja namierzac i strzelac w gracza


	float odleglosc_od_gracza = pow((pozycja_gracza->x - pozycja.x), 2) + pow((pozycja_gracza->y - pozycja.y), 2);
	
	//std::cout << odleglosc_od_gracza << std::endl;



	float a = (pozycja.y - pozycja_gracza->y) / (pozycja.x - pozycja_gracza->x);
	float d = atan(a) + PI / 2;




	float kierunek_patrzenia = fmod(abs(tank_model.get_pozycja_wieza() + tank_model.get_pozycja_kadlub()), 2 * PI);

	if (odleglosc_od_gracza > 36)
		d = fmod(abs(tank_model.get_pozycja_kadlub()), 2 * PI);


	//if (kierunek_patrzenia < 0)kierunek_patrzenia *= -1;
	if (pozycja.x < pozycja_gracza->x&& odleglosc_od_gracza <= 36) d += PI;

	float odl = abs(d - kierunek_patrzenia);
	float odl_przez_0 = 2 * PI - abs(d - kierunek_patrzenia);

	if (abs(kierunek_patrzenia - d) > 0.01)// unikamy niepotrzebnego ruchu lewo prawo kiedy gracz jest ju¿ namierzony
	{
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

	}

	if (odleglosc_od_gracza < 36 && abs(kierunek_patrzenia - d) <= 0.01)
	{
		flag_czy_widac_gracza = true;
	}
	else
	{
		flag_czy_widac_gracza = false;
	}
}

bool Enemy::czy_zyje()
{
	if (dead_animation_progress == 0)
		return true;
	return false;
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

void Enemy::set_particle_manager(ParticleEffect_Manager* pm)
{
	particle_manager = pm;
}