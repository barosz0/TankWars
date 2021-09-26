#include "Interface.h"
Interface::Interface() :
	rozmiar_numbers(1)
{

}

void Interface::draw_interface(int hp, int ammo_ilosc)
{
	interface_shader->use();
	glClear(GL_DEPTH_BUFFER_BIT);

	_draw_hearts(hp, -1, -1);
	_draw_ammo(ammo_ilosc, 0.6, -1);
	_draw_crosshair(0, 0.05);
}

void Interface::_draw_hearts(int hp, float x, float y)
{
	float rozmiar=0.1;

	glUniform1i(interface_shader->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, hearts);

	float offset = 1 / 3.0 *2;

	for (int i = 1; i <= 3; i++)
	{
		float x_offset = rozmiar * (i - 1);

		float vertex[] =
		{
			x + x_offset,y,
			x + x_offset,y + rozmiar,
			x + rozmiar + x_offset,y,
			x + rozmiar + x_offset,y + rozmiar
		};

		glEnableVertexAttribArray(interface_shader->a("vertex"));
		glVertexAttribPointer(interface_shader->a("vertex"), 2, GL_FLOAT, false, 0, vertex);


		if (hp >= i * 2)
		{
			offset = 0;
		}
		else if (hp >= i * 2-1)
		{
			offset = 1 / 3.0 * 1;
		}
		else
		{
			offset = 1 / 3.0 * 2;
		}

		float texCoords[] =
		{
			0 + offset,1,
			0 + offset,0,
			1 / 3.0 + offset,1,
			1 / 3.0 + offset,0
		};

		glEnableVertexAttribArray(interface_shader->a("texCoord0"));
		glVertexAttribPointer(interface_shader->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

	glDisableVertexAttribArray(interface_shader->a("vertex"));
	glDisableVertexAttribArray(interface_shader->a("texCoord0"));
	//std::cout << "Tu\n";
}

void Interface::_draw_ammo(int ilosc, float x, float y)
{
	float rozmiar = 0.1;

	glUniform1i(interface_shader->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ammo);



	float vertex[] =
	{
		x,y,
		x,y + rozmiar,
		x + rozmiar,y,
		x + rozmiar,y + rozmiar
	};

	float texCoords[] =
	{
		0,1,
		0,0,
		1,1,
		1,0
	};

	glEnableVertexAttribArray(interface_shader->a("vertex"));
	glVertexAttribPointer(interface_shader->a("vertex"), 2, GL_FLOAT, false, 0, vertex);

	glEnableVertexAttribArray(interface_shader->a("texCoord0"));
	glVertexAttribPointer(interface_shader->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//liczba pociskow

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, numbers);


	for (int i = 0; i < 2; i++) {
		x += rozmiar;


		float vertex2[] =
		{
			x,y,
			x,y + rozmiar,
			x + rozmiar,y,
			x + rozmiar,y + rozmiar
		};

		glEnableVertexAttribArray(interface_shader->a("vertex"));
		glVertexAttribPointer(interface_shader->a("vertex"), 2, GL_FLOAT, false, 0, vertex2);

		int id = ilosc / 10;
		ilosc -= id *10;

		float l = numbers_offset[id].first / (float)rozmiar_numbers; // lewy
		float p = l + numbers_offset[id].second / (float)rozmiar_numbers; // prawy

		//std::cout << l << " " << p << "\n";

		float texCoords2[] =
		{
			l,0.5,
			l,0,
			p,0.5,
			p,0
		};

		glEnableVertexAttribArray(interface_shader->a("texCoord0"));
		glVertexAttribPointer(interface_shader->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords2);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		ilosc *= 10;
	}

	glDisableVertexAttribArray(interface_shader->a("vertex"));
	glDisableVertexAttribArray(interface_shader->a("texCoord0"));
}

void Interface::_draw_crosshair(float x, float y)
{
	float rozmiar = 0.1;

	glUniform1i(interface_shader->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, crosshair);




	float vertex[] =
	{
		x - rozmiar/2, y - rozmiar/2,
		x - rozmiar/2 ,y + rozmiar/2,
		x + rozmiar/2, y - rozmiar/2,
		x + rozmiar/2, y + rozmiar/2
	};

	float texCoords[] =
	{
		0,1,
		0,0,
		1,1,
		1,0
	};

	glEnableVertexAttribArray(interface_shader->a("vertex"));
	glVertexAttribPointer(interface_shader->a("vertex"), 2, GL_FLOAT, false, 0, vertex);

	glEnableVertexAttribArray(interface_shader->a("texCoord0"));
	glVertexAttribPointer(interface_shader->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableVertexAttribArray(interface_shader->a("vertex"));
	glDisableVertexAttribArray(interface_shader->a("texCoord0"));
}

void Interface::set_tex_numbers(GLuint t, std::vector<std::pair<int, int>> n_o, int r_n)
{
	numbers = t;
	numbers_offset = n_o;
	rozmiar_numbers = r_n;
}

void Interface::set_tex_ammo(GLuint t)
{
	ammo = t;
}

void Interface::set_tex_hearts(GLuint t)
{
	hearts = t;
}

void Interface::set_shader(ShaderProgram *s)
{
	interface_shader = s;
}

void Interface::set_tex_crosshair(GLuint t)
{
	crosshair = t;
}