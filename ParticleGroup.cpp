#include "ParticleGroup.h"
ParticleGroup::ParticleGroup() :
	list_p(new Particle[1]),
	liczba_czasteczek(0),
	rozmiar_czasteczki(1),
	alpha_channel(false),
	scale_vec(glm::vec3(1.0f, 1.0f, 1.0f)),
	rozmiar_tex_x(1),
	rozmiar_tex_y(1),
	Group_active(true)
{

}

bool ParticleGroup::update(float czas)
{
	if (Group_active == false)
		return false;

	bool active = false;
	for (int i = 0; i < liczba_czasteczek; i++)
	{
		if (!list_p[i].active)
			continue;
		list_p[i].position += list_p[i].speed * czas;
		list_p[i].life_time -= czas;
		if (list_p[i].life_time < 0)
			list_p[i].active = false;
		
		if (list_p[i].active) // test czy sa jeszcze czasteczki do renderowania
			active = true;
			
	}

	if (active == false)
		Group_active = false;


	return active;
}

void ParticleGroup::draw(ShaderProgram* sp, glm::mat4 M)
{
	if (Group_active == false)
		return;


	if (list_p == nullptr)
		return;
	


	glDepthMask(false);

	glm::mat4 S = glm::scale(glm::mat4(1.0f), scale_vec);
	glUniformMatrix4fv(sp->u("S"), 1, false, glm::value_ptr(S));

	tabs_fill();



	glUniform1i(sp->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	for (int i = 0; i < liczba_czasteczek; i++)
	{


		if (!list_p[i].active) continue;



		glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(glm::translate(M, list_p[i].position))); // ustawienie pozycji czasteczki

		float a = list_p[i].life_time / list_p[i].max_life_time;
		glUniform4f(sp->u("color"), list_p[i].color.x, list_p[i].color.y, list_p[i].color.z, a);

		float progress = (1 - a) * rozmiar_tex_x * rozmiar_tex_y;

		int id1 = floor(progress);
		int id2;
		if (id1 < rozmiar_tex_x * rozmiar_tex_y)
			id2 = id1 + 1;
		else
			id2 = id1;

		id2 = id1;
		float permeation = 1 - (progress - id1); // ulamkowa czesc progressu

		glUniform2fv(sp->u("offset0"), 1, glm::value_ptr(tex_offset(id1)));
		glUniform2fv(sp->u("offset1"), 1, glm::value_ptr(tex_offset(id2)));
		glUniform1f(sp->u("permeation"), permeation);

		glEnableVertexAttribArray(sp->a("vertex"));
		glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, Vertices);

		glEnableVertexAttribArray(sp->a("texCoord0"));
		glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("color"));
	glDisableVertexAttribArray(sp->a("texCoord0"));
	glDepthMask(true);
}



glm::vec2 ParticleGroup::tex_offset(int id)
{
	glm::vec2 offset;

	offset.x = (id % rozmiar_tex_x) / (float)rozmiar_tex_x;
	offset.y = (id / rozmiar_tex_x) / (float)rozmiar_tex_y;

	//offset.y = offset.y-0.01; // textura dymu ma jakiœ problem i bez tego zle sie dzieli na podelementy

	return offset;
}

void ParticleGroup::tabs_fill()
{
	//first vertex
	Vertices[0] = 0.0f;
	Vertices[1] = -rozmiar_czasteczki / 2;
	Vertices[2] = -rozmiar_czasteczki / 2;
	Vertices[3] = 1.0f;

	texCoords[0] = 0.0f;
	texCoords[1] = 0.0f;

	//second
	Vertices[4] = 0.0f;
	Vertices[5] = +rozmiar_czasteczki / 2;
	Vertices[6] = -rozmiar_czasteczki / 2;
	Vertices[7] = 1.0f;

	texCoords[2] = 0.0f;
	texCoords[3] = 1.0f / rozmiar_tex_y;

	texCoords[2] = 0.0f;
	texCoords[3] = 1.0f / rozmiar_tex_y;

	//third
	Vertices[8] = 0.0f;
	Vertices[9] = -rozmiar_czasteczki / 2;
	Vertices[10] = rozmiar_czasteczki / 2;
	Vertices[11] = 1.0f;

	texCoords[4] = 1.0f / rozmiar_tex_x;
	texCoords[5] = 0.0f;

	//fourth

	Vertices[12] = 0.0f;
	Vertices[13] = rozmiar_czasteczki / 2;
	Vertices[14] = rozmiar_czasteczki / 2;
	Vertices[15] = 1.0f;

	texCoords[6] = 1.0f / rozmiar_tex_x;
	texCoords[7] = 1.0f / rozmiar_tex_y;
}

void ParticleGroup::set_list_particles(Particle* lp)
{
	list_p = lp;
}

void ParticleGroup::ParticleGroup::set_liczba_czasteczek(int lc)
{
	liczba_czasteczek = lc;
}

void ParticleGroup::set_rozmiar_czasteczek(float rc)
{
	rozmiar_czasteczki = rc;
}

void ParticleGroup::set_texture(GLuint t, int rx, int ry)
{
	texture = t;
	rozmiar_tex_x = rx;
	rozmiar_tex_y = ry;
}

void ParticleGroup::set_alpha_channel(bool c)
{
	alpha_channel = c;
}

void ParticleGroup::set_scale(glm::vec3 v)
{
	scale_vec = v;
}

int ParticleGroup::get_liczba_czasteczek()
{
	return liczba_czasteczek;
}

bool ParticleGroup::is_active()
{
	return Group_active;
}

void ParticleGroup::show_yourself()
{
	std::cout << "Start" << std::endl;
	std::cout << liczba_czasteczek << std::endl;
	std::cout << rozmiar_czasteczki << std::endl;
	std::cout << scale_vec.x << " " << scale_vec.y << " " << scale_vec.z << std::endl;
	std::cout << "Koniec" << std::endl;


}