#version 330 core

in vec4 a;

void main(){
	if (a.x > -0.15 && a.y > (0.666*a.x - 0.1) && a.y < (-0.666*a.x + 0.1))
		gl_FragColor = vec4(0,0,0,1);
	else
		gl_FragColor = vec4(1,1,1,1);
}
