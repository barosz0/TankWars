#version 330

out vec4 Kolor;
in  vec3 TexCoords;

uniform samplerCube skybox;

void main(){
Kolor = texture(skybox,TexCoords);
}
