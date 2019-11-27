#version 330 core
layout (location = 0) in vec3 attrPos;
layout (location = 1) in vec2 attrTexCoords;
layout (location = 2) in vec3 attrNormal;
out vec2 TexCoord;
uniform mat4 projection, view, model;
void main() {
	gl_Position = projection * view * model * vec4(attrPos, 1.0);
	TexCoord = attrTexCoords;
}