#version 330
uniform sampler2D textureMap0;

uniform float permeation;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec4 ic; 
in vec2 iTexCoord0;
in vec2 iTexCoord1;


void main(void) {
	
	vec4 color0 = texture(textureMap0,iTexCoord0);
	vec4 color1 = texture(textureMap0,iTexCoord1);

	pixelColor= mix(color0,color1,permeation)*ic;//vec4(0.7f,0.7f,0.7f,1.0f);// 
}
