#include "ParticleEffect.h"
ParticleEffect::ParticleEffect()
{

}

void ParticleEffect::sort_particle()
{
	for(int j=0;j<liczba_czasteczek;j++)
		for (int i = j+1; i < liczba_czasteczek; i++)
		{
			if (list_p[i].speed.x < list_p[i + 1].speed.x)
			{
				std::swap(list_p[i], list_p[i + 1]);
			}
		}
}

void ParticleEffect::create_effect(glm::vec3 pozycja_startowa,int l_c, float rot)
{
	liczba_czasteczek = l_c;
	rozmiar_czasteczki = 0.5;//0.2;
	rotation = rot;

	std::default_random_engine generator;
	std::normal_distribution<double> distribution(0.0, 1);
	std::normal_distribution<double> distribution2(0.8, 0.1);

	list_p = new Particle[liczba_czasteczek];

	for (int i = 0; i < liczba_czasteczek; i++)
	{
		list_p[i].position = pozycja_startowa;

		list_p[i].speed = glm::vec3(distribution(generator), distribution(generator), abs(distribution(generator)) * 20);
		list_p[i].speed *= 0.1f;

		list_p[i].speed = rotateVec3Y(list_p[i].speed, rot);
		//list_p[i].speed = glm::vec3(0.0f, 0.0f, 0.0f);

		list_p[i].color = glm::vec3(1, 1, 1);
		list_p[i].life_time = 0.5;//abs(distribution2(generator));//1;
		list_p[i].max_life_time = list_p[i].life_time;
	}
	//sort_particle();
}

void ParticleEffect::update(float czas)
{
	for (int i = 0; i < liczba_czasteczek; i++)
	{	
		if (!list_p[i].active)
			continue;
		list_p[i].position += list_p[i].speed*czas;
		//list_p[i].speed = list_p[i].speed* 0.7f * czas;
		list_p[i].life_time -= czas;
		if (list_p[i].life_time < 0)
			list_p[i].active = false;
		//list_p[i].speed.x += list_p[i].speed.x * 20 * czas;
		//list_p[i].speed.x += list_p[i].speed.y * 20 * czas;
		//list_p[i].speed.x += list_p[i].speed.z * 20 * czas;


	}
}

void ParticleEffect::draw(ShaderProgram* sp,glm::mat4 M)
{
	if (list_p == nullptr)
		return;

	glDepthMask(false);
	//sp->use();
	//glm::mat4 S = glm::mat4(1.0f);
	glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(0.1, 0.1, 0.1));
	//S = glm::mat4(1.0f);
	glUniformMatrix4fv(sp->u("S"), 1, false, glm::value_ptr(S));
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));
	

	glUniform2f(sp->u("texture_size"), rozmiar_tex_x, rozmiar_tex_y);


	for (int i = 0; i < liczba_czasteczek; i += 1)
	{
		//glm::mat4 pom = glm::rotate(M, rotation, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 pom = glm::translate(M, list_p[i].position);
		
		glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(pom));

		//liczenie koloru
		float a = list_p[i].life_time / list_p[i].max_life_time;
		if (a < 0) continue;
		glUniform4f(sp->u("color"), list_p[i].color.x, list_p[i].color.y, list_p[i].color.z, a);



		float progress = (1-a) * rozmiar_tex_x * rozmiar_tex_y;


		int id1 = floor(progress);
		int id2;
		if (id1 < rozmiar_tex_x * rozmiar_tex_y)
			id2 = id1 + 1;
		else
			id2 = id1;

		id2 = id1;
		float permeation = 1 - (progress - id1); // ulamkowa czesc progressu


		glUniform2fv(sp->u("offset0"),1, glm::value_ptr(tex_offset(id1)));
		glUniform2fv(sp->u("offset1"), 1, glm::value_ptr(tex_offset(id2)));
		glUniform1f(sp->u("permeation"), permeation);

	
		//first vertex
		Vertices[0] = 0.0f;
		Vertices[1] = - rozmiar_czasteczki / 2;
		Vertices[2] = - rozmiar_czasteczki / 2;
		Vertices[3] = 1.0f;

		texCoords[0] = 0.0f ;
		texCoords[1] = 0.0f ;

		//second
		Vertices[4] = 0.0f;
		Vertices[5] =+ rozmiar_czasteczki/2;
		Vertices[6] =- rozmiar_czasteczki / 2;
		Vertices[7] = 1.0f;

		texCoords[2] = 0.0f;
		texCoords[3] = 1.0f/rozmiar_tex_y;

		texCoords[2] = 0.0f ;
		texCoords[3] = 1.0f / rozmiar_tex_y;

		//third
		Vertices[8] = 0.0f;
		Vertices[9] = - rozmiar_czasteczki / 2;
		Vertices[10] =rozmiar_czasteczki / 2;
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

		glEnableVertexAttribArray(sp->a("vertex"));
		glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, Vertices);


		glEnableVertexAttribArray(sp->a("texCoord0"));
		glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords);

		glUniform1i(sp->u("textureMap0"), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glDisableVertexAttribArray(sp->a("vertex"));
		glDisableVertexAttribArray(sp->a("color"));
		glDisableVertexAttribArray(sp->a("texCoord0"));

	}

	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(true);
}

glm::vec2 ParticleEffect::tex_offset(int id)
{
	glm::vec2 offset;
	
	offset.x = (id % rozmiar_tex_x) / (float)rozmiar_tex_x;
	offset.y= (id / rozmiar_tex_x) / (float)rozmiar_tex_y;

	//offset.y = offset.y-0.01; // textura dymu ma jakiœ problem i bez tego zle sie dzieli na podelementy

	return offset;
}

glm::vec3 ParticleEffect::rotateVec3Y(glm::vec3 v, float angle)
{
	glm::mat3 rot = glm::mat3(1.0f);

	rot[0][0] = cos(angle);
	rot[2][2] = cos(angle);
	rot[0][2] = sin(angle);
	rot[2][0] = -sin(angle);


	return rot*v;
}


void ParticleEffect::test_draw(ShaderProgram* sp, glm::mat4 M, float* vertices, int vertexCount) 
{
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

	glEnableVertexAttribArray(sp->a("vertex"));
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, vertices);

	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	glDisableVertexAttribArray(sp->a("vertex"));
}

void ParticleEffect::set_texture(GLuint t, int x, int y)
{
	texture = t;
	rozmiar_tex_x = x;
	rozmiar_tex_y = y;
}