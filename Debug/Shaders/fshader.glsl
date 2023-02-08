#version 330 core
out vec4 fragColor;
uniform vec4 uColor;
in vec3 Color;
void main(){
	fragColor=vec4(Color,1.0f);
}