#version 330 core
layout(location=0) in vec3 pos;
uniform vec3 uPosition;
void main(){
	gl_Position=vec4(pos+uPosition,1.0);
}