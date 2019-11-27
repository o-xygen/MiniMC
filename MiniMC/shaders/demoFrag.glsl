#version 330 core
out vec4 fragColor;
in vec2 TexCoord;

uniform sampler2D diffuse_tex;
void main(){
	fragColor = texture(diffuse_tex, TexCoord);
}