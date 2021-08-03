#include "obj3d.h"


obj3d::obj3d() :
	vertices(nullptr),
	normals(nullptr),
	texCoords(nullptr),
	vertexCount(0)
{}

obj3d::obj3d(float* v, float* n, float* t, int vc) :
	vertices(v),
	normals(n),
	texCoords(t),
	vertexCount(vc)
{}

obj3d::obj3d(float* v, float* n, float* t, int vc, GLuint tex):
	vertices(v),
	normals(n),
	texCoords(t),
	vertexCount(vc),
	texture(tex)
{}

void obj3d::draw(ShaderProgram* sp)
{
	
	// wgranie wspolzednych textur
	glEnableVertexAttribArray(sp->a("texCoord0"));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords);


	// wgranie textury
	glUniform1i(sp->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	// wgranie wspolzednych wierzcholkow
	glEnableVertexAttribArray(sp->a("vertex")); 
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, vertices);
	

	//wgranie wektorow normalnych wierzcholkow
	glEnableVertexAttribArray(sp->a("normal")); 
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, normals); 

	// rysowanie objektu
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);


	// wylaczanie przesylania
	glDisableVertexAttribArray(sp->a("texCoord0"));
	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("normal"));

}

void obj3d::set_texture(GLuint t)
{
	texture = t;
}