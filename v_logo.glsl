#version 330


//Atrybuty
in vec2 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec2 texCoord0;

//Zmienne interpolowane
out vec4 ic;
out vec2 iTexCoord0;


void main(void) {

    iTexCoord0 = texCoord0;


    gl_Position=vec4(vertex,0.0,1.0);
}
