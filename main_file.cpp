/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "myCube.h"
#include "myTeapot.h"


#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "Tank.h"
#include "obj3d.h"
#include "Gra.h"


float speed_x=0;
float speed_y=0;
float speed_kamera = 0;
float aspectRatio=1;

float speed_w = 0; // obrot wierza
float speed_k = 0; // obrot kadlub


ShaderProgram *sp;

GLuint tex0;
GLuint tex1;

Gra* main_game;
glm::mat4 M_main = glm::mat4(1.0f);

obj3d *pom_obj;

Tank *t;

//Odkomentuj, żeby rysować kostkę
float* vertices = myCubeVertices;
float* normals = myCubeNormals;
float* texCoords = myCubeTexCoords;
float* colors = myCubeColors;
int vertexCount = myCubeVertexCount;


//Odkomentuj, żeby rysować czajnik
//float* vertices = myTeapotVertices;
//float* normals = myTeapotVertexNormals;
//float* texCoords = myTeapotTexCoords;
//float* colors = myTeapotColors;
//int vertexCount = myTeapotVertexCount;

using namespace std;

vector<float*> load(string fn)
{
	std::fstream file;
	std::string linia;
	file.open(fn);


	string prefix = "nic";

	int a;
	char c;

	vector<glm::vec3> v;
	vector<glm::vec2> t;
	vector<glm::vec3> n;
	glm::vec3 temp3;
	glm::vec3 temp2;

	vector<int> vi;
	vector<int> ti;
	vector<int> ni;



	while (getline(file, linia))
	{
		istringstream ss(linia);
		ss >> prefix;
		//cout << prefix << endl;

		if (!ss.fail())
		{

			if (prefix == "v")
			{
				ss >> temp3.x >> temp3.y >> temp3.z;
				v.push_back(temp3);
			}

			else if (prefix == "vt")
			{
				ss >> temp2.x >> temp2.y;
				t.push_back(temp2);
			}
			else if (prefix == "vn")
			{
				ss >> temp3.x >> temp3.y >> temp3.z;
				n.push_back(temp3);
			}
			else if (prefix == "f")
			{
				for (int i = 0; i < 3; i++)
				{
					ss >> a;
					vi.push_back(a);
					ss >> c >> a;
					ti.push_back(a);
					ss >> c >> a;
					ni.push_back(a);

				}
			}
		}

	}


	vector<glm::vec3> vectors;
	vector<glm::vec2> texture;
	vector<glm::vec3> normalsv;


	for (int i = 0; i < vi.size(); i++)
	{
		//cout << vi[i] <<endl;
		vectors.push_back(v[vi[i] - 1]);
		texture.push_back(t[ti[i] - 1]);
		normalsv.push_back(n[ni[i] - 1]);
	}

	//cout << "v: " << v.size() << " t: " << t.size() << " vn: " << n.size() << endl ;

	float* vertex_p = new float[vectors.size() * 4];
	float* texture_p = new float[vectors.size() * 2];
	float* normals_p = new float[vectors.size() * 4];

	for (int i = 0; i < vectors.size(); i++)
	{
		vertex_p[4 * i] = vectors[i].x;
		vertex_p[4 * i + 1] = vectors[i].y;
		vertex_p[4 * i + 2] = vectors[i].z;
		vertex_p[4 * i + 3] = 1.0f;
	}

	for (int i = 0; i < vectors.size(); i++)
	{
		texture_p[2 * i] = texture[i].x;
		texture_p[2 * i + 1] = 1-texture[i].y;
		//tex[i + 2] = texture[i].z;
	}

	for (int i = 0; i < vectors.size(); i++)
	{
		normals_p[4 * i] = normalsv[i].x;
		normals_p[4 * i + 1] = normalsv[i].y;
		normals_p[4 * i + 2] = normalsv[i].z;
		normals_p[4 * i + 3] = 0.0f;
	}

	vector<float*> ret;
	ret.push_back(vertex_p);
	ret.push_back(texture_p);
	ret.push_back(normals_p);
	ret.push_back(new float(vectors.size()));
	//*cn = normals_p;
	//*ct = texture_p;
	//*cv = vertex_p;

	//vertices = vertex_p;
	//normals = normals_p;
	//texCoords = texture_p;
	//vertexCount = vectors.size();


	return ret;
}



GLuint readTexture(const char* filename) {
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);

	//Wczytanie do pamięci komputera
	std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
	unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
	//Wczytaj obrazek
	unsigned error = lodepng::decode(image, width, height, filename);
	cout << error << endl;
	//Import do pamięci karty graficznej
	glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
	//Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	return tex;
}

