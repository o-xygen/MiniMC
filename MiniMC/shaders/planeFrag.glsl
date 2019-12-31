#version 330 core
out vec4 fragColor;
in vec2 TexCoord;

uniform sampler2D diffuse_tex1, diffuse_tex2;
void main(){
	fragColor = texture(diffuse_tex1, TexCoord);
}