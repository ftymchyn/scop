//VERTEX SHADER
#version 330 core

layout(location = 0) in vec4 position;

void main()
{
	gl_Position = position;
}

//FRAGMENT SHADER
#version 330 core

void main()
{
	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}