//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}


void keyCallback(GLFWwindow* window,int key,int scancode,int action,int mods) {
    if (action==GLFW_PRESS) {
        if (key==GLFW_KEY_LEFT) speed_x=-PI/2;
        if (key==GLFW_KEY_RIGHT) speed_x=PI/2;
        if (key==GLFW_KEY_UP) speed_y=PI/2;
        if (key==GLFW_KEY_DOWN) speed_y=-PI/2;

		// obrot wierzy
		if (key == GLFW_KEY_Q) speed_w +=PI / 2;
		if (key == GLFW_KEY_E) speed_w -= PI / 2;

		// obrot kadlub
		if (key == GLFW_KEY_A) speed_k += PI / 2;
		if (key == GLFW_KEY_D) speed_k -= PI / 2;

		// ruch przod tyl
		if (key == GLFW_KEY_W) speed_kamera -= PI / 2;
		if (key == GLFW_KEY_S) speed_kamera += PI / 2;

    }
    if (action==GLFW_RELEASE) {
        if (key==GLFW_KEY_LEFT) speed_x=0;
        if (key==GLFW_KEY_RIGHT) speed_x=0;
        if (key==GLFW_KEY_UP) speed_y=0;
        if (key==GLFW_KEY_DOWN) speed_y=0;

		// obrot wierzy
		if (key == GLFW_KEY_Q) speed_w -= PI / 2;
		if (key == GLFW_KEY_E) speed_w += PI / 2;

		// obrot kadlub
		if (key == GLFW_KEY_A) speed_k -= PI / 2;
		if (key == GLFW_KEY_D) speed_k += PI / 2;

		// ruch przod tyl
		if (key == GLFW_KEY_W) speed_kamera += PI / 2;
		if (key == GLFW_KEY_S) speed_kamera -= PI / 2;
    }
}

void windowResizeCallback(GLFWwindow* window,int width,int height) {
    if (height==0) return;
    aspectRatio=(float)width/(float)height;
    glViewport(0,0,width,height);
}

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
	
	
	tex1 = readTexture("sky.png");
	glClearColor(0,0,0,1);
	glEnable(GL_DEPTH_TEST);
	glfwSetWindowSizeCallback(window,windowResizeCallback);
	glfwSetKeyCallback(window,keyCallback);

	//tex0 = readTexture("models\\crate_1.png");
	//load("models\\crate.obj");

	//tex0 = readTexture("models\\1.png");
	//load("models\\1t.obj");

	vector<float*> r;

	tex0 = readTexture("models\\Tank\\turret.png");
	r = load("models\\Tank\\TurretT.obj");
	obj3d tank_turret(r[0], r[2], r[1], *r[3], tex0);

	tex0 = readTexture("models\\Tank\\hull.png");
	r = load("models\\Tank\\HullT.obj");
	obj3d tank_hull(r[0], r[2], r[1], *r[3], tex0);

	tex0 = readTexture("models\\Tank\\tracks.png");
	r = load("models\\Tank\\TracksT.obj");
	obj3d tank_tracks(r[0], r[2], r[1], *r[3], tex0);

	t = new Tank(tank_turret, tank_hull, tank_tracks);

	

	vertices = r[0];
	texCoords = r[1];
	normals = r[2];
	vertexCount = *r[3];

	tex0 = readTexture("models\\Squere\\GrassTex.png");
	r = load("models\\Squere\\Squere.obj");
	pom_obj = new obj3d(r[0], r[2], r[1], *r[3], tex0);
	
	main_game = new Gra(pom_obj);

	/*tex0 = readTexture("models\\SkyBox\\Tex.png");
	r = load("models\\SkyBox\\Skybox.obj");
	pom_obj = new obj3d(r[0], r[2], r[1], *r[3], tex0);*/


	//load2("models\\crate.obj");

	

	

	sp = new ShaderProgram("v_simplest.glsl", NULL, "f_simplest.glsl");
}


//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
    //************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************
	glDeleteTextures(1, &tex0);
    delete sp;
}




