#pragma once
#include <GL/glew.h>
#include "shaderprogram.h"

class obj3d
{
	float* vertices;
	float* normals;
	float* texCoords;
	int vertexCount;
	GLuint texture;

public:

	obj3d();
	obj3d(float* v, float* n, float* t, int vc);
	obj3d(float* v, float* n, float* t, int vc,  GLuint tex);

	void draw(ShaderProgram* sp);
	void set_texture(GLuint t);

};

