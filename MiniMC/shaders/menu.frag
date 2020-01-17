#version 330 core

in vec4 a;

void main(){
	if (a.y > 0.85 && a.y < 0.95 && ((a.x > -0.95 && a.x < -0.85)))
		gl_FragColor = vec4(0.8, 0.8, 0.8, 0.8);
	else if (a.y > 0.85 && a.y < 0.95 && ((a.x < 0.95 && a.x > 0.85)))
		gl_FragColor = vec4(0.7, 0.5, 0.6, 0.8);
	else if (a.y < 0.8 && (a.x < 0.95 && a.x > 0.85))
		gl_FragColor = vec4(0.7, 0.5, 0.6, 0.8);
	else if (a.y < 0.8 && (a.x > -0.95 && a.x < -0.8))
		gl_FragColor = vec4(0.8, 0.8, 0.8, 0.8);
	else
		gl_FragColor = vec4(0.3, 0.3, 0.3, 0.1);
}
