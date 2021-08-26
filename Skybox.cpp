#include "Skybox.h"

using namespace std;



vector <const char*> skybox_faces = { 
	"models\\Skybox\\right.png",
	"models\\Skybox\\left.png",
	"models\\Skybox\\top.png",
	"models\\Skybox\\bot.png",
	"models\\Skybox\\front.png",
	"models\\Skybox\\back.png"
};


GLuint loadSkybox()
{
	GLuint ID_tekstury;
	glGenTextures(1, &ID_tekstury);
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID_tekstury);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	unsigned width, height, error;
	vector<unsigned char> image;
	for (int i = 0; i < 6; i++) {
		error = lodepng::decode(image, width, height, skybox_faces[i]);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());
	}
	

	return ID_tekstury;
}

Skybox::Skybox() {
	ID_tekstury = loadSkybox();
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, 144, &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
};

void Skybox::draw(ShaderProgram* sp)
{
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID_tekstury);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
}