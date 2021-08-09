#version 330
layout (location=0) in vec3 position;
out vec3 TexCoords;

universal mat4 P;
universal mat4 V;
universal mat4 M;

void main(){
TexCoords = position;
vec4 pos = P*V*M*vec4(position,1.0f);
gl_Position = pos.xyww
}
