#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform mat4 S;

//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec2 texCoord0;

//Zmienne interpolowane
out vec4 ic;
out vec2 iTexCoord0;
out vec2 iTexCoord1;

uniform vec2 offset0;
uniform vec2 offset1;

uniform vec4 color;

mat4 rotationX( in float angle ) {
	return mat4(	1.0,		0,			0,			0,
			 		0, 	cos(angle),	-sin(angle),		0,
					0, 	sin(angle),	 cos(angle),		0,
					0, 			0,			  0, 		1);
}

mat4 rotationY( in float angle ) {
	return mat4(	cos(angle),		0,		sin(angle),	0,
			 				0,		1.0,			 0,	0,
					-sin(angle),	0,		cos(angle),	0,
							0, 		0,				0,	1);
}

mat4 rotationZ( in float angle ) {
	return mat4(	cos(angle),		-sin(angle),	0,	0,
			 		sin(angle),		cos(angle),		0,	0,
							0,				0,		1,	0,
							0,				0,		0,	1);
}

void main(void) {

    iTexCoord0 = texCoord0+offset0;
	iTexCoord1 = texCoord0+offset1;
    ic =color;//vec4(0.7f,0.7f,0.7f,1.0f);

    mat4 TM  = M;

   TM[0][0] = V[0][0];
   TM[0][1] = V[1][0];
   TM[0][2] = V[2][0];
   TM[1][0] = V[0][1];
   TM[1][1] = V[1][1];
   TM[1][2] = V[2][1];
   TM[2][0] = V[0][2];
   TM[2][1] = V[1][2];
   TM[2][2] = V[2][2];

   TM =TM*rotationY(3.14/2);
   TM = TM *S;

    gl_Position=P*V*TM*vertex;
}
