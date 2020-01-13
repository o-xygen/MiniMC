#version 330 core

uniform mat4 ortho, view, model;

void main() {
	gl_Position = ortho * view * model * gl_Vertex;
}