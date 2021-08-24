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
	std::cout << xd << " | " << yd << "\n"; 

	/*
	int xs = round(pozycja_gracza->x / 2);
	int ys = round(pozycja_gracza->y / 2);

	int xd = pozycja.x / 2;
	int yd = pozycja.y / 2;
	*/
	//std::cout<< fb[xd][yd] <<"\n";
	
	

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

	//debug
	for (int i = 0; i < odle.size(); i++)
	{
		for (int j = 0; j < odle.size(); j++)
		{
			std::cout << odle[i][j] << " ";
		}
		std::cout << "\n";
	}
	//debug

	if (min != -1) {
		flag_czy_ruch = true;
		flag_czy_obrot = true;
		gdzie_ruch = pom;
	}
}

void Enemy::update(float czas)
{
	//poruszanie siê w kierunku gracza

	if (!flag_czy_ruch)
	{
		szukaj_drogi();
	}


	if (flag_czy_obrot)
	{
		float a = (pozycja.y - gdzie_ruch->y) / (pozycja.x - gdzie_ruch->x);
		float d = atan(a) + PI / 2;


		float kierunek_patrzenia = fmod(abs(tank_model.get_pozycja_kadlub()), 2 * PI);

		//if (kierunek_patrzenia < 0)kierunek_patrzenia *= -1;
		if (pozycja.x < gdzie_ruch->x) d += PI;

		float odl = abs(d - kierunek_patrzenia);
		float odl_przez_0 = 2 * PI - abs(d - kierunek_patrzenia);

		if (abs(kierunek_patrzenia - d) > 0.02) // unikamy niepotrzebnego ruchu lewo prawo kiedy gracz jest ju¿ namierzony
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

		if(pozycja.x == gdzie_ruch->x&& pozycja.y == gdzie_ruch->y)
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
		else if(pozycja.y == gdzie_ruch->y) // ruch w x
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


	// patrzenie na gracza

	//obracanie wierzy
	//jest "ma³y" problem kiedy wartosc obrotu wierzy wejdzie na plus
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

	tank_model.update(czas, flag_czy_ruch);
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