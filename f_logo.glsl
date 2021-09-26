#version 330
uniform sampler2D textureMap0;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec2 iTexCoord0;


void main(void) {
	
	pixelColor=texture(textureMap0,iTexCoord0);//vec4(0.7f,0.7f,0.7f,1.0f);// 
}
