#pragma once
#include "lodepng.h"
#include "shaderprogram.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>


unsigned int loadSkybox(); //ladowanie tekstury z pliku

class Skybox
{
public:
	GLuint ID_tekstury;
	GLuint skyboxVAO, skyboxVBO;
	//wierzcholki skyboxa
	GLfloat skyboxVertices[144] = {
		-1.0f,  1.0f,-1.0f,
		-1.0f, -1.0f,-1.0f,
		 1.0f, -1.0f,-1.0f,
		 1.0f, -1.0f,-1.0f,
		 1.0f,  1.0f,-1.0f,
		-1.0f,  1.0f,-1.0f,

		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f,-1.0f,
		-1.0f,  1.0f,-1.0f,
		-1.0f,  1.0f,-1.0f,
		-1.0f,  1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,

		 1.0f, -1.0f,-1.0f,
		 1.0f, -1.0f, 1.0f,
		 1.0f,  1.0f, 1.0f,
		 1.0f,  1.0f, 1.0f,
		 1.0f,  1.0f,-1.0f,
		 1.0f, -1.0f,-1.0f,

		-1.0f, -1.0f, 1.0f,
		-1.0f,  1.0f, 1.0f,
		 1.0f,  1.0f, 1.0f,
		 1.0f,  1.0f, 1.0f,
		 1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,

		-1.0f,  1.0f,-1.0f,
		 1.0f,  1.0f,-1.0f,
		 1.0f,  1.0f, 1.0f,
		 1.0f,  1.0f, 1.0f,
		-1.0f,  1.0f, 1.0f,
		-1.0f,  1.0f,-1.0f,

		-1.0f, -1.0f,-1.0f,
		-1.0f, -1.0f, 1.0f,
		 1.0f, -1.0f,-1.0f,
		 1.0f, -1.0f,-1.0f,
		-1.0f, -1.0f, 1.0f,
		 1.0f, -1.0f, 1.0f
	};
	Skybox(); //konstruktor
	void draw(ShaderProgram* sp); //rysowanie skyboxa
};