//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window,float angle_x,float angle_y,float obrot_kamery) {
	//************Tutaj umieszczaj kod rysujący obraz******************l
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 V=glm::lookAt(
         glm::vec3(0, 0, -2.5),
         glm::vec3(0,0,0),
         glm::vec3(0.0f,1.0f,0.0f)); //Wylicz macierz widoku

	V = glm::rotate(V, obrot_kamery, glm::vec3(0.0f, -1.0f, 0.0f));


    glm::mat4 P=glm::perspective(50.0f*PI/180.0f, aspectRatio, 0.01f, 50.0f); //Wylicz macierz rzutowania

	glm::mat4 M = M_main;
	M=glm::rotate(M,angle_y,glm::vec3(1.0f,0.0f,0.0f)); //Wylicz macierz modelu
	M=glm::rotate(M,angle_x,glm::vec3(0.0f,1.0f,0.0f)); //Wylicz macierz modelu
	

	M = glm::translate(M, glm::vec3(0.0f, -0.8f, 0.0f));
    sp->use();//Aktywacja programu cieniującego
    //Przeslij parametry programu cieniującego do karty graficznej
    glUniformMatrix4fv(sp->u("P"),1,false,glm::value_ptr(P));
    glUniformMatrix4fv(sp->u("V"),1,false,glm::value_ptr(V));

	//glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));
	main_game->draw(sp, M);

	glm::mat4 TM = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.5));
	TM = glm::translate(TM, glm::vec3(0.0f, -2.4f, 0.0f));
	t->draw(sp, TM) ;
	
	/*float sc = 8.0f;
	TM = glm::scale(glm::mat4(1.0f), glm::vec3(sc, sc, sc));
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(TM));

	pom_obj->draw(sp);*/

    /*
	glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));

	glEnableVertexAttribArray(sp->a("texCoord0"));
	glVertexAttribPointer(sp->a("texCoord0"),2, GL_FLOAT, false, 0, texCoords);

	glUniform1i(sp->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex0);

	glUniform1i(sp->u("textureMap1"), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex1);


    glEnableVertexAttribArray(sp->a("vertex"));  //Włącz przesyłanie danych do atrybutu vertex
    glVertexAttribPointer(sp->a("vertex"),4,GL_FLOAT,false,0,vertices); //Wskaż tablicę z danymi dla atrybutu vertex

	glEnableVertexAttribArray(sp->a("color"));  //Włącz przesyłanie danych do atrybutu color
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, colors); //Wskaż tablicę z danymi dla atrybutu color

	glEnableVertexAttribArray(sp->a("normal"));  //Włącz przesyłanie danych do atrybutu normal
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, normals); //Wskaż tablicę z danymi dla atrybutu normal


    glDrawArrays(GL_TRIANGLES,0,vertexCount); //Narysuj obiekt

	glDisableVertexAttribArray(sp->a("texCoord0"));
    glDisableVertexAttribArray(sp->a("vertex"));  //Wyłącz przesyłanie danych do atrybutu vertex
	glDisableVertexAttribArray(sp->a("color"));  //Wyłącz przesyłanie danych do atrybutu color
	glDisableVertexAttribArray(sp->a("normal"));  //Wyłącz przesyłanie danych do atrybutu normal
	*/
    glfwSwapBuffers(window); //Przerzuć tylny bufor na przedni
}


int main(void)
{
	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
	{
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjujące

	//Główna pętla
	float angle_x=0; //Aktualny kąt obrotu obiektu
	float angle_y=0; //Aktualny kąt obrotu obiektu
	float czas = 0;


	glfwSetTime(0); //Zeruj timer
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
        angle_x+=speed_x*glfwGetTime(); //Zwiększ/zmniejsz kąt obrotu na podstawie prędkości i czasu jaki upłynał od poprzedniej klatki
        angle_y+=speed_y*glfwGetTime(); //Zwiększ/zmniejsz kąt obrotu na podstawie prędkości i czasu jaki upłynał od poprzedniej klatki
		czas = glfwGetTime();
		//t->set_pozycja_wieza(t->get_pozycja_wieza() + speed_w * glfwGetTime());
		t->obroc_wierze(czas * speed_w);
		t->obroc_kadlub(czas * speed_k);
		//M_main = glm::rotate(M_main, czas * speed_k, glm::vec3(0.0f, 0.0f, 0.0f));
		M_main = glm::translate(M_main, glm::vec3(0.0f, 0.0f,cos(t->get_pozycja_kadlub())*czas*speed_kamera));
		M_main = glm::translate(M_main, glm::vec3(sin(t->get_pozycja_kadlub()) * czas * speed_kamera,0.0f, 0.0f));

        glfwSetTime(0); //Zeruj timer
		drawScene(window,angle_x,angle_y,t->get_pozycja_wieza()+t->get_pozycja_kadlub()); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